#include <iostream>
#include "globals.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "player.h"

Player::Player(const char* title, const char* description, Room* room) :
Creature(title, description, room)
{
	type = PLAYER;
}

Player::~Player()
{}

void Player::Look(const vector<string>& args) const
{
	if (args.size() > 1)
	{
		for (auto it : parent->container)
		{
			if (Same(it->name, args[1]) || (it->type == EXIT && Same(args[1], ((Exit*)it)->GetNameFrom((Room*)parent))))
			{
				it->Look();
				return;
			}
		}

		if (Same(args[1], "me"))
		{
			cout << "\n" << name << "\n";
			cout << description << "\n";
		}
	}
	else
	{
		parent->Look();
	}
}


bool Player::Go(const vector<string>& args)
{
	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if (exit->locked) {
		
		if (exit->exit_type == KEY)
		{
			cout << "\nThat exit is locked. A key may open it...\n";
			return false;
		}

		if (exit->exit_type == AURA)
		{
			cout << "\nThat exit is locked. A strange dim " << exit->aura << " light sorrounds it...\n";
			return false;
		}
	}

	cout << "\nYou take direction " << exit->GetNameFrom((Room*)parent) << "...\n";
	ChangeParentTo(exit->GetDestinationFrom((Room*)parent));
	parent->Look();

	return true;
}



bool Player::Take(const vector<string>& args)
{
	if (args.size() == 4)
	{
		Item* item = (Item*)parent->Find(args[3], ITEM);

		if (item == NULL)
			item = (Item*)Find(args[3], ITEM);

		if (item == NULL)
		{
			cout << "\nCannot find '" << args[3] << "' in this room or in your inventory.\n";
			return false;
		}

		Item* subitem = (Item*)item->Find(args[1], ITEM);

		if (subitem == NULL)
		{
			cout << "\n" << item->name << " does not contain '" << args[1] << "'.\n";
			return false;
		}

		cout << "\nYou take " << subitem->name << " from " << item->name << ".\n";
		subitem->ChangeParentTo(this);
	}
	else if (args.size() == 2)
	{
		Item* item = (Item*)parent->Find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\nThere is no item here with that name.\n";
			return false;
		}

		cout << "\nYou take " << item->name << ".\n";
		item->ChangeParentTo(this);
	}

	return false;
}


void Player::Inventory() const
{
	list<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0)
	{
		cout << "\nYou do not own any item.\n";
		return;
	}

	for (auto it : items)
	{
		if (it == weapon)
			cout << "\n" << it->name << " (as weapon)";
		else if (it == armour)
			cout << "\n" << it->name << " (as armour)";
		else
			cout << "\n" << it->name;
	}

	cout << "\n";
}


bool Player::Drop(const vector<string>& args)
{
	if (args.size() == 2)
	{
		Item* item = (Item*)Find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\nThere is no item on you with that name.\n";
			return false;
		}

		cout << "\nYou drop " << item->name << "...\n";
		item->ChangeParentTo(parent);

		return true;
	}
	else if (args.size() == 4)
	{
		Item* item = (Item*)Find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\nCan not find '" << args[1] << "' in your inventory.\n";
			return false;
		}

		Item* container = (Item*)parent->Find(args[3], ITEM);

		if (container == NULL)
		{
			container = (Item*)Find(args[3], ITEM);
			cout << "\nCan not find '" << args[3] << "' in your inventory or in the room.\n";
			return false;
		}

		cout << "\nYou put " << item->name << " into " << container->name << ".\n";
		item->ChangeParentTo(container);

		return true;
	}

	return false;
}


bool Player::Equip(const vector<string>& args)
{
	Item* item = (Item*)Find(args[1], ITEM);

	if (item == NULL)
	{
		cout << "\nCannot find '" << args[1] << "' is not in your inventory.\n";
		return false;
	}

	switch (item->item_type)
	{
	case WEAPON:
		weapon = item;
		break;

	case ARMOUR:
		armour = item;
		break;

	default:
		cout << "\n" << item->name << " cannot be equipped.\n";
		return false;
	}

	cout << "\nYou equip " << item->name << "...\n";

	return true;
}


bool Player::UnEquip(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)Find(args[1], ITEM);

	if (item == NULL)
	{
		cout << "\n" << item->name << " is not in your inventory.\n";
		return false;
	}

	if (item == weapon)
		weapon = NULL;
	else if (item == armour)
		armour = NULL;
	else
	{
		cout << "\n" << item->name << " is not equipped.\n";
		return false;
	}

	cout << "\nYou un-equip " << item->name << "...\n";

	return true;
}


bool Player::Examine(const vector<string>& args) const
{
	Creature* target = (Creature*)parent->Find(args[1], CREATURE);

	if (target == NULL)
	{
		cout << "\n" << args[1] << " is not here.\n";
		return false;
	}

	target->Inventory();
	target->Stats();

	return true;
}


bool Player::Attack(const vector<string>& args)
{
	Creature* target = (Creature*)parent->Find(args[1], CREATURE);

	if (target == NULL)
	{
		cout << "\n" << args[1] << " is not here.";
		return false;
	}

	else if (((weapon) ? weapon->max_value : max_damage) == 0) {
		cout << "\nYou don't have damage!\n";
		return false;
	}

	else {
		
		if (DamageWarning(target->aura, this->aura)) {
			
			cout << "\nDo you still want to attack?\n";

			string response = "";
			cin >> response;

			if (Same(response, "no") || Same(response, "n"))
			{
				cout << "\nYou back away slowly...\n";
				return false;
			}

			else if (!Same(response, "yes") && !Same(response, "y")) {
				
				cout << "\nIf you can't respond a simple yes or no question in your head, maybe you sould not attempt to fight a real fight in the real world...\n";
				cout << "\nYou back away slowly...\n";
				return false;
			}
		}

		combat_target = target;
		cout << "\nYou jump to attack " << target->name << "!\n";
		return true;
	}
}


