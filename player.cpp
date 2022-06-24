#include <iostream>
#include "player.h"

Player::Player(const char* title, const char* description, Room* room) :
Creature(title, description, room)
{
	type = PLAYER;
}

Player::~Player()
{}