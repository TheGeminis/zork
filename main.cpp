#include <iostream>
#include "world.h"

using namespace std;

#define WHITE_ "\033[1;36m"
#define _WHITE "\033[0m"

int main()
{
	cout << WHITE_ "Welcome to MyZork!\n" _WHITE;
	cout << "----------------\n";

	World MyWorld;


	cout << "\nThanks for playing, Bye!\n";
	return 0;
}
