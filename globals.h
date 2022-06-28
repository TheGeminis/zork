#ifndef __Globals__
#define __Globals__

#include <string>
#include <vector>

using namespace std;


#define _OFF "\033[0m"
#define RED_ "\033[0;31m"
#define GREEN_ "\033[0;32m"
#define BROWN_ "\033[0;33m"
#define BLUE_ "\033[1;34m"
#define MAGENTA_ "\033[1;35M"
#define WHITE_ "\033[1;36m"


bool Same(const string& a, const string& b);
bool Same(const char* a, const string& b);
bool Same(const string& a, const char* b);
void Tokenize(const string& line, vector<string>& arguments);
int Roll(int min, int max);
int Modifiers(string& aura_attacker, string& aura_target);

#endif //__Globals__#pragma once
