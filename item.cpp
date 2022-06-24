#include <iostream>
#include "item.h"

Item::Item() : Entity(title, description, (Entity*)room)
{
}

Item::~Item()
{}