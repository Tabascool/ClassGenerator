//
//  ClassParser.cpp
//  Programme2
//
//  Created by Arnaud Le Bourblanc on 01/06/2015.
//  Copyright (c) 2015 ESGI. All rights reserved.
//

#include "ClassParser.h"

ClassParser::ClassParser(string path, string folder){
    this->path = path;
    this->folder = folder;
}

CGUtils::ResultCode ClassParser::run() {

    result.first = true;
    result.second = "La génération est terminé, vous pouvez trouver vos fichiers sur votre bureau.";

    pugi::xml_parse_result parseResult = doc.load_file(path.c_str());
    if(parseResult.status == pugi::status_file_not_found) {
        result.first = false;
        result.second = "File not found";
    } else if(parseResult.status != pugi::status_ok) {
        result.first = false;
        result.second = "An unknown error occured";
    } else {
        parse();
    }


    return result;
}
void ClassParser::parse(){
    pugi::xpath_node_set nClasses = doc.select_nodes("//classe");

    for (pugi::xpath_node_set::const_iterator itC = nClasses.begin(); itC != nClasses.end(); ++itC)
    {
        pugi::xpath_node node = *itC;
        classe = new Classe();
        classe->setName(node.node().attribute("name").value());
        classe->setHeritage(node.node().attribute("extends").value());
        string heritageVisibility = node.node().attribute("visiblity").value();
        if(heritageVisibility.compare("public") == 0) {
            classe->setHeritageVisibility(CGUtils::PUBLIC);
        } else if(heritageVisibility.compare("protected") == 0) {
            classe->setHeritageVisibility(CGUtils::PROTECTED);
        } else {
            classe->setHeritageVisibility(CGUtils::PRIVATE);
        }

        parseVariables(node);
        parseFunction(node);

        //Create Header File and Source File
        createFiles();
    }
}

void ClassParser::parseVariables(pugi::xpath_node& node){
    pugi::xpath_node_set nVariables = node.node().select_nodes(".//attribute");

    Variable* variable;
    for (pugi::xpath_node_set::const_iterator itV = nVariables.begin(); itV != nVariables.end(); ++itV)
    {
        pugi::xpath_node node = *itV;
        variable = new Variable();
        variable->setName(node.node().attribute("name").value());
        variable->setVisibility(node.node().attribute("visibility").value());
        variable->setType(node.node().attribute("type").value());

        //Add created variable to collection
        if(variable->getVisibility().compare("private") == 0) {
            classe->addPrivateVariable(variable);
        } else {
            variable->setVisibility("public");
            classe->addPublicVariable(variable);
        }
    }
}

void ClassParser::parseFunction(pugi::xpath_node& node){
    pugi::xpath_node_set nFonctions = node.node().select_nodes(".//function");

    Fonction* function;
    for(pugi::xpath_node_set::const_iterator itF = nFonctions.begin(); itF != nFonctions.end(); itF++){
        pugi::xpath_node node = *itF;
        function = new Fonction();
        function->setName(node.node().attribute("name").value());
        function->setVisibility(node.node().attribute("visibility").value());
        function->setType(node.node().attribute("type").value());
        //pugi::xpath_node_set nParameters = node.node().select_nodes(".//parameter");

        //add created function to collection
        if(function->getVisibility().compare("private") == 0){
            classe->addPrivateFunction(function);
        } else{
            function->setVisibility("public");
            classe->addPublicFunction(function);
        }
    }
}

void ClassParser::createFiles(){
    //Create Header File and Source File
    bool resultHeaderFile;
    bool resultSourceFile;
    HeaderFileCreator hfc (classe, folder);
    SourceFileCreator sfc (classe, folder);
    resultHeaderFile = hfc.writeHeaderFile();
    resultSourceFile = sfc.writeSourceFile();
}
