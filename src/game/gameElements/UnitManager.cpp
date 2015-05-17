/*
** Author:  Lukas Stanek
** File:    UnitManager.cpp
** Project: Turn Based Strategy Game
*/


#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "UnitManager.h"
#include "../../tbs.h"

UnitManager* UnitManager::mInstance = 0;

UnitManager::UnitManager() {

}

UnitManager::~UnitManager() {
    for(int i = 0; i < mPrototypes.size(); ++i){
        mPrototypes.at(i).reset();
    }
    LOG_F_TRACE(GAME_LOG_PATH, "destroying unitManager");
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
    configFile.open(pathToConfig);


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

    std::cout << "Units successfully loaded" << std::endl << std::endl;

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


std::vector< std::shared_ptr< Unit > >  UnitManager::getList() {
    return mPrototypes;
}


void UnitManager::printPrototypesToCout() {
    for(auto &prototype : mPrototypes){
        std::cout << prototype->getType() <<
        std::endl << prototype->getName() <<
        std::endl << prototype->getMaxHP() <<
        std::endl << prototype->getDmg() <<
        std::endl << prototype->getHitChance() <<
        std::endl << prototype->getRange() <<
        std::endl << prototype->getMovement() <<
        std::endl << std::endl;
    }
}

std::shared_ptr<Unit> UnitManager::getChild(std::string name) {
    for(std::shared_ptr<Unit> unit : mPrototypes){
        if(unit->getName() == name){
            return unit;
        }
    }
    return NULL;
}
