#include <iostream>
#include "room.h"

Room::Room() : Entity(title, description, (Entity*)room)
{
}

Room::~Room()
{}