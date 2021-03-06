#ifndef __Player__
#define __Player__

#include "creature.h"
#include <vector>

using namespace std;

class Player : public Creature {
public:
	Player(const char* name, const char* description, Room* room);
	~Player();

	bool Go(const vector<string>& args);
	void Look(const vector<string>& args) const;
	bool Take(const vector<string>& args);
	bool Drop(const vector<string>& args);
	void Inventory() const;
	bool Equip(const vector<string>& args);
	bool UnEquip(const vector<string>& args);
	bool Examine(const vector<string>& args) const;
	bool Attack(const vector<string>& args);
	bool Loot(const vector<string>& args);
	bool Lock(const vector<string>& args);
	bool UnLock(const vector<string>& args);
	bool Combine(const vector<string>& args);
	bool Use(const vector<string>& args);
	bool DamageWarning(string& aura_opponent, string& aura_player);
};

#endif //__Player__
