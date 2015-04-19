/*
** Author:  Lukas Stanek
** File:    UnitManager.cpp
** Project: Turn Based Strategy Game
*/


#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "UnitManager.h"

UnitManager* UnitManager::mInstance = 0;

UnitManager::UnitManager() {

}

UnitManager* UnitManager::getInstance() {
    if(mInstance == 0){
        mInstance = new UnitManager();
    }
    return mInstance;
}

void UnitManager::loadProtoypes(){
    std::ifstream configFile;
    std::cout << "opening config file " << std::endl;
    configFile.open("D:\\Repos\\itp4\\src\\units.txt");


    if(configFile.is_open()){
        std::string line;
        while(std::getline(configFile, line)){

            std::shared_ptr<Unit> newUnit = parseLine(line);
            mPrototypes.push_back(newUnit);
        }

        configFile.close();
    }else{
        //TODO Log Error
        std::cout << "could not open units.txt, check if the file exists and you have permission to read" << std::endl;
        exit(1);
    }

}


std::shared_ptr<Unit> UnitManager::parseLine(std::string lineString){
    std::stringstream line;
    line.str(lineString);

    std::string attribute;
    std::shared_ptr<Unit> unit(new Unit);

    int i = 0;
    while(std::getline(line, attribute, ' ')){
        int unitStat = 0;
        if(i>1){
            unitStat = atoi(attribute.c_str());
        }

        switch (i){
            case 0: unit->setType(attribute); break;
            case 1: unit->setName(attribute); break;
            case 2: unit->setMaxHP(unitStat); break;
            case 3: unit->setDmg(unitStat); break;
            case 4: unit->setRange(unitStat); break;
            case 5: unit->setHitChance(unitStat); break;
            case 6: unit->setMovement(unitStat); break;
            case 7: unit->setSightRadius(unitStat); break;
            case 8: unit->setManaCost(unitStat); break;
            default: std::cout << "config file formatting error" << std::endl; exit(1);
        }

        ++i;
    }

    return unit;
}


std::vector<Unit> UnitManager::getList() {
    return std::vector<Unit>();
}
