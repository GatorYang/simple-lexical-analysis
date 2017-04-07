#include <iostream>
#include <vector>

using namespace std;

class Stack{
    vector <string> vect;
    int maxCount = 0;
    int currentCount = 0;
public:
    void push(string data);
    void pop();
    int getMax();
    int getCurrent();
    void setMax(int newMax);
    void setCurrent(int newCurrent);
    int size();
    void clean();
    
};



