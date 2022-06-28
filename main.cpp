#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include "world.h"
#include "globals.h"

using namespace std;


int main()
{
	char key;
	string player_input;
	vector<string> args;
	args.reserve(10); //command with more than 10 arguments is not expected
	
	cout << WHITE_ "Welcome to MyZork!\n" _OFF;
	cout << "----------------\n";
	cout << "You awake from a big fall after the floor below you collapses when you were exploring an old ruin.\n";
	World MyWorld;

	args.push_back("look");

	while (1)
	{
		if (_kbhit() != 0)
		{
			key = _getch();
			if (key == '\b') // backspace
			{
				if (player_input.length() > 0)
				{
					player_input.pop_back();
					cout << '\b';
					cout << " ";
					cout << '\b';
				}
			}
			else if (key != '\r') // return
			{
				player_input += key;
				cout << key;
			}
			else
				Tokenize(player_input, args);
		}

		if (MyWorld.GameFinished) {
			cout << endl << WHITE_ "You did it, you escaped!\nCongratulations!" _OFF;
			break;
		}

		if (args.size() > 0 && Same(args[0], "quit"))
			break;

		if (MyWorld.Tick(args) == false)
			cout << "\nSorry, I do not understand your command.\n";

		if (args.size() > 0)
		{
			args.clear();
			player_input = "";
			cout << "> ";
		}
	}

	cout << WHITE_ "\nThanks for playing, Bye!\n" _OFF;
	return 0;
}
