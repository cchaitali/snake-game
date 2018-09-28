#pragma once

#include "Helper.h"

class Snake
{
private:
	COORD head, prevTail;
	int bodyLength;
	vector<COORD> body;
	int arenaStartRow, arenaStartCol, arenaEndRow, arenaEndCol;
	bool hasCollided;
	Direction direction;

public:
	Snake()
	{
		head = prevTail = { -1, -1 };
		bodyLength = 0;
		hasCollided = false;
		direction = STOPPED;
	}

	// Sets arena position and sets starting head position.
	inline void SetArenaPosition(int startRow, int startCol, int endRow, int endCol)
	{
		arenaStartRow = startRow;
		arenaStartCol = startCol;
		arenaEndRow = endRow;
		arenaEndCol = endCol;
		head = { (SHORT)(startCol + (endCol - startCol) / 2), (SHORT)(startRow + (endRow - startRow) / 2) };
	}

	// Returns true if snake has collided with itself.
	inline bool Collided()
	{
		return hasCollided;
	}

	// Sets the direction of movement of snake.
	inline void SetDirection(Direction newDirection)
	{
		// Fancy way to check if new direction is not exactly opposite to the correct direction.
		// We don't want snake to turn by 180 degrees.
		if ((direction != STOPPED) && ((((int)direction - 1) + 2) % (NUM_DIRECTIONS - 1) + 1 == (int)newDirection))
			return;
		direction = newDirection;
	}

	// Returns position of snake's head.
	inline COORD GetHeadPosition()
	{
		return head;
	}

	// Returns length of snake's body (does not include head).
	inline int GetLength()
	{
		return bodyLength;
	}

	// Draws snake.
	inline void Draw()
	{
		// Store the position of current tail because if snake eats food, we need to increase its length.
		// So, we should know where two draw new piece of body.
		prevTail = (bodyLength > 0) ? body[bodyLength - 1] : head;

		// Erase tail (last piece of body).
		SetCursorPosition((bodyLength > 0) ? body[bodyLength - 1] : head);
		cout << ' ';
		cout.flush();

		// Shift pieces of body by one position.
		for (int i = bodyLength - 1; i > 0; i--)
			body[i] = body[i - 1];
		if (bodyLength > 0)
		{
			body[0] = head;

			SetCursorPosition(head);
			cout << 'o';
			cout.flush();
		}

		// Update head's new position based on the direction.
		switch (direction)
		{
		case UP:
			head.Y--;
			break;
		case LEFT:
			head.X--;
			break;
		case DOWN:
			head.Y++;
			break;
		case RIGHT:
			head.X++;
			break;
		default:
			break;
		}

		// Uncomment this if snake can collide with walls of arena.
		/*if ((head.X < arenaStartCol) || (head.X > arenaEndCol) || (head.Y < arenaStartRow) || (head.Y > arenaEndRow))
		{
			hasCollided = true;
			return;
		}*/

		// If snake reaches a wall, it will come through exactly opposite wall.
		// Comment this if snake can collide with walls of arena.
		if (head.X < arenaStartCol)
			head.X = arenaEndCol;
		else if (head.X > arenaEndCol)
			head.X = arenaStartCol;
		if (head.Y < arenaStartRow)
			head.Y = arenaEndRow;
		else if (head.Y > arenaEndRow)
			head.Y = arenaStartRow;

		// Draw head.
		SetCursorPosition(head);
		cout << (char)153;
		cout.flush();

		// Check if snake has collided with its own body. If yes, then we set hasCollided to true to indicate
		// that the game is over.
		for (int i = 0; i < bodyLength; i++)
		{
			if ((head.X == body[i].X) && (head.Y == body[i].Y))
			{
				hasCollided = true;
				return;
			}
		}
	}

	// Increase snake's length by one.
	inline void IncreaseLength()
	{
		body.push_back(prevTail);
		bodyLength++;

		SetCursorPosition(prevTail);
		cout << 'o';
		cout.flush();
	}
};