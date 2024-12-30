#pragma once

#include <Windows.h>
#include <string>
#include <cstddef>
#include <vector>

#include "InputEvents.hpp"

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
	InputEvent* checkInput() const;

	/*
	* Draws a colour vector on the console buffer.
	*/
	void draw(const std::vector<uint8_t>& data, uint32_t width, uint32_t height, int x, int y);

	/*
	* Draws a solid colour in the specified area at the specified position (0,0 by default).
	*/
	void draw(uint8_t colour, uint32_t width, uint32_t height, int x = 0, int y = 0);
};

