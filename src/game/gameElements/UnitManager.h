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
    UnitManager getInstace();
    void readConfig();
    void loadProtoypes();
    std::vector< Unit > getList();


private:
    UnitManager();
    static UnitManager instance;
    std::vector prototypes;


};


#endif //ITP4_UNITMANAGER_H
