#ifndef __Room__
#define __Room__

#include <string>
#include "entity.h"

class Exit;

using namespace std;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	~Room();

	void Look() const;

	Exit* GetExit(const string& direction) const;

public:
};

#endif //__Room__
