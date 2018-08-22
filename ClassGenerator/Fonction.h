#ifndef FONCTION_H
#define FONCTION_H

#include <iostream>
#include <vector>
#include "Variable.h"
using namespace std;
class Fonction
{
private:
    string name_;
    string visibility_;
    string type_;
    vector<Variable*> parameters;
public:
    Fonction();
    Fonction(const Fonction &);
    string getName();
    void setName(string);
    string getVisibility();
    void setVisibility(string);
    string getType();
    void setType(string);
    const vector<Variable*>& getParameters();
    void addParameter(Variable*);
    bool operator <(Fonction&);
    bool operator ==(Fonction&);
    Fonction& operator =(Fonction&);

};

#endif // FONCTION_H
