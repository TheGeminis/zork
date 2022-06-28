#include <iostream>
#include "room.h"
#include "exit.h"
#include "item.h"
#include "globals.h"
#include "creature.h"

Room::Room(const char* title, const char* description) :
	Entity(title, description, NULL)
{
	type = ROOM;
}


Room::~Room()
{
}


void Room::Look() const
{
	cout <<"\n" << name << "\n";
	cout << description;

	// List exits --
	for (auto it : container)
	{
		if (it->type == EXIT)
		{
			Exit* ex = (Exit*)it;
			cout << "\nDirection (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->name;
		}
	}

	// List items --
	for (auto it : container)
	{
		if (it->type == ITEM)
		{
			Item* item = (Item*)it;
			cout << "\nThere is an item here: " << item->name;
		}
	}

	// List creatures --
	for (auto it : container)
	{
		if (it->type == CREATURE)
		{
			Creature* cr = (Creature*)it;
			cout << "\nThere is someone else here: " << cr->name;
			if (cr->IsAlive() == false)
				cout << " (dead)";
		}
	}

	cout << "\n";
}


Exit* Room::GetExit(const string& direction) const
{
	for (auto it : container)
	{
		if (it->type == EXIT)
		{
			Exit* ex = (Exit*)it;
			if (Same(ex->GetNameFrom(this), direction))
				return ex;
		}
	}

	return NULL;
}