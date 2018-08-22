//
//  SourceFileCreator.h
//  Programme2
//
//  Created by Arnaud Le Bourblanc on 01/06/2015.
//  Copyright (c) 2015 ESGI. All rights reserved.
//

#ifndef __Programme2__SourceFileCreator__
#define __Programme2__SourceFileCreator__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Classe.h"
#include "Variable.h"
#include "CGUtils.h"

using namespace std;
class SourceFileCreator
{
private:
    Classe* classe;
    string path;
    Variable* var;
    ofstream SourceFile;
    void createFile();
    void closeFile();
    void copyConstructor();
    void destructor();
    void operatorE();
    void operatorINE();
    void getterSetter();
    void functions();
public:
    SourceFileCreator(Classe*, string);
    bool writeSourceFile();
};

#endif /* defined(__Programme2__SourceFileCreator__) */
