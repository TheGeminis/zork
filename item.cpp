#include <iostream>
#include "item.h"

Item::Item(const char* title, const char* description, Entity* parent, ItemType item_type) : 
Entity(title, description, parent), item_type(item_type)
{
}

Item::~Item()
{}