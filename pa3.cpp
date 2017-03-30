#include <iostream>
#include <fstream>
#include <vector>
#include "pa3.h"

using namespace std;


int main (){
	vector <string> filelines;
	vector <string> parted;
	
    string filename;
    cout << "Please enter the name of the input file:" <<endl;
    cin >> filename;
    ifstream file;
    file.open(filename);
    if (file.fail()){
        cout << "file not open!";
        return 1;
    }
    int count = 0;
    while( file.good() ) {
		std::string token;
		file >> token;
		std::cout << "Token " << count++ << ": " << token << std::endl;
	}
	
	
	file.close();
	return 0;
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


