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
	cout << BROWN_ "\n" << name << "\n" _OFF;
	cout << description;

	// List exits --
	for (auto it : container)
	{
		if (it->type == EXIT)
		{
			Exit* ex = (Exit*)it;
			cout << "\nDirection (" << BROWN_ << ex->GetNameFrom(this) << _OFF << ") you see " << BROWN_  <<ex->GetDestinationFrom(this)->name << _OFF;
		}
	}

	// List items --
	for (auto it : container)
	{
		if (it->type == ITEM)
		{
			Item* item = (Item*)it;
			cout << "\nThere is an item here: " << GREEN_ << item->name << _OFF;
		}
	}

	// List creatures --
	for (auto it : container)
	{
		if (it->type == CREATURE)
		{
			Creature* cr = (Creature*)it;
			cout << "\nThere is someone else here: " << BLUE_ << cr->name << _OFF;
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