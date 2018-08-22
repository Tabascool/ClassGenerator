#ifndef CLASSE_H
#define CLASSE_H

#include <string>
#include "Variable.h"
#include "Fonction.h"
#include <vector>
#include <iostream>
#include "CGUtils.h"
using namespace std;

class Classe
{
private:
    vector<Variable*> vPrivate;
    vector<Variable*> vPublic;
    vector<Fonction*>fPrivate;
    vector<Fonction*>fPublic;
    string name_;
    string heritage_;
    CGUtils::visibility heritageVisibility_;

public:
    Classe();
    Classe(const Classe &);
    const vector<Variable*>& getVPrivate() const;
    const vector<Variable*>& getVPublic() const;
    const vector<Fonction*>& getFPrivate();
    const vector<Fonction*>& getFPublic();
    void setName(string);
    string getName();
    void setHeritage(string);
    string getHeritage();
    void setHeritageVisibility(CGUtils::visibility);
    CGUtils::visibility getHeritageVisibility();
    void addPublicVariable(Variable*);
    void addPrivateVariable(Variable*);
    void addPublicFunction(Fonction*);
    void addPrivateFunction(Fonction*);
    bool operator<(Classe);
    bool operator==(Classe);
    Classe & operator=(const Classe &);
};

#endif // CLASSE_H
