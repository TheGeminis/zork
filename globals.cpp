#include "globals.h"


bool Same(const string& a, const string& b)
{
	return _stricmp(a.c_str(), b.c_str()) == 0;
}


bool Same(const char* a, const string& b)
{
	return _stricmp(a, b.c_str()) == 0;
}


bool Same(const string& a, const char* b)
{
	return _stricmp(a.c_str(), b) == 0;
}


void Tokenize(const string& line, vector<string>& arguments)
{
	const char* str = line.c_str();

	do
	{
		const char* begin = str;

		while (*str != ' ' && *str)
			str++;

		arguments.push_back(string(begin, str));
	} while (0 != *str++);
}


int Roll(int min, int max)
{
	return (max > 0) ? min + (rand() % (max - min)) : 0;
}

int Modifiers(string& aura_attacker, string& aura_target) {

	if (aura_attacker != "" && aura_target != "" && aura_attacker != aura_target) {

		int modifier; // 1: x2 damage, 2: %2 damage, 3: 10x damae, 4: 0x damage

		if (aura_attacker == "red")
		{
			if (aura_target == "green") modifier = 1;
			else if (aura_target == "blue") modifier = 2;
			else if (aura_target == "yellow") modifier = 3;
		}

		else if (aura_attacker == "green")
		{
			if (aura_target == "yellow") modifier = 1;
			else if (aura_target == "red") modifier = 2;
			else if (aura_target == "blue") modifier = 3;
		}

		else if (aura_attacker == "yellow") {
			if (aura_target == "blue") modifier = 1;
			else if (aura_target == "green") modifier = 2;
			else if (aura_target == "red") modifier = 4;
		}

		else if (aura_attacker == "blue") {
			if (aura_target == "red") modifier = 1;
			else if (aura_target == "yellow") modifier = 2;
			else if (aura_target == "green") modifier = 4;
		}

		return modifier;
	}

	else return 0;
}