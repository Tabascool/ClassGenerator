#include "Classe.h"

Classe::Classe()
{

}

Classe::Classe(const Classe &c){
    vPrivate = c.vPrivate;
    vPublic = c.vPublic;
    name_ = c.name_;
    heritage_ = c.heritage_;
}

const vector<Variable*>& Classe::getVPrivate() const {
    return vPrivate;
}

const vector<Variable *>& Classe::getVPublic() const {
    return vPublic;
}

const vector<Fonction*>& Classe::getFPrivate(){
    return fPrivate;
}

const vector<Fonction*>& Classe::getFPublic(){
    return fPublic;
}

void Classe::setName(string name){
    name_ = name;
}

string Classe::getName(){
    return name_;
}

void Classe::setHeritage(string heritage){
    heritage_ = heritage;
}

string Classe::getHeritage(){
    return heritage_;
}

void Classe::setHeritageVisibility(CGUtils::visibility heritageVisibility){
    heritageVisibility_ = heritageVisibility;
}

CGUtils::visibility Classe::getHeritageVisibility(){
    return heritageVisibility_;
}

void Classe::addPrivateVariable(Variable *v) {
    vPrivate.push_back(v);
}

void Classe::addPublicVariable(Variable *v) {
    vPublic.push_back(v);
}

void Classe::addPublicFunction(Fonction*f){
    fPublic.push_back(f);
}

void Classe::addPrivateFunction(Fonction*f){
    fPrivate.push_back(f);
}

bool Classe::operator<(Classe v){
    return name_ < v.name_;
}

bool Classe::operator==(Classe v){
    return name_ == v.name_;
}

Classe & Classe::operator=(const Classe &c){
    if(this != &c) {
        name_ = c.name_;
        heritage_ = c.heritage_;
        vPrivate = c.vPrivate;
        vPublic = c.vPublic;
    }
    return *this;
}
