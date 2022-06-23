#include <iostream>
#include "world.h"
#include "globals.h"

using namespace std;


World::World()
{
	tick_timer = clock();
}

World::~World()
{
}

bool World::Tick(vector<string>& args)
{
	bool ret = true;

	if (args.size() > 0 && args[0].length() > 0)
		ret = ParseCommand(args);

	GameLoop();

	return ret;
}

void World::GameLoop()
{
	clock_t now = clock();

	if ((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
	{
		tick_timer = now;
	}
}

bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;

	switch (args.size())
	{
	case 1: // commands with no arguments ------------------------------
	{
		if (Same(args[0], "look") || Same(args[0], "l"))
		{
			cout << "command was look\n";
		}
		else if (Same(args[0], "north") || Same(args[0], "n"))
		{
			cout << "command was go north\n";
		}
		else if (Same(args[0], "south") || Same(args[0], "s"))
		{
			cout << "command was go south\n";
		}
		else if (Same(args[0], "east") || Same(args[0], "e"))
		{
			cout << "command was go east\n";
		}
		else if (Same(args[0], "west") || Same(args[0], "w"))
		{
			cout << "command was go west\n";
		}
		else if (Same(args[0], "up") || Same(args[0], "u"))
		{
			cout << "command was go up\n";
		}
		else if (Same(args[0], "down") || Same(args[0], "d"))
		{
			cout << "command was go down\n";
		}
		else if (Same(args[0], "stats") || Same(args[0], "st"))
		{
			cout << "command was stats\n";
		}
		else if (Same(args[0], "inventory") || Same(args[0], "i"))
		{
			cout << "command was inventory\n";
		}
		else
			ret = false;
		break;
	}
	case 2: // commands with one argument ------------------------------
	{
		if (Same(args[0], "look") || Same(args[0], "l"))
		{
			cout << "command was look with one argument\n";
		}
		else if (Same(args[0], "go"))
		{
			cout << "command was go with one argument\n";
		}
		else if (Same(args[0], "take") || Same(args[0], "pick"))
		{
			cout << "command was take with one argument\n";
		}
		else if (Same(args[0], "drop") || Same(args[0], "put"))
		{
			cout << "command was drop with one argument\n";
		}
		else if (Same(args[0], "equip") || Same(args[0], "eq"))
		{
			cout << "command was equip with one argument\n";
		}
		else if (Same(args[0], "unequip") || Same(args[0], "uneq"))
		{
			cout << "command was unequip with one argument\n";
		}
		else if (Same(args[0], "examine") || Same(args[0], "ex"))
		{
			cout << "command was examine with one argument\n";
		}
		else if (Same(args[0], "attack") || Same(args[0], "at"))
		{
			cout << "command was attack with one argument\n";
		}
		else if (Same(args[0], "loot") || Same(args[0], "lt"))
		{
			cout << "command was loot with one argument\n";
		}
		else
			ret = false;
		break;
	}
	case 3: // commands with two arguments ------------------------------
	{
		break;
	}
	case 4: // commands with three arguments ------------------------------
	{
		if (Same(args[0], "unlock") || Same(args[0], "unlk"))
		{
			cout << "command was unlock with three argument\n";
		}
		else if (Same(args[0], "lock") || Same(args[0], "lk"))
		{
			cout << "command was lock with three argument\n";
		}
		else if (Same(args[0], "take") || Same(args[0], "pick"))
		{
			cout << "command was take with three argument\n";
		}
		else if (Same(args[0], "drop") || Same(args[0], "put"))
		{
			cout << "command was drop with three argument\n";
		}
		else
			ret = false;
		break;
	}
	default:
		ret = false;
	}

	return ret;
}