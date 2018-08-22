//
//  ClassParser.h
//  Programme2
//
//  Created by Arnaud Le Bourblanc on 01/06/2015.
//  Copyright (c) 2015 ESGI. All rights reserved.
//

#ifndef __Programme2__ClassParser__
#define __Programme2__ClassParser__

#include <stdio.h>
#include <iostream>
#include "CGUtils.h"
#include "pugixml.hpp"
#include "Classe.h"
#include "Variable.h"
#include "Fonction.h"
#include "HeaderFileCreator.h"
#include "SourceFileCreator.h"

using namespace std;
class ClassParser {
private:
    CGUtils::ResultCode result;
    string path;
    string folder;
    pugi::xml_document doc;
    Classe* classe;
    void parse();
    void parseVariables(pugi::xpath_node&);
    void parseFunction(pugi::xpath_node&);
    void createFiles();
public:
    ClassParser(string, string);
    CGUtils::ResultCode run();
};



#endif /* defined(__Programme2__ClassParser__) */
