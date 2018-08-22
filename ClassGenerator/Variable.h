#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <iostream>
using namespace std;
class Variable
{
private:
    string name_;
    string visibility_;
    string type_;
    bool isPointer_;
    bool isReference_;
    string simplifiedType_;

public:
    Variable();
    Variable(const Variable &);
    void setName(string);
    string getName();
    void setSimplifiedType(string);
    string getSimplifiedType();
    void setVisibility(string);
    string getVisibility();
    void setType(string);
    string getType();
    bool isPointer();
    bool isReference();
    void print();
    bool operator < (Variable&);
    bool operator ==(Variable&);
    Variable & operator =(const Variable &);
};

#endif // VARIABLE_H
