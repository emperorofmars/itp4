#ifndef HEXFIELD_H
#define HEXFIELD_H

#include <vector>
#include "Unit.h"

class Hexfield{
public:
    Hexfield();
    void setOccupation(Unit unit);

private:
    int terrain;
    Unit isOccupied;

    int position[2];

    Hexfield *linkedTo[6];

    int renderId;



};


#endif // HEXFIELD_H
