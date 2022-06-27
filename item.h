#ifndef __Item__
#define __Item__

#include <string>
#include "entity.h"

class Room;

using namespace std;

enum ItemType
{
	COMMON,
	WEAPON,
	ARMOUR,
	COMBINER
};

class Item : public Entity {
public:
	Item(const char* name, const char* description, Entity* parent, ItemType item_type = COMMON);
	~Item();

	void Look() const;
	int GetValue() const;

public:
	ItemType item_type;
	int min_value;
	int max_value;
	Item* comp; // compnent that needs to combine
	Item* full_combination; // Result of combination
};

#endif //__Item__
