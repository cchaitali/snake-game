#include "Helper.h"
#include "SnakeGame.h"

int main()
{
	// Resize console window to required size.
	MoveWindow(GetConsoleWindow(), 100, 100, 700, 500, TRUE);

	// Hide cursor.
	HideCursor();

	// Keep looping infinitely between starting screen and game screen until user does not close the game.
	while (true)
	{
		// Display start screen.
		ClearScreen();
		cout << "\n  ____              _           ____                       \n";
		cout << " / ___| _ __   __ _| | _____   / ___| __ _ _ __ ___   ___  \n";
		cout << " \\___ \\| '_ \\ / _` | |/ / _ \\ | |  _ / _` | '_ ` _ \\ / _ \\ \n";
		cout << "  ___) | | | | (_| |   <  __/ | |_| | (_| | | | | | |  __/ \n";
		cout << " |____/|_| |_|\\__,_|_|\\_\\___|  \\____|\\__,_|_| |_| |_|\\___| \n";
		cout << "\n\n\n Press any key to start ...";
		cout.flush();
		_getwch();

		// Start the game.
		ClearScreen();
		SnakeGame game;
		game.start();
		_getwch();
	}
	return 0;
}