#pragma once

#include "Helper.h"

class Food
{
private:
	COORD position;
	int arenaStartRow, arenaStartCol, arenaEndRow, arenaEndCol;

public:
	Food()
	{
		position = { -1, -1 };
	}

	// Sets arena position.
	inline void SetArenaPosition(int startRow, int startCol, int endRow, int endCol)
	{
		arenaStartRow = startRow;
		arenaStartCol = startCol;
		arenaEndRow = endRow;
		arenaEndCol = endCol;
	}

	// Returns position of food.
	inline COORD GetPosition()
	{
		return position;
	}

	// Generates location for new food.
	inline void Generate()
	{
		position = { (SHORT)((rand() % (arenaEndCol - arenaStartCol + 1)) + arenaStartCol), (SHORT)((rand() % (arenaEndRow - arenaStartRow + 1)) + arenaStartRow) };
	}

	// Draw food.
	inline void Draw()
	{
		SetCursorPosition(position);
		cout << (char)162;
		cout.flush();
	}
};