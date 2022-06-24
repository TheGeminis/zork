#include <iostream>
#include "creature.h"

Creature::Creature(const char* title, const char* description, Room* room) : 
Entity(title, description, (Entity*)room)
{
}

Creature::~Creature()
{}