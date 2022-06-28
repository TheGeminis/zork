#ifndef __Exit__
#define __Exit__

#include "entity.h"
#include <string>

class Room;

using namespace std;

enum ExitType {
	KEY,
	AURA,
	NONE
};

class Exit : public Entity
{
public:
	Exit(const char* name, const char* opposite_name, const char* description, Room* origin, Room* destination, bool one_way = false);
	~Exit();
	
	void Look() const;
	const string& GetNameFrom(const Room* room) const;
	Room* GetDestinationFrom(const Room* room) const;

public:
	bool one_way;
	bool closed;
	bool locked;
	string opposite_name;
	Room* destination;
	
	Entity* key;
	string aura;
	
	ExitType exit_type;
};

#endif //__Exit__
