#include "Console.hpp"
#include <Configuration.hpp>
#include <cinttypes>
#include <exception>
#include <iostream>
#include <vector>
#include <cmath>

Console* Console::instance = new Console();

/*
* Windows console initialization.
*/
Console::Console(void) {
	CONSOLE_CURSOR_INFO ccinf;
	CONSOLE_FONT_INFOEX cfi;
	SMALL_RECT rcSize;
	COORD dims;
	LONG winStyle;

	/*
	* Get the standard input and output handlers.
	*/
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);

	/*
	* Create a new console buffer.
	*/
	screen = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	if (screen == INVALID_HANDLE_VALUE) {
		throw std::exception("Cannot create the console screen buffer");
	}

	/*
	* Allocate the char buffer.
	*/
	buffer_size = config::screen::width * config::screen::height * sizeof(CHAR_INFO);
	buffer = new CHAR_INFO[buffer_size]();

	if (!SetConsoleActiveScreenBuffer(screen)) {
		throw std::exception("Cannot activate the console screen buffer");
	}

	SetConsoleTitle(config::game::name.c_str());

	/*
	* Hide the console cursor.
	*/
	ccinf.dwSize = 100;
	ccinf.bVisible = FALSE;
	
	SetConsoleCursorInfo(screen, &ccinf);

	/*
	* Change the input mode: disable the Windows 10 console behaviour on click,
	* since this freezes console until the user finish its text selection.
	*/
	GetConsoleMode(hStdIn, &dwRestoreInputMode);
	dwInputMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS | (dwRestoreInputMode & ~ENABLE_QUICK_EDIT_MODE);
	SetConsoleMode(hStdIn, dwInputMode);

	/*
	* Change the default font.
	*/
	ZeroMemory(&cfi, sizeof(cfi));
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.nFont = 0;
	cfi.dwFontSize.X = config::screen::font_size_x;
	cfi.dwFontSize.Y = config::screen::font_size_y;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Terminal");

	SetCurrentConsoleFontEx(screen, TRUE, &cfi);

	/*
	* Configure the window size.
	*/
	rcSize.Left = 0;
	rcSize.Top = 0;
	rcSize.Right = 1;
	rcSize.Bottom = 1;
	dims.X = config::screen::width;
	dims.Y = config::screen::height;

	SetConsoleWindowInfo(screen, TRUE, &rcSize);
	SetConsoleScreenBufferSize(screen, dims);

	rcSize.Right = config::screen::width - 1;
	rcSize.Bottom = config::screen::height - 1;

	SetConsoleWindowInfo(screen, TRUE, &rcSize);
	Sleep(10);

	/*
	* Remove the maximize button and the thick frame to resize the window.
	*/
	hWndConsole = GetConsoleWindow();

	dwRestoreStyle = GetWindowLong(hWndConsole, GWL_STYLE);
	winStyle = dwRestoreStyle ^ (WS_MAXIMIZEBOX | WS_THICKFRAME);

	SetWindowLong(hWndConsole, GWL_STYLE, winStyle);

	/*
	* Save the window title to restore once the game is closed.
	*/
	wchar_t buffer[500] = { 0 };
	GetWindowText(hWndConsole, buffer, 500);
	restoreTitle = buffer;
}

/*
 * Windows console restauration.
 */
Console::~Console(void) {
	SetWindowText(hWndConsole, restoreTitle.c_str());

	SetConsoleActiveScreenBuffer(hStdOut);
	CloseHandle(screen);

	SetConsoleMode(hStdIn, dwRestoreInputMode);

	SetWindowLong(hWndConsole, GWL_STYLE, dwRestoreStyle);

	delete [] buffer;
}

void Console::clear(void) {
	memset(buffer, 0, buffer_size);
}

void Console::presentBuffer(void) const {
	SMALL_RECT rcRegion = { 0, 0, config::screen::width - 1, config::screen::height - 1 };
	COORD dims = { config::screen::width, config::screen::height };
	COORD origin = { 0,0 };

	WriteConsoleOutput(screen, buffer, dims, origin, &rcRegion);
}

InputEvent* Console::checkInput(void) const {
	DWORD dwPendingEvents = 0;
	BOOL result = 0;

	result = GetNumberOfConsoleInputEvents(hStdIn, &dwPendingEvents);

	if (result && dwPendingEvents > 0) {
		INPUT_RECORD ev = { 0 };
		DWORD dwEventsRead = 0;

		// Get the next event.

		ReadConsoleInput(hStdIn, &ev, 1, &dwEventsRead);

		// Process events.

		if (ev.EventType == KEY_EVENT) {
			auto event = new KeyboardEvent();

			event->keycode = ev.Event.KeyEvent.wVirtualKeyCode;
			event->is_pressed = ev.Event.KeyEvent.bKeyDown;

			return event;
		}

		if (ev.EventType == MOUSE_EVENT) {
			auto event = new MouseEvent();
			const int button_state = ev.Event.MouseEvent.dwButtonState;
			const int mx = ev.Event.MouseEvent.dwMousePosition.X;
			const int my = ev.Event.MouseEvent.dwMousePosition.Y;

			event->button =
				button_state & FROM_LEFT_1ST_BUTTON_PRESSED ? MouseButton::left :
				button_state & RIGHTMOST_BUTTON_PRESSED ? MouseButton::right :
				MouseButton::other;

			event->is_pressed = button_state != 0;

			event->position.x = static_cast<double>(mx);
			event->position.y = static_cast<double>(my);

			return event;
		}
	}

	return nullptr;
}

void Console::draw(const std::vector<uint8_t>& data, uint32_t width, uint32_t height, int x, int y) {
	const int max_x = static_cast<int>(width) + x;
	const int max_y = static_cast<int>(height) + y;

	for (int by = y; by < max_y; by++) {
		for (int bx = x; bx < max_x; bx++) {

			if (bx >= 0 && by >= 0 && by < config::screen::height && bx < config::screen::width) {
				const int buffer_pos = bx + (by * config::screen::width);
				const int data_pos = (bx - x) + (by - y) * width;

				buffer[buffer_pos].Attributes = data[data_pos];
			}

		}
	}

}

void Console::draw(uint8_t colour, uint32_t width, uint32_t height, int x, int y) {

	for (int by = y; by < y + height; by++) {
		for (int bx = x; bx < x + width; bx++) {

			if (bx >= 0 && by >= 0 && by < config::screen::height && bx < config::screen::width) {
				const int buffer_pos = bx + (by * config::screen::width);

				buffer[buffer_pos].Attributes = colour;
			}

		}
	}

}