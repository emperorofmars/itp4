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
    static UnitManager* getInstance();
    void loadProtoypes();
    std::vector< std::shared_ptr<Unit> > getList();
    void printPrototypesToCout();

private:
    UnitManager();

    static UnitManager* mInstance;

    std::vector< std::shared_ptr<Unit> > mPrototypes;

    std::shared_ptr<Unit> parseLine(std::string);

};

//Lukas Windows: D:\Repos\itp4\src\units.txt
//Lukas Mac: /Users/Luke/Projects/itp4/src/units.txt

#define pathToConfig "/Users/Luke/Projects/itp4/src/units.txt"


#endif //ITP4_UNITMANAGER_H
