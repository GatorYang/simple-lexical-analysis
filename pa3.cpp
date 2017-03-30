#include <iostream>
#include <fstream>
#include <vector>
#include "pa3.h"

using namespace std;
bool hasPlus = false;
bool hasMinus = false;
bool hasStar = false;
bool hasForwardSlash = false;
bool hasPlusPlus  = false;
bool hasEquals = false;
bool hasComma = false;
bool hasSemicolon = false;
bool hasFor = false;
bool hasBegin = false;
bool hasEnd = false;

int main (){
	vector <string> filelines;
	vector <string> parted;
	
    string filename;
    string type;
    
    cout << "Please enter the name of the input file:" <<endl;
    cin >> filename;
    ifstream file;
    file.open(filename);
    if (file.fail()){
        cout << "ERROR FAIL TO OPEN FILE" <<endl;
        return 1;
    }
    int count = 0;
    while( file.good() ) {
		std::string token;
		file >> token;
		cout << "Token " << count++ << ": " << token << std::endl;
		for (unsigned int i = 0; i < token.size(); i++){
			filelines.push_back(token.substr(i,1));
		}
		
	}
	for ( unsigned int i = 0; i < filelines.size(); i++){
		cout << filelines[i] << " " <<endl;
	}
	
	
	file.close();
	return 0;
}

// vector<string> toVector(string s) {
// 	vector <string> words;
// 	string word;
// 	for (int i; i<s.size(); i++){
		
// 	}
	
// }

bool isOperator(string s){
	bool check = false;
	if (s == "+"){
		check = true;
		hasPlus = true;
	}
	else if(s == "-"){
		check = true;
		hasMinus = true;
	}
	else if(s == "*"){
		check = true;
		hasStar = true;
	}
	else if(s == "/"){
		check = true;
		hasForwardSlash = true;
	}
	else if(s == "++"){
		check = true;
		hasPlusPlus = true;
	}
	else if(s == "="){
		check = true;
		hasEquals = true;
	}
	return check;
}

bool isDelimiter(string s) {
	bool check = false;
	if (s == ","){
		check = true;
		hasComma = true;
	}
	else if (s == ";"){
		check = true;
		hasSemicolon = true;
	}
	return check;
}

bool isLowercase(string s) {
	for (int i = 0; i < (signed int)s.size(); ++i) {
		if (s[i] < 'a' || s[i] > 'z')
			return false;
	}
	return true;
}

bool isUppercase(string s) {
	for (int i = 0; i < (signed int)s.size(); ++i) {
		if (s[i] < 'A' || s[i] > 'Z')
			return false;
	}
	return true;
}



