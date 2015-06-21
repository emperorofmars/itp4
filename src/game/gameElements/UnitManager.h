/*
** Author:  Lukas Stanek
** File:    UnitManager.h
** Project: Turn Based Strategy Game
*/


#ifndef ITP4_UNITMANAGER_H
#define ITP4_UNITMANAGER_H

#include <vector>
#include "Unit.h"

class UnitManager {
public:
    static UnitManager *getInstance();


    void loadProtoypes();

    std::vector <std::shared_ptr<Unit>> getList();

    void printPrototypesToCout();

    std::shared_ptr <Unit> getChild(std::string name);

private:
    UnitManager();

    ~UnitManager();

    static UnitManager *mInstance;

    std::vector <std::shared_ptr<Unit>> mPrototypes;

    std::shared_ptr <Unit> parseLine(std::string);

};


#define pathToConfig "res/units.txt"


#endif //ITP4_UNITMANAGER_H
