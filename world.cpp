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
	Room* collapsed = new Room("Collapsed tunnel", "You find yourself inside a collapsed tunnel, the ceiling must have collapsed due to your weight.");
	Room* hall = new Room("Hall", "You are inside a great hall, you are surrounded by great columns, small statues, and inscriptions on the walls.");
	Room* chapel = new Room("Chapel", "The Chapel features a single altar in front of a statue depicting a hooded figure praying.");
	Room* vault = new Room("Vault", "The vault contains many pergamins and old rusted paintings on the walls.");
	Room* intersection = new Room("Intersection", "A point where two tunnels meet connecting 4 places.");
	Room* crypt = new Room("Crypt", "You are inside a room that seems to be built more like a prison cell, you have a feeling something doesn't want you here.");
	Room* lab = new Room("Lab", "You are inside a room full of old crystal flasks, boxes and a cauldron in the middle.");
	Room* library = new Room("Library", "You are inside a room full of old bookcases and moldy books.");
	Room* portalRoom = new Room("Portal Room", "This room is different from all the other places you have seen, at the center, there is a frame with columns that resemble an entrance. Maybe you can get out through here.");
	Room* portal = new Room("Portal", "You can exit through here...");

	Room* devRoom = new Room("devRoom", "You are not meant to be here");


	Exit* ex1 = new Exit("south", "north", "Hall entrance", collapsed, hall);
	Exit* ex2 = new Exit("north", "south", "Decorated entrance", chapel, hall);
	Exit* ex3 = new Exit("down", "up", "Main stairs", hall, intersection);
	Exit* ex4 = new Exit("west", "east", "Iridescent doorway", hall, portalRoom);
	Exit* ex5 = new Exit("south", "north", "Golden gate", vault, intersection);
	Exit* ex6 = new Exit("west", "east", "Fuming gate", lab, intersection);
	Exit* ex7 = new Exit("north", "south", "Bony Gate", crypt, intersection);
	Exit* ex8 = new Exit("east", "west", "Wooden door", hall, library);
	Exit* ex9 = new Exit("center", "exterior", "Portal", portalRoom, portal);
	
	
	ex2->exit_type = AURA;
	ex2->aura = "red";
	ex2->locked = true;

	ex5->exit_type = KEY;
	ex5->locked = true;
	
	ex6->exit_type = AURA;
	ex6->aura = "yellow";
	ex6->locked = true;
	
	ex7->exit_type = AURA;
	ex7->aura = "blue";
	ex7->locked = true;

	ex8->exit_type = AURA;
	ex8->aura = "yellow";
	ex8->locked = true;

	ex9->exit_type = KEY;
	ex9->locked = true;


	entities.push_back(collapsed);
	entities.push_back(hall);
	entities.push_back(chapel);
	entities.push_back(vault);
	entities.push_back(intersection);
	entities.push_back(crypt);
	entities.push_back(lab);
	entities.push_back(library);
	entities.push_back(portalRoom);
	entities.push_back(portal);

	entities.push_back(devRoom);

	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);
	entities.push_back(ex5);
	entities.push_back(ex6);
	entities.push_back(ex7);
	entities.push_back(ex8);
	entities.push_back(ex9);


	// Creatures ----
	Creature* skeleton = new Creature("Skeleton", "You don't believe your eyes, it's an esqueleton standing there menacingly.", intersection);
	skeleton->hit_points = 10;
	skeleton->aura = "blue";

	Creature* ghost = new Creature("Ghost", "You feel chills, it's a ghost looking right at you.", library);
	ghost->hit_points = 31;
	ghost->aura = "red";

	Creature* zombie = new Creature("Zombie", "You try not to puke, it's a zombie half decomposed.", crypt);
	zombie->hit_points = 115;
	zombie->aura = "green";

	Creature* witch = new Creature("Witch", "You don't believe your eyes, it a witch laughing maniacally!", lab);
	witch->hit_points = 18;
	witch->aura = "yellow";

	Creature* demon = new Creature("Demon", "You don't believe your eyes, it's a demon from the frozen depths of hell!", chapel);
	demon->hit_points = 666;
	demon->aura = "blue";

	entities.push_back(skeleton);
	entities.push_back(ghost);
	entities.push_back(zombie);
	entities.push_back(witch);
	entities.push_back(demon);


	// Items -----
	Item* chest = new Item("Chest", "Looks like it might contain something.", vault);
	Item* key = new Item("Key", "Old iron key.", portalRoom);
	Item* device = new Item("Device", "Glows and feels powerful...", devRoom);
	
	ex5->key = key;
	ex9->key = device;

	Item* garnet = new Item("Garnet", "A gem that glows with a red light and feels warm to the touch.", ghost, CHANGER);
	Item* opal = new Item("Opal", "A gem that glows with a blue light and feels cold to the touch.", skeleton, CHANGER);
	Item* jade = new Item("Jade", "A gem that glows with a green light and feels pulsating with life.", zombie, CHANGER);
	Item* pearl = new Item("Pearl", "A gem that glows with a yellow light and makes you feel tingles while touching it.", chest, CHANGER);
	
	garnet->aura = "red";
	opal->aura = "blue";
	jade->aura = "green";
	pearl->aura = "yellow";

	Item* sword = new Item("Sword", "A simple old and rusty sword.", chest, WEAPON);
	sword->min_value = 2;
	sword->max_value = 6;

	Item* mace = new Item("Mace", "A big scary mace", skeleton, WEAPON);
	mace->min_value = 4;
	mace->max_value = 8;
	skeleton->AutoEquip();

	Item* bone = new Item("Bone", "A half eaten bone", zombie, WEAPON);
	bone->min_value = 0;
	bone->max_value = 1;
	zombie->AutoEquip();

	Item* chandelier = new Item("Chandelier", "An old yet supresingly sturdy chandelier lit with fire.", ghost, WEAPON);
	chandelier->min_value = 4;
	chandelier->max_value = 10;
	ghost->AutoEquip();

	Item* wand = new Item("Wand", "A sparkly wand that emits energy.", witch, WEAPON);
	wand->min_value = 8;
	wand->max_value = 88;
	witch->AutoEquip();
	
	Item* axe = new Item("Axe", "A giant frozen axe.", demon, WEAPON);
	axe->min_value = 10;
	axe->max_value = 30;
	demon->AutoEquip();

	Item* shield = new Item("Shield", "An old wooden shield.", skeleton, ARMOUR);
	shield->min_value = 1;
	shield->max_value = 3;
	skeleton->AutoEquip();

	Item* encyclopedia = new Item("Encyclopedia", "An old giant book that does a surprisingly good job as a shield.", ghost, ARMOUR);
	encyclopedia->min_value = 3;
	encyclopedia->max_value = 7;
	ghost->AutoEquip();

	Item* headstone = new Item("Headstone", "A big piece of stone with some engravings.", zombie, ARMOUR);
	headstone->min_value = 10;
	headstone->max_value = 20;
	zombie->AutoEquip();

	Item* gem = new Item("Gem", "A small gem, maybe it is of some use...", witch, COMBINER);
	Item* stone = new Item("Stone", "An hexagonal shaped stone with a hole in the middle, maybe it is of some use...", demon, COMBINER);
	gem->comp = stone;
	gem->full_combination = device;
	stone->comp = gem;
	stone->full_combination = device;

	//entities.push_back(chest);
	//entities.push_back(key);
	//entities.push_back(sword);
	//entities.push_back(shield);
	//entities.push_back(gem);
	//entities.push_back(stone);

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