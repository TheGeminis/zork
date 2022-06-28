#include <iostream>
#include "world.h"
#include "globals.h"
#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "creature.h"

using namespace std;


World::World()
{
	tick_timer = clock();

	// Rooms ----
	Room* collapsed = new Room("Collapsed", "You find yourself inside a collapsed tunnel, the ceiling must have collapsed due to your weight.");
	Room* hall = new Room("Hall", "You are inside a great hall, you are surrounded by great columns, small statues, and inscriptions on the walls.");
	Room* chapel = new Room("Chapel", "The Chapel features a single altar in front of a statue depicting a hooded figure praying.");
	Room* vault = new Room("Vault", "The vault contains many pergamins and old rusted paintings on the walls.");
	Room* intersection = new Room("Intersection", "A point where two tunnels meet connecting 4 places.");
	Room* crypt = new Room("Crypt", "You are inside a room that seems to be built more like a prison cell, you have a feeling something doesn't want you here.");
	Room* portal = new Room("Portal", "This room is different from all the other places you have seen, at the center, there is a frame with columns that resemble an entrance. Maybe you can get out through here.");

	Room* devRoom = new Room("devRoom", "You are not meant to be here");

	Exit* ex1 = new Exit("south", "north", "Hall entrance", collapsed, hall);
	Exit* ex2 = new Exit("west", "east", "Decorated entrance", chapel, hall);
	Exit* ex3 = new Exit("north", "west", "Golden gate", vault, hall);
	Exit* ex4 = new Exit("south", "north", "Main tunnel", hall, intersection);
	Exit* ex5 = new Exit("up", "down", "stairs", crypt, intersection);
	Exit* ex6 = new Exit("west", "east", "Golden tunnel", intersection, vault);
	Exit* ex7 = new Exit("south", "north", "Iridescent doorway", intersection, portal);
	
	ex2->locked = true;
	ex4->locked = true;
	ex7->locked = true;

	//Testing aura unlocking feature
	ex1->exit_type = AURA;
	ex1->aura = "red";
	ex1->locked = true;

	entities.push_back(collapsed);
	entities.push_back(hall);
	entities.push_back(chapel);
	entities.push_back(vault);
	entities.push_back(intersection);
	entities.push_back(crypt);
	entities.push_back(portal);

	entities.push_back(devRoom);

	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);
	entities.push_back(ex5);
	entities.push_back(ex6);
	entities.push_back(ex7);

	// Creatures ----
	Creature* skeleton = new Creature("Skeleton", "You don't believe your eyes, it's an esqueleton standing there menacingly", collapsed);
	skeleton->hit_points = 10;
	skeleton->aura = "yellow";

	entities.push_back(skeleton);

	// Items -----
	Item* chest = new Item("Chest", "Looks like it might contain something.", vault);
	Item* key = new Item("Key", "Old iron key.", chest);
	Item* key2 = new Item("Shortcut Key", "This key may help you go somewhere faster.", skeleton);
	Item* device = new Item("Device", "Glows and feels powerful...", devRoom);
	ex2->key = key;
	ex4->key = key2;
	ex7->key = device;

	//Testing aura unlocking feature
	Item* garnet = new Item("Garnet", "A gem that glows with a red light and feels warm to the touch.", collapsed, CHANGER);
	garnet->aura = "blue";

	Item* sword = new Item("Sword", "A simple old and rusty sword.", collapsed, WEAPON);
	sword->min_value = 2;
	sword->max_value = 6;

	Item* mace = new Item("Mace", "A big scary mace", skeleton, WEAPON);
	mace->min_value = 3;
	mace->max_value = 7;
	skeleton->AutoEquip();

	Item* shield = new Item("Shield", "An old wooden shield.", skeleton, ARMOUR);
	shield->min_value = 1;
	shield->max_value = 3;
	skeleton->AutoEquip();

	Item* gem = new Item("Gem", "A small gem, maybe it is of some use...", skeleton, COMBINER);
	Item* stone = new Item("Stone", "An hexagonal shaped stone with a hole in the middle, maybe it is of some use...", chapel, COMBINER);
	gem->comp = stone;
	gem->full_combination = device;
	stone->comp = gem;
	stone->full_combination = device;

	entities.push_back(chest);
	entities.push_back(sword);
	entities.push_back(shield);
	entities.push_back(gem);
	entities.push_back(stone);

	// Player ----
	player = new Player("Explorer", "You are an explorer tasked with surveing some old ruins in the forest.", collapsed);
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

	for (auto it : entities) {
		if (it->name == "Portal" && player->GetRoom() == it) GameFinished = true;
	}
	

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

bool World::IsPlayerAlive() {
	
	return player->IsAlive();
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

		else if (Same(args[0], "use"))
		{
			player->Use(args);
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

		else if (Same(args[0], "combine") || Same(args[0], "comb"))
		{
			player->Combine(args);
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