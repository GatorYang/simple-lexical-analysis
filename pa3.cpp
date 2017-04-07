#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "pa3.h"

using namespace std;

void checkIden(string line, vector <string> &iden);
void checkCons(string line, vector <string> &cons);
void checkErrors(string line, vector <string> &errors);
bool checkSyntax (string s);
void checkEnd(vector <string> &errors, bool end);
void checkParen(string line, vector <string> &errors, bool &paren);//parenthesis syntax error

void Stack::push(string data){
	vect.push_back(data);
}

void Stack::pop(){
	if (vect.size() > 0){
		vect.pop_back();
		currentCount++;
		if (currentCount > maxCount){
			maxCount = currentCount;
		}
	}
}

void Stack::clean(){
	for (int i; i < vect.size(); i ++){
		vect.pop_back();
		currentCount--;
	}
}

int Stack::getMax(){
	return maxCount;
}

int Stack::getCurrent(){
	return currentCount;
}

void Stack::setMax(int newMax){
	maxCount = newMax;
}

void Stack::setCurrent(int newCurrent){
	currentCount = newCurrent;
}

int Stack::size(){
	return vect.size();
}

int main (){
	vector <string> iden; // vector store all the identifiers
	vector <string> cons; // vector store all the constants
	vector <string> errors; // vector store all the syntax errors
	vector <int> depth; // vector store all the possible depth
	bool isnest = true; //bool to see if the loops are nested
	int nestcount = 0;
	int absnest = 0;
	int count = 0;
	bool paren = true;
	//bunch checks see if what we are looking for are in the txt file
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

    string filename;
    string line;
    cout << "Please enter the name of the input file:" <<endl;
    cin >> filename;
    ifstream file;
    file.open(filename);
    if (file.fail()){
        cout << "ERROR FAIL TO OPEN FILE" <<endl;
        return 1;
    }
    Stack loop;
    
    
    while( getline(file,line) ) {
	
		
		if (line.find("FOR")!=-1){
			hasFor= true;
		}
		if (line.find("BEGIN")!=-1){
			hasBegin= true;
			loop.push("BEGIN");
			
			if (isnest && paren){
				nestcount ++;
			}
			else if (!isnest && paren){
				absnest = nestcount;
				nestcount = 0;
				nestcount ++;
				isnest=true;
			}
			
			if (!paren){
				paren = true;
			}
		}
		if (line.find("END")!=-1){
			hasEnd= true;
			loop.pop();
			isnest = false;
		}
		if (line.find(",")!=-1){
			hasComma= true;
		}
		if (line.find(";")!=-1){
			hasSemicolon= true;
		}
		if (line.find(" + ")!=-1){
			hasPlus= true;
		}
		if (line.find("++")!=-1){
			hasPlusPlus= true;
		}
		if (line.find("-")!=-1){
			hasMinus= true;
		}
		if (line.find("*")!=-1){
			hasStar= true;
		}
		if (line.find("/")!=-1){
			hasForwardSlash= true;
		}
		if (line.find("(")!=-1 || line.find(")")!=-1){
			checkParen(line, errors, paren);
		}
		
		checkIden(line, iden);
		checkCons(line, cons);
		checkErrors(line, errors);
    }
    

    count = loop.getMax();
    
    if (loop.size() == 0 && nestcount > absnest){
    	absnest = nestcount;
    }
    

	if (loop.size() > 0 && loop.getMax() != 0){
		count = loop.getMax() - loop.size();
	}
	
	if (loop.getCurrent() < 0 && loop.getMax() != 0){
		count = loop.getMax() + loop.getCurrent();
	}
	
	if (absnest > 0 && count > absnest){
		count = absnest;
	}
	
	cout << "The depth of nested loop(s) is ";
	cout << count << "!";
	
	
	cout <<"\nKeywords: ";
	if (hasFor) cout<<"FOR ";
	if (hasBegin) cout<<"BEGIN ";
	if (hasEnd) cout<<"END";
	cout <<"\nIdentifiers: ";
	for (int i = 0; i < iden.size(); i++){
	    cout<<iden[i] + " ";
	}
	cout <<"\nConstants: ";
	for (int i = 0; i < cons.size(); i++)
	    cout<<cons[i] + " ";
	cout <<"\nOperators: ";
	if (hasPlusPlus) cout<<"++ ";
	if (hasEquals) cout<<"= ";
	if (hasPlus) cout<<"+ ";
	if (hasMinus) cout<<"- ";
	if (hasStar) cout<<"* ";
	if (hasForwardSlash) cout<<"/ ";
	cout <<"\nDelimiters: ";
	if (hasSemicolon) cout<<"; ";
	if (hasComma) cout<<", ";
	
	cout<<"\nSyntax Error(s):";
	checkEnd(errors, hasEnd);
    for (int i = 0; i < errors.size(); i++){
	    cout<<errors[i] + " ";
    }
	if ( errors.size() < 2){
		cout << "NA" <<endl;
	}
	file.close();
	return 0;
}


void checkIden(string line, vector <string> &iden){
	string identi = "";
	for(int i = 0; i < line.size(); i++){
		if (islower(line[i])!=0){
			identi += line[i];
		} 
		if (islower(line[i])==0){
			iden.push_back(identi);
			identi = "";
		}
	}
	sort( iden.begin(), iden.end() );
	iden.erase( unique( iden.begin(), iden.end() ), iden.end() );
}


void checkCons(string line, vector <string> &cons){
	string conss = "";
	for(int i = 0; i < line.size(); i++){
		if (isdigit(line[i])!=0){
			conss += line[i];
		} 
		if (isdigit(line[i])==0){
			cons.push_back(conss);
			conss = "";
		}
	}
	sort( cons.begin(), cons.end() );
	cons.erase( unique( cons.begin(), cons.end() ), cons.end() );
}

void checkErrors(string line, vector <string> &errors){
	string uper = "";
	bool check = true;
	for(int i = 0; i < line.size(); i++){
		if (isupper(line[i])!=0){
			uper += line[i];
		} 
		if (isupper(line[i])==0){
			if(checkSyntax(uper)){
				errors.push_back(uper);	
			}
			uper = "";
			check = false;
		}
	}
	if (checkSyntax(uper)){
		errors.push_back(uper);
	}
	sort( errors.begin(), errors.end() );
	errors.erase( unique( errors.begin(), errors.end() ), errors.end() );
}

bool checkSyntax (string s){
	if (s == "FOR" || s == "END" || s == "BEGIN")
	{
		return false;
	}
	else{
		return true;
	}
	
}

void checkEnd(vector <string> &errors, bool end){
	if (!end){
		errors.push_back("END");
	}
}

void checkParen(string line, vector <string> &errors, bool &paren){
	int braIn = 0;
	int braEnd = 0;
	for(int i = 0; i < line.size(); i++){
		if(line[i] == '('){
			braIn ++;
		}
		else if(line[i] == ')'){
			braEnd ++;
		}
	}
	if (braEnd < braIn){
		errors.push_back("(");
		paren = false;
	}
	if (braIn < braEnd){
		errors.push_back(")");
		paren = false;
	}
}