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
	cout << "\n" << name << "\n";
	cout << description;

	// List exits --
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			cout << "\nDirection (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->name;
		}
	}

	cout << "\n";
}


Exit* Room::GetExit(const string& direction) const
{
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (Same(ex->GetNameFrom(this), direction))
				return ex;
		}
	}

	return NULL;
}