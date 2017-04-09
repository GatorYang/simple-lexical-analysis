#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "pa3.h"

using namespace std;

void checkIden(string line, vector <string> &iden); //method check all the identifiers and store into the vector
void checkCons(string line, vector <string> &cons); //method check all the constant and store into the vector
void checkErrors(string line, vector <string> &errors); //method check all the errors and store into the vector
bool checkSyntax (string s); //method check if the string contain words thats not "FOR,BEGIN,END"
void checkEnd(vector <string> &errors, bool end); //if not in "FOR,BEGIN,END" add to the error vector
void checkParen(string line, vector <string> &errors, bool &paren);//parenthesis syntax error

void Stack::push(string data){ //push for the stack
	vect.push_back(data);
	currentCount++;
		if (currentCount > maxCount){
			maxCount = currentCount;
		}
}

void Stack::pop(){ //pop for the stack
	if (vect.size() > 0){
		vect.pop_back();
		currentCount--;
	}
}

void Stack::clean(){	//delete everything on the stack
	for (size_t i; i < vect.size(); i ++){
		vect.pop_back();
		currentCount--;
	}
}

int Stack::getMax(){	//return the top stack size
	return maxCount;
}

int Stack::getCurrent(){	//return current count on the stack size
	return currentCount;
}

void Stack::setMax(int newMax){	//reset new max stack size
	maxCount = newMax;
}

void Stack::setCurrent(int newCurrent){	//set new current count
	currentCount = newCurrent;
}

int Stack::size(){ //return the stack size
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
	size_t a = -1;
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
    file.open(filename); // open the file
    
    
    if (file.fail()){ //if the file doesnt open
        cout << "ERROR: FAIL TO OPEN FILE!" <<endl;
        return 1;
    }
    
    Stack loop; //make a stack for counting the oop
    
    
    while( getline(file,line) ) {	//go thorugh the file line by line
		if (line.find("FOR")!= a){
			hasFor= true;
		}
		if (line.find("BEGIN")!= a){
			hasBegin= true;
			loop.push("BEGIN");
			if (isnest && paren){
				nestcount ++;
				if (nestcount > absnest){
					absnest = nestcount;
				}
			}
			else if (!isnest && paren){
				if (nestcount > absnest){
					absnest = nestcount;
				}
				nestcount = 0;
				nestcount ++;
				isnest=true;
			}
			
			if (!paren){
				paren = true;
			}
		}
		if (line.find("END")!= a){
			hasEnd= true;
			loop.pop();
			isnest = false;
		}
		if (line.find(",")!= a){
			hasComma= true;
		}
		if (line.find(";")!= a){
			hasSemicolon= true;
		}
		if (line.find(" + ")!= a){
			hasPlus= true;
		}
		if (line.find("++")!= a){
			hasPlusPlus= true;
		}
		if (line.find("-")!= a){
			hasMinus= true;
		}
		if (line.find("*")!= a){
			hasStar= true;
		}
		if (line.find("/")!= a){
			hasForwardSlash= true;
		}
		if (line.find("(")!= a || line.find(")")!= a){
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
	if (absnest > 0 && count < absnest){
		count = absnest;
	}
	
	//just output the results 
	cout << "The depth of nested loop(s) is ";
	cout << count;
	
	
	cout <<"\nKeywords: ";
	if (hasFor) cout<<"FOR ";
	if (hasBegin) cout<<"BEGIN ";
	if (hasEnd) cout<<"END";
	cout <<"\nIdentifiers: ";
	for (size_t i = 0; i < iden.size(); i++){
	    cout<<iden[i] + " ";
	}
	cout <<"\nConstants: ";
	for (size_t i = 0; i < cons.size(); i++)
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
    for (size_t i = 0; i < errors.size(); i++){
	    cout<<errors[i] + " ";
    }
	if ( errors.size() < 2){
		cout << "NA" ;
	}
	cout << "\n";
	file.close();
	return 0;
}


void checkIden(string line, vector <string> &iden){
	string identi = "";
	for(size_t i = 0; i < line.size(); i++){
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
	for(size_t i = 0; i < line.size(); i++){
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
	for(size_t i = 0; i < line.size(); i++){
		if (isupper(line[i])!=0){
			uper += line[i];
		} 
		if (isupper(line[i])==0){
			if(checkSyntax(uper)){
				errors.push_back(uper);	
			}
			uper = "";
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
	for(size_t i = 0; i < line.size(); i++){
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