bool Player::Loot(const vector<string>& args)
{
	Creature* target = (Creature*)parent->Find(args[1], CREATURE);

	if (target == NULL)
	{
		cout << "\n" << args[1] << " is not here.\n";
		return false;
	}

	if (target->IsAlive() == true)
	{
		cout << "\n" << target->name << " cannot be looted until it is killed.\n";
		return false;
	}

	list<Entity*> items;
	target->FindAll(ITEM, items);

	if (items.size() > 0)
	{
		cout << "\nYou loot " << target->name << "'s corpse:\n";

		for (auto it : items)
		{
			Item* i = (Item*)it;
			cout << "You find: " << i->name << "\n";
			i->ChangeParentTo(this);
		}
	}
	else
		cout << "\nYou loot " << target->name << "'s corpse, but find nothing there.\n";

	return true;
}


bool Player::Lock(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if (exit->locked == true)
	{
		cout << "\nThat exit is already locked.\n";
		return false;
	}

	Item* item = (Item*)Find(args[3], ITEM);

	if (item == NULL)
	{
		cout << "\nItem '" << args[3] << "' not found in your inventory.\n";
		return false;
	}

	if (exit->key != item)
	{
		cout << "\nItem '" << item->name << "' is not the key for " << exit->GetNameFrom((Room*)parent) << ".\n";
		return false;
	}

	cout << "\nYou lock " << exit->GetNameFrom((Room*)parent) << "...\n";

	exit->locked = true;

	return true;
}


bool Player::UnLock(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if (exit->locked == false)
	{
		cout << "\nThat exit is not locked.\n";
		return false;
	}

	if (Same(args[3], "aura")) {
		
		if (exit->exit_type != AURA) {
			cout << "\nThat exit does not test your soul.\n";
			return false;
		}

		cout << "\nDo you want to offer your soul?\n";
		
		string response = "";
		cin >> response;

		if (Same(response, "no") || Same(response, "n"))
		{
			cout << "\nCome back when you feel brave enough to offer your soul then...\n";
			return false;
		}

		if (Same(response, "yes") || Same(response, "y")) {
			
			if (!Same(this->aura, exit->aura)) {
				cout << "\nYour soul is not worthy! Suffer the punishment!\n";
				cout << "\nYou take 1 damage!\n";
				this->hit_points -= 1;
				return false;
			}
		}

		else {
			cout << "\nCome back when you learn how to respond a simple yes or no question...\n";
			return false;
		}
	}

	else {

		Item* item = (Item*)Find(args[3], ITEM);

		if (item == NULL)
		{
			cout << "\nKey '" << args[3] << "' not found in your inventory.\n";
			return false;
		}

		if (exit->key != item)
		{
			cout << "\nKey '" << item->name << "' is not the key for " << exit->GetNameFrom((Room*)parent) << ".\n";
			return false;
		}
	}

	cout << "\nYou unlock " << exit->GetNameFrom((Room*)parent) << "...\n";

	exit->locked = false;

	return true;
}


bool Player::Combine(const vector<string>& args) {
	if (!IsAlive()) return false;

	Item* comp1 = (Item*)Find(args[1], ITEM);
	Item* comp2 = (Item*)Find(args[3], ITEM);
	
	if (comp1 == NULL) {
		cout << "\nObject '" << args[1] << "' not found in your inventory.\n";
		return false;
	}

	if (comp2 == NULL) {
		cout << "\nObject '" << args[3] << "' not found in your inventory.\n";
		return false;
	}

	if (comp1->name != "Gem" && comp2->name != "Gem") {
		cout << "\nCannot combine these objects.\n";
		return false;
	}

	if (comp1->name != "Stone" && comp2->name != "Stone") {
		cout << "\nCannot combine these objects.\n";
		return false;
	}

	Room* devRoom = (Room*)Find("DevRoom", ROOM);
	Item* device = comp1->full_combination;
	
	cout << "\nYou combine " << args[1] << " and " << args[3] << "\n";
	cout << "\nYou made " << device->name << "!\n";
	cout << "\n" << device->description << "\n";
	
	comp1->ChangeParentTo(devRoom);
	comp2->ChangeParentTo(devRoom);
	device->ChangeParentTo(this);

	return true;
}


bool Player::Use(const vector<string>& args)
{
	if (!IsAlive()) return false;
	
	Item* item = (Item*)Find(args[1], ITEM);

	if (item == NULL)
	{
		cout << "\nObject '" << args[1] << "' not found in your inventory.\n";
		return false;
	}

	if (item->item_type != CHANGER)
	{
		cout << "\nObject '" << args[1] << "' doesn't seem to have any effect.\n";
		return false;
	}

	cout << "\nSomething is happening...\n";
	this->aura = item->aura;
	cout << "\nA " << item->aura << " colored light sorrounds you...\n";
}

bool Player::DamageWarning(string& aura_opponent, string& aura_player) {
	
	int modifier = Modifiers(aura_opponent, aura_player);

	if (modifier <= 0) return false;

	else {

		cout << "\nYour " << aura_player << " aura reacts with the " << aura_opponent << " aura from this being\n";

		if (modifier == 1) cout << "\nIt feels more powerful than you...\n";
		else if (modifier == 2) cout << "\nIt feels less powerful than you...\n";
		else if (modifier == 3) cout << "\nThis foe is beyond any of your skills... Run!!!\n";
		else cout << "\nYou feel like a god compared to this thing...\n";

		return true;
	}
}