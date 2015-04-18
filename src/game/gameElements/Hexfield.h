#ifndef HEXFIELD_H
#define HEXFIELD_H

#include <vector>
#include "Unit.h"

class Hexfield{
public:
    Hexfield();
    void setOccupation(Unit unit);
    int mPosition[2];
    std::shared_ptr<Hexfield> linkedTo[6];
private:
    int terrain;
    std::shared_ptr< Unit > isOccupied;


    int renderId;


};


#endif // HEXFIELD_H


