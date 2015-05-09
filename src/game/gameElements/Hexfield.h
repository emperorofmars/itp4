#ifndef HEXFIELD_H
#define HEXFIELD_H

#include <vector>
#include <memory>
#include <src/scene/Node.h>
#include "Unit.h"

class Unit;

class Hexfield{
public:
    Hexfield();
    void setOccupation(std::shared_ptr<Unit> unit);
    std::shared_ptr<Unit> getOccupation();
    bool getIsOccupied();

    void setEmtpy();
    //TODO write getter for position
    float mPosition[2];
    glm::vec3 mPositionVector;
    //TODO write getter for linked to
    std::shared_ptr<Hexfield> linkedTo[6];

    int mIsRendered = 0;

    std::string printPos();

    void setEngineObjectRef(std::shared_ptr<mgf::Node> EngineObjectRef);
private:
    int mTerrain;
    std::shared_ptr< Unit > occupation;
    bool isOccupied;

//TODO change signature to shared_ptr mgf::node
    std::shared_ptr<mgf::Node> mEngineObjectRef;
    
};


#endif // HEXFIELD_H


