#pragma once

#include <Windows.h>
#include <string>
#include <cstddef>
#include <vector>

#include "InputEvents.hpp"
#include "Types.hpp"

class Console {
private:
	static Console* instance;
	Console(void);
	~Console(void);
public:
	/*
	* Get the existing and unique Console instance.
	*/
	inline static Console* getInstance(void) { return instance; }
private:
	/*
	* Destroy the unique instance, this function should be called once.
	*/
	inline static void destroyInstance(void) { delete instance; instance = nullptr; }

	friend class Game;
private:
	HANDLE hStdOut;
	HANDLE hStdIn;

	HANDLE screen;
	CHAR_INFO* buffer;
	size_t buffer_size;

	HWND hWndConsole;
	DWORD dwInputMode;

	/*
	* Input mode to restore once the game is closed.
	*/
	DWORD dwRestoreInputMode;

	/*
	* Title of the window to be restored once the game is closed.
	*/
	std::wstring restoreTitle;

	/*
	* The window style to be restored once the game is closed.
	*/
	DWORD dwRestoreStyle;
public:
	/*
	* Clears the entire screen buffer.
	*/
	void clear(void);

	/*
	* Renders the buffer data on the screen.
	*/
	void presentBuffer(void) const;

	/*
	* Checks if there are any pending input events to read and returns
	* an InputEvent object, if there are not pending input events returns
	* nullptr.
	*/
	InputEvent* checkInput(void) const;

	/*
	* Draws a color vector on the console buffer.
	* 
	* If data_rect has smaller size than data actually is, the data will be
	* clipped.
	* 
	* If data_rect is greater than screen_rect, the data will be clipped to fit the
	* draw area given by the second rectangle.
	* 
	* Negative width or height values in data_rect will be ignored and converted
	* to positive values.
	* 
	* Negative width or height in screen_rect will result in a flip effect along
	* x or y axis respectively.
	* 
	*/
	void draw(const ColorData& data, const Rect2d& data_rect, const Rect2d& screen_rect);

	/*
	* Draws a solid color in the specified area at the specified position (0,0 by default).
	*/
	void draw(Color color, uint32_t width, uint32_t height, int x = 0, int y = 0);

	/*
	* Draws a text string on the screen.
	*/
	void drawString(std::string string, const int x = 0, const int y = 0);

	/*
	* Draws a frame around the specified rect.
	*/
	void drawFrame(const Rect2d& rect, Color color = Color::red);
};

