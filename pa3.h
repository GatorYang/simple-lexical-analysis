#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

string keyword[];
string identi[];
string constant[];
string operators[];
string delimiters[];

string filename;
int depth;


bool isLowercase(string s);
bool isUppercase(string s);