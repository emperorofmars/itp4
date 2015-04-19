#ifndef HEXFIELD_H
#define HEXFIELD_H

#include <vector>
#include <memory>

class Hexfield{
public:
    Hexfield();
    //void setOccupation(Unit unit);
    float mPosition[2];
    std::shared_ptr<Hexfield> linkedTo[6];

    std::string printPos();
private:
    int mTerrain;
    //std::shared_ptr< Unit > isOccupied;


    int renderId;


};


#endif // HEXFIELD_H


