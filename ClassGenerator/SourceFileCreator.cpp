#include "SourceFileCreator.h"

SourceFileCreator::SourceFileCreator(Classe *c, string p){
    classe = c;
    path = p;
}

bool SourceFileCreator::writeSourceFile() {

    createFile();
    copyConstructor();
    destructor();
    operatorE();
    operatorINE();
    functions();
    getterSetter();
    closeFile();
    return true;
}

void SourceFileCreator::createFile(){
    string filename = path + classe->getName() + ".cpp";
    SourceFile.open(filename.c_str());
    SourceFile << "//" << endl;
    SourceFile << "//   " << classe->getName() << ".cpp" << endl;
    SourceFile << "//" << endl;
    SourceFile << "//   File generated using ClassGenerator" << endl;
    SourceFile << "//" << endl;
    SourceFile << endl;
    SourceFile << "#include \"" << classe->getName() << ".h\"" << endl;
    SourceFile << endl;
}

void SourceFileCreator::closeFile(){
    SourceFile << endl;
    SourceFile.close();
}

void SourceFileCreator::copyConstructor(){
    //constructor copy
    SourceFile << classe->getName() << "::" << classe->getName() << "(const " << classe->getName() << "& a) {" << endl;
    for(vector<Variable*>::const_iterator itVPublic = classe->getVPublic().begin() ; itVPublic != classe->getVPublic().end(); ++itVPublic) {
        var = *itVPublic;
        SourceFile << "\t" << var->getName() << " = a." << var->getName() << ";" << endl;
    }
    for(vector<Variable*>::const_iterator itVPrivate = classe->getVPrivate().begin() ; itVPrivate != classe->getVPrivate().end(); ++itVPrivate) {
        var = *itVPrivate;
        SourceFile << "\t" << var->getName() << " = a." << var->getName() << ";" << endl;
    }
    SourceFile << "}" << endl;
    SourceFile << endl;
}

void SourceFileCreator::destructor(){
    //destructor
    SourceFile << classe->getName() << "::~" << classe->getName() << "() {" << endl;
    for(vector<Variable*>::const_iterator itVPublic = classe->getVPublic().begin() ; itVPublic != classe->getVPublic().end(); ++itVPublic) {
        var = *itVPublic;
        if(var->isPointer()) {
            SourceFile << "\t" << "delete[] " << var->getName() << ";" << endl;
        }
    }
    for(vector<Variable*>::const_iterator itVPrivate = classe->getVPrivate().begin() ; itVPrivate != classe->getVPrivate().end(); ++itVPrivate) {
        var = *itVPrivate;
        if(var->isPointer()) {
            SourceFile << "\t" << "delete[] " << var->getName() << ";" << endl;
        }
    }
    SourceFile << "}" << endl;
    SourceFile << endl;
}

void SourceFileCreator::operatorE(){
    //operator =
    SourceFile << classe->getName() << "& " << classe->getName() << "::" << "operator=(const " << classe->getName() << "& a) {" << endl;
    SourceFile << "\t" << "if(this != &a) {" << endl;
    for(vector<Variable*>::const_iterator itVPublic = classe->getVPublic().begin() ; itVPublic != classe->getVPublic().end(); ++itVPublic) {
        var = *itVPublic;
        SourceFile << "\t\t" << var->getName() << " = a." << var->getName() << ";" << endl;
    }
    for(vector<Variable*>::const_iterator itVPrivate = classe->getVPrivate().begin() ; itVPrivate != classe->getVPrivate().end(); ++itVPrivate) {
        var = *itVPrivate;
        SourceFile << "\t\t" << var->getName() << " = a." << var->getName() << ";" << endl;
    }
    SourceFile << "\t" << "}" << endl;
    SourceFile << "\t" << "return *this" << endl;
    SourceFile << "}" << endl;
    SourceFile << endl;
}

void SourceFileCreator::operatorINE(){
    //operator <
    SourceFile << "bool " << classe->getName() << "::operator<(const " << classe->getName() << "& a) {" << endl;
    if(!classe->getVPrivate().empty()) {
        SourceFile << "\t" << "return " << classe->getVPrivate().at(0)->getName() << " < a." << classe->getVPrivate().at(0)->getName() << ";" << endl;
    } else if (!classe->getVPublic().empty()) {
        SourceFile << "\t" << "return " << classe->getVPublic().at(0)->getName() << " < a." << classe->getVPublic().at(0)->getName() << ";" << endl;
    } else {
        SourceFile << "\t" << "return true;" << endl;
    }
    SourceFile << "}" << endl;
    SourceFile<<endl;
}

void SourceFileCreator::functions(){
    Fonction* func;
    for(vector<Fonction*>::const_iterator itFPublic = classe->getFPublic().begin(); itFPublic!= classe->getFPublic().end(); itFPublic++){
        func = *itFPublic;
        SourceFile << func->getType() <<" " << classe->getName() << "::" << func->getName() << "(){}" << endl;
        SourceFile << endl;

    }
    for(vector<Fonction*>::const_iterator itFPrivate = classe->getFPrivate().begin(); itFPrivate != classe->getFPrivate().end(); itFPrivate++){
        func = *itFPrivate;
        SourceFile << func->getType() << " " << classe->getName() << "::" << func->getName() << "(){}" << endl;
        SourceFile << endl;
    }
}

void SourceFileCreator::getterSetter(){
    for (vector<Variable*>::const_iterator itVPrivate = classe->getVPrivate().begin(); itVPrivate != classe->getVPrivate().end(); itVPrivate++){
        var = *itVPrivate;
        string varName = var->getName();
        varName[0] = toupper(varName[0]);
        SourceFile << var->getType()<<" " << classe->getName() << "::get" << varName << "(){" << endl;
        SourceFile << "\t" << "return " << var->getName() << ";" << endl;
        SourceFile << "}"<< endl;
        SourceFile << "void " << classe->getName() << "::set" << varName << "(" << var->getType() << " " << var->getName() <<"){" <<endl;
        SourceFile << "\t" << "this." << var->getName() << "=" << var->getName() << ";" << endl;
        SourceFile << "}" << endl;
    }
    SourceFile << endl;
}

