//
//  HeaderSourceFile.cpp
//  Programme2
//
//  Created by Arnaud Le Bourblanc on 01/06/2015.
//  Copyright (c) 2015 ESGI. All rights reserved.
//

#include "HeaderFileCreator.h"
HeaderFileCreator::HeaderFileCreator(Classe *c, string p){
    classe = c;
    path = p;
}

bool HeaderFileCreator::writeHeaderFile() {

    setInclude();
    createFile();
    privateMF();
    publicMF();
    getterSetter();
    closeFile();

    return true;
}

void HeaderFileCreator::setInclude(){
    if(!classe->getHeritage().empty()) {
        includes.insert(classe->getHeritage());
    }
    Variable* var;
    if(!classe->getVPublic().empty()) {
        for(vector<Variable*>::const_iterator itVPublic = classe->getVPublic().begin() ; itVPublic != classe->getVPublic().end(); ++itVPublic) {
            var = *itVPublic;
            if(find(CGUtils::dataTypes, CGUtils::dataTypes + 7, var->getType()) == (CGUtils::dataTypes + 7)) {
                if(var->isPointer() || var->isReference()){
                    includes.insert(var->getSimplifiedType());
                } else {
                    includes.insert(var->getType());
                }
            }
        }
    }

    if(!classe->getVPrivate().empty()) {
        for(vector<Variable*>::const_iterator itVPrivate = classe->getVPrivate().begin() ; itVPrivate != classe->getVPrivate().end(); ++itVPrivate) {
            var = *itVPrivate;
            if(find(CGUtils::dataTypes, CGUtils::dataTypes + 7, var->getType()) == (CGUtils::dataTypes + 7)) {
                if(var->isPointer() || var->isReference()){
                    includes.insert(var->getSimplifiedType());
                } else {
                    includes.insert(var->getType());
                }
            }
        }
    }
}

void HeaderFileCreator::createFile(){
    string filename = path + classe->getName() + ".h";
    headerFile.open(filename.c_str());
    headerFile << "//" << endl;
    headerFile << "//   " << classe->getName() << ".h" << endl;
    headerFile << "//" << endl;
    headerFile << "//   File generated using ClassGenerator" << endl;
    headerFile << "//" << endl;
    headerFile << endl;
    headerFile << "#ifndef " << classe->getName() << endl;
    headerFile << "#define " << classe->getName() << endl;
    headerFile << endl;
    if(!includes.empty()) {
        for(set<string>::const_iterator itInclude = includes.begin(); itInclude != includes.end() ; ++itInclude) {
            headerFile << "#include \"" << *itInclude << ".h\"" << endl;
        }
        headerFile << endl;
    }
    headerFile << "class " << classe->getName();
    if(!classe->getHeritage().empty()) {
        headerFile << " : ";
        switch(classe->getHeritageVisibility()) {
            case CGUtils::PRIVATE :
                headerFile << "private";
                break;
            case CGUtils::PROTECTED :
                headerFile << "protected";
                break;
            case CGUtils::PUBLIC :
                headerFile << "public";
                break;
        }

        headerFile << " " << classe->getHeritage() << endl;
    } else {
        headerFile << endl;
    }
    headerFile << "{" << endl;
}

void HeaderFileCreator::privateMF(){
    headerFile << "private :" << endl;
    headerFile << "\t" << "//Private members and functions : " << endl;
    displayVariables(classe->getVPrivate());
    displayFunctions(classe->getFPrivate());
}

void HeaderFileCreator::publicMF(){
    headerFile << "public :" << endl;
    headerFile << "\t" << "//Public members and functions" << endl;
    displayVariables(classe->getVPublic());
    displayFunctions(classe->getFPublic());

    headerFile << "\t" << classe->getName() << "() = default;" << endl;
    headerFile << "\t" << classe->getName() << "(const " << classe->getName() << "&);" << endl;
    headerFile << "\t" << classe->getName() << "& " << "operator=(const " << classe->getName() << "&);" << endl;
    headerFile << "\t" << "bool operator<(const " << classe->getName() <<"&);" <<endl;
    headerFile << "\t" << "~" << classe->getName() << "();" << endl;
}

void HeaderFileCreator::closeFile(){
    headerFile << "}" << endl;
    headerFile << endl;
    headerFile << "#endif" << endl;
    headerFile.close();
}

void HeaderFileCreator::displayVariables(const vector<Variable *> & variables){
    if(!variables.empty()) {
        Variable* var;
        for(vector<Variable*>::const_iterator itVPrivate = variables.begin() ; itVPrivate != variables.end(); ++itVPrivate) {
            var = *itVPrivate;
            headerFile << "\t" << var->getType() << " " << var->getName() << ";" << endl;
        }
        headerFile << endl;
    }
}

void HeaderFileCreator::displayFunctions(const vector<Fonction *> & functions){
    if(!functions.empty()){
        Fonction* func;
        for(vector<Fonction*>::const_iterator itFPrivate = functions.begin(); itFPrivate != functions.end(); itFPrivate++){
            func = *itFPrivate;
            headerFile << "\t" << func->getType() << " " << func->getName() << "();" << endl;
        }
    }
}

void HeaderFileCreator::getterSetter(){
    Variable* var;
    for(vector<Variable*>::const_iterator itVPrivate = classe->getVPrivate().begin(); itVPrivate != classe->getVPrivate().end(); itVPrivate++){
        var = *itVPrivate;
        string varName = var->getName();
        varName[0] = toupper(varName[0]);
        headerFile << "\t" << var->getType() << " get" << varName << "();" << endl;
        headerFile << "\t" << "void " << "set" << varName << "(" << var->getType() << ");" << endl;
    }
}
