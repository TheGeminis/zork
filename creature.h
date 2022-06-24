#ifndef __Creature__
#define __Creature__

#include "entity.h"

class Room;

using namespace std;

class Creature : public Entity {
public:
	Creature(const char* name, const char* description, Room* room);
	~Creature();
};

#endif //__Creature__