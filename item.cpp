#include <iostream>
#include "item.h"
#include "globals.h"


Item::Item(const char* title, const char* description, Entity* parent, ItemType item_type) : 
Entity(title, description, parent), item_type(item_type)
{
}


Item::~Item()
{}


void Item::Look() const
{
	cout << "\n" << name << "\n";
	cout << description << "\n";

	list<Entity*> stuff;
	FindAll(ITEM, stuff);

	if (stuff.size() > 0)
	{
		cout << "It contains: " << "\n";
		for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.cend(); ++it)
			cout << (*it)->name << "\n";
	}
}


int Item::GetValue() const
{
	return Roll(min_value, max_value);
}