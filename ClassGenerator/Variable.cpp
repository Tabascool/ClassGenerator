#include "Variable.h"

Variable::Variable()
{

}
Variable::Variable(const Variable & v){
    name_ = v.name_;
    visibility_ = v.visibility_;
    type_ = v.type_;
}

void Variable::setName(string name){
    name_ = name;
}

string Variable::getName(){
    return name_;
}

void Variable::setSimplifiedType(string simplifiedType){
    simplifiedType_ = simplifiedType;
}

string Variable::getSimplifiedType(){
    return simplifiedType_;
}

void Variable::setVisibility(string visibility){
    visibility_ = visibility;
}

string Variable::getVisibility(){
    return visibility_;
}

void Variable::setType(string type){    
    char ch = *type.rbegin();
    if(ch == '*') {
        isPointer_ = true;
        simplifiedType_ = type.substr(0, type.find_last_not_of("*")+1);
    } else if(ch == '&') {
        isReference_ = true;
        simplifiedType_ = type.substr(0, type.find_last_not_of("&")+1);
    }
    type_ = type;
}

string Variable::getType(){
    return type_;
}

bool Variable::isPointer() {
    return isPointer_;
}

bool Variable::isReference() {
    return isReference_;
}

void Variable::print(){
    cout << type_ << " " << name_ << " " << visibility_;
}

bool Variable::operator<(Variable& v){
    return name_ < v.name_;
}

bool Variable::operator==(Variable& v){
    return name_ == v.name_ && type_ == v.type_;
}

Variable & Variable::operator=(const Variable &v){
    if(this != &v) {
        name_ = v.name_;
        visibility_ = v.visibility_;
        type_ = v.type_;
    }
    return *this;
}
