#include <iostream>
#include "world.h"
#include "globals.h"
#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "creature.h"
//#include <algorithm>

using namespace std;


World::World()
{
	tick_timer = clock();

	// Rooms ----
	Room* collapsed = new Room("Collapsed", "You find yourself inside a collapsed tunnel, the cealing must had collapsed due to your weight.");
	Room* hall = new Room("Hall", "You are inside a great hall, you are surrounded by great columns, small statues and inscriptions on the walls.");
	Room* temple = new Room("Temple", "The temple features a single altar in front of a statue depicting a hooded figure praying.");
	Room* vault = new Room("Vault", "The vault contains many pergamins and old rusted paintings on the walls.");
	Room* intersection = new Room("Intersection", "A point where two tunnels meet connecting 4 places.");
	Room* crypt = new Room("Crypt", "You are inside a room that seems to be build more like a prison cell, you have a feeling something doesn't want you here.");
	Room* portal = new Room("Portal", "This room is different to all the other places you have seen, at the center there is a frame with columns that resemble an entrance. Maybe you can get out through here.");

	Exit* ex1 = new Exit("south", "north", "Hall entrance", collapsed, hall);
	Exit* ex2 = new Exit("west", "east", "Decorated entrance", temple, hall);
	Exit* ex3 = new Exit("north", "west", "Golden gate", vault, hall);
	Exit* ex4 = new Exit("south", "north", "Main tunnel", hall, intersection);
	Exit* ex5 = new Exit("up", "down", "stairs", crypt, intersection);
	Exit* ex6 = new Exit("west", "east", "Golden tunnel", intersection, vault);
	Exit* ex7 = new Exit("south", "north", "Iridescent doorway", intersection, portal);

	ex2->locked = true;
	ex4->locked = true;

	entities.push_back(collapsed);
	entities.push_back(hall);
	entities.push_back(temple);
	entities.push_back(vault);
	entities.push_back(intersection);
	entities.push_back(crypt);
	entities.push_back(portal);

	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);
	entities.push_back(ex5);
	entities.push_back(ex6);
	entities.push_back(ex7);

	// Creatures ----
	Creature* butler = new Creature("Butler", "It's James, the house Butler.", hall);
	butler->hit_points = 10;

	entities.push_back(butler);

	// Items -----
	Item* mailbox = new Item("Mailbox", "Looks like it might contain something.", vault);
	Item* key = new Item("Key", "Old iron key.", mailbox);
	ex2->key = key;

	Item* sword = new Item("Sword", "A simple old and rusty sword.", collapsed, WEAPON);
	sword->min_value = 2;
	sword->max_value = 6;

	Item* sword2(sword);
	sword2->parent = butler;

	Item* shield = new Item("Shield", "An old wooden shield.", butler, ARMOUR);
	shield->min_value = 1;
	shield->max_value = 3;
	butler->AutoEquip();

	entities.push_back(mailbox);
	entities.push_back(sword);
	entities.push_back(shield);

	// Player ----
	player = new Player("Hero", "You are an awesome adventurer!", collapsed);
	player->hit_points = 25;
	entities.push_back(player);
}

World::~World()
{
	for (auto it : entities) delete it;
	entities.clear();
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
		for (auto it : entities) it->Tick();

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
			player->Look(args);
		}
		else if (Same(args[0], "north") || Same(args[0], "n"))
		{
			(args.size() == 1) ? args.push_back("north") : args[1] = "north";
			player->Go(args);
		}
		else if (Same(args[0], "south") || Same(args[0], "s"))
		{
			(args.size() == 1) ? args.push_back("south") : args[1] = "south";
			player->Go(args);
		}
		else if (Same(args[0], "east") || Same(args[0], "e"))
		{
			(args.size() == 1) ? args.push_back("east") : args[1] = "east";
			player->Go(args);
		}
		else if (Same(args[0], "west") || Same(args[0], "w"))
		{
			(args.size() == 1) ? args.push_back("west") : args[1] = "west";
			player->Go(args);
		}
		else if (Same(args[0], "up") || Same(args[0], "u"))
		{
			(args.size() == 1) ? args.push_back("up") : args[1] = "up";
			player->Go(args);
		}
		else if (Same(args[0], "down") || Same(args[0], "d"))
		{
			(args.size() == 1) ? args.push_back("down") : args[1] = "down";
			player->Go(args);
		}
		else if (Same(args[0], "stats") || Same(args[0], "st"))
		{
			player->Stats();
		}
		else if (Same(args[0], "inventory") || Same(args[0], "i"))
		{
			player->Inventory();
		}
		else
			ret = false;
		break;
	}
	case 2: // commands with one argument ------------------------------
	{
		if (Same(args[0], "look") || Same(args[0], "l"))
		{
			player->Look(args);
		}
		else if (Same(args[0], "go"))
		{
			player->Go(args);
		}
		else if (Same(args[0], "take") || Same(args[0], "pick"))
		{
			player->Take(args);
		}
		else if (Same(args[0], "drop") || Same(args[0], "put"))
		{
			player->Drop(args);
		}
		else if (Same(args[0], "equip") || Same(args[0], "eq"))
		{
			player->Equip(args);
		}
		else if (Same(args[0], "unequip") || Same(args[0], "uneq"))
		{
			player->UnEquip(args);
		}
		else if (Same(args[0], "examine") || Same(args[0], "ex"))
		{
			player->Examine(args);
		}
		else if (Same(args[0], "attack") || Same(args[0], "at"))
		{
			player->Attack(args);
		}
		else if (Same(args[0], "loot") || Same(args[0], "lt"))
		{
			player->Loot(args);
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
			player->UnLock(args);
		}
		else if (Same(args[0], "lock") || Same(args[0], "lk"))
		{
			player->Lock(args);
		}
		else if (Same(args[0], "take") || Same(args[0], "pick"))
		{
			player->Take(args);
		}
		else if (Same(args[0], "drop") || Same(args[0], "put"))
		{
			player->Drop(args);
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