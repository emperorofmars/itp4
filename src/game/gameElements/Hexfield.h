#ifndef HEXFIELD_H
#define HEXFIELD_H

#include <vector>
#include "Unit.h"

class Hexfield{
public:
    void setOccupation(Unit unit);

private:
    int terrain;
    Unit isOccupied;

    std::vector position;

    Hexfield *linkedTo[6];

    int renderId;



};


#endif // HEXFIELD_H
