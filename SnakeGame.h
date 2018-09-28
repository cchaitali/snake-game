#pragma once

#include "Helper.h"
#include "Snake.h"
#include "Food.h"

class SnakeGame
{
private:
	int width, height;
	int firstRow, firstCol;
	Snake snake;
	Food food;
	int score;

	// Draws game arena where snake will move.
	inline void DrawArena()
	{
		cout << " Score: 0\n\n";
		cout << ' ' << (char)201;
		for (int i = 1; i <= width; i++)
			cout << (char)205;
		cout << (char)187 << '\n';
		for (int i = 1; i <= height; i++)
		{
			cout << ' ' << (char)186;
			for (int j = 1; j <= width; j++)
				cout << ' ';
			cout << (char)186 << '\n';
		}
		cout << ' ' << (char)200;
		for (int i = 1; i <= width; i++)
			cout << (char)205;
		cout << (char)188 << '\n';
		cout << "\n Controls: \n";
		cout << " W - Move up, S - Mode down, A - Move left, D - Move right";
		cout.flush();
	}

	// Checks if user pressed a key. If correct key is pressed, tells snake to change its direction.
	inline void ReadInput()
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':
			case 'W':
				snake.SetDirection(UP);
				break;
			case 'a':
			case 'A':
				snake.SetDirection(LEFT);
				break;
			case 's':
			case 'S':
				snake.SetDirection(DOWN);
				break;
			case 'd':
			case 'D':
				snake.SetDirection(RIGHT);
				break;
			default:
				break;
			}
		}
	}

	// Checks if snake has eaten food (i.e. if head of snake overlaps with food).
	inline bool HasSnakeEatenFood()
	{
		COORD snakeHeadPosition = snake.GetHeadPosition();
		COORD foodPosition = food.GetPosition();
		if ((snakeHeadPosition.X == foodPosition.X) && (snakeHeadPosition.Y == foodPosition.Y))
			return true;
		return false;
	}

public:
	SnakeGame()
	{
		srand((unsigned int)time(NULL));

		width = 50;
		height = 20;
		firstRow = 2;
		firstCol = 1;
		score = 0;

		// Draw game arena.
		DrawArena();

		// Send arena position to snake and food.
		snake.SetArenaPosition(firstRow + 1, firstCol + 1, firstRow + height, firstCol + width);
		food.SetArenaPosition(firstRow + 1, firstCol + 1, firstRow + height, firstCol + width);
	}

	// Runs the main game loop.
	inline void start()
	{
		// Generate new food.
		food.Generate();

		// Run the loop while snake has not collided with itself.
		while (!snake.Collided())
		{
			// Read user input to change snake's direction.
			ReadInput();

			// Update snake location and redraw snake and food.
			// We redraw food every time we draw snake, because if the food overlaps with snake's body,
			// we want the food to be visible to the user through snake's body.
			snake.Draw();
			food.Draw();

			// If snake has eaten food, then we increase snake's length and generate new food.
			if (HasSnakeEatenFood())
			{
				snake.IncreaseLength();
				food.Generate();
			}

			// Update the score.
			int length = snake.GetLength();
			if (score < length * 10)
			{
				score = 10 * length;
				SetCursorPosition({ 8, 0 });
				cout << score;
				cout.flush();
			}

			Sleep(100);
		}

		SetCursorPosition({ (SHORT)(firstCol + width / 2 - 6), (SHORT)(firstRow + height / 2) });
		cout << "Game Over!!!";
		cout.flush();
	}
};