//
//  HeaderSourceFile.h
//  Programme2
//
//  Created by Arnaud Le Bourblanc on 01/06/2015.
//  Copyright (c) 2015 ESGI. All rights reserved.
//

#ifndef __Programme2__HeaderSourceFile__
#define __Programme2__HeaderSourceFile__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>
#include "Classe.h"
#include "Variable.h"
#include "Fonction.h"
#include "CGUtils.h"

using namespace std;

class HeaderFileCreator {
private:
    Classe* classe;
    string path;
    set<string> includes;
    ofstream headerFile;
    void setInclude();
    void createFile();
    void privateMF();
    void publicMF();
    void getterSetter();
    void closeFile();
    void displayVariables(const vector<Variable*>&);
    void displayFunctions(const vector<Fonction*>&);
public :
    HeaderFileCreator(Classe*, string);
    bool writeHeaderFile();
};

#endif /* defined(__Programme2__HeaderSourceFile__) */
