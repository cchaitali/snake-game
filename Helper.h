#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <conio.h>

using namespace std;

// Directions in which snake can travel.
enum Direction
{
	STOPPED = 0,
	UP,
	LEFT,
	DOWN,
	RIGHT,
	NUM_DIRECTIONS
};

// Hides the cursor.
inline void HideCursor()
{
	static const HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(outputHandle, &info);
}

// Sets cursor position on console to given co-ordinates.
inline void SetCursorPosition(COORD coord)
{
	static const HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
	SetConsoleCursorPosition(outputHandle, coord);
}

// Clears screen.
inline void ClearScreen()
{
	static const HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };
	DWORD written;

	cout.flush();

	// Find out the current width and height of the console window.
	if (!GetConsoleScreenBufferInfo(outputHandle, &csbi))
		return;

	// Fill the entire console screen with blanks.
	FillConsoleOutputCharacterA(outputHandle, ' ', csbi.dwSize.X * csbi.dwSize.Y, topLeft, &written);

	// Set the buffer's attributes accordingly.
	FillConsoleOutputAttribute(outputHandle, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, topLeft, &written);

	// Move the cursor to the top left of the screen.
	SetConsoleCursorPosition(outputHandle, topLeft);
}