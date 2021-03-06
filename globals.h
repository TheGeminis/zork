#ifndef __Globals__
#define __Globals__

#include <string>
#include <vector>

using namespace std;

bool Same(const string& a, const string& b);
bool Same(const char* a, const string& b);
bool Same(const string& a, const char* b);
void Tokenize(const string& line, vector<string>& arguments);
int Roll(int min, int max);
int Modifiers(string& aura_attacker, string& aura_target);

#endif //__Globals__#pragma once
