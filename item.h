#ifndef __Item__
#define __Item__

#include "entity.h"

class Room;

using namespace std;

enum ItemType
{
	COMMON,
	WEAPON,
	ARMOUR
};

class Item : public Entity {
public:
	Item(const char* name, const char* description, Entity* parent, ItemType item_type = COMMON);
	~Item();

public:
	ItemType item_type;
};

#endif //__Item__
