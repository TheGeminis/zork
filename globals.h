#ifndef __Globals__
#define __Globals__

#include <string>
#include <vector>

using namespace std;

bool Same(const string& a, const string& b);
bool Same(const char* a, const string& b);
bool Same(const string& a, const char* b);
void Tokenize(const string& line, vector<string>& arguments);

#endif //__Globals__#pragma once
