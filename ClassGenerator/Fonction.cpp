#include "Fonction.h"

Fonction::Fonction()
{

}

Fonction::Fonction(const Fonction &f){
    name_ = f.name_;
    visibility_ = f.visibility_;
    type_ = f.type_;
    parameters = f.parameters;
}

string Fonction::getName(){
    return name_;
}

void Fonction::setName(string name){
    name_ = name;
}

string Fonction::getVisibility(){
    return visibility_;
}

void Fonction::setVisibility(string v){
    visibility_ = v;
}

string Fonction::getType(){
    return type_;
}

void Fonction::setType(string type){
    type_ = type;
}

const vector<Variable*>& Fonction::getParameters(){
    return parameters;
}

void Fonction::addParameter(Variable* v){
    parameters.push_back(v);
}

bool Fonction::operator <(Fonction& f){
    return name_ < f.name_;
}

bool Fonction::operator ==(Fonction& f){
    return name_ == f.name_;
}

Fonction& Fonction::operator =(Fonction& f){
    if(this != &f){
        name_ = f.name_;
        visibility_ = f.visibility_;
        type_ = f.type_;
        parameters = f.parameters;
    }
    return *this;
}

