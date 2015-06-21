//
// Created by Lukas on 18.04.2015.
//

#include <sstream>
#include "Hexfield.h"
#include "../../tbs.h"

Hexfield::Hexfield() {
    mTerrain = 0;
    mPosition[0] = 0;
    mPosition[1] = 0;
    isOccupied = false;
}

Hexfield::~Hexfield() {
    occupation.reset();

    //LOG_F_TRACE(GAME_LOG_PATH, "destroying Hex");
}


std::string Hexfield::printPos() {
    std::ostringstream ss;
    ss << mPosition[0];
    std::string s(ss.str());
    std::string pos = s + "/";

    std::ostringstream ss1;
    ss1 << mPosition[1];
    pos = pos + std::string(ss1.str());
    return pos;
}

float Hexfield::getDist(std::shared_ptr < Hexfield > target) {
    return (std::abs(target->mPosition[1] - mPosition[1])
            + std::abs(target->mPosition[0] - mPosition[0]));
}

std::shared_ptr <Hexfield> Hexfield::getNearestNeighbor(std::shared_ptr < Hexfield > target) {
    float minDist = INFINITY;
    std::shared_ptr <Hexfield> nearestNeighbor;

    for (std::shared_ptr <Hexfield> neighbor : linkedTo) {
        if (neighbor == NULL) continue;

        float curDist = neighbor->getDist(target);
        if (curDist < minDist) {
            nearestNeighbor = neighbor;
            minDist = curDist;
        }

    }
    return nearestNeighbor;
}

/**
 * Setter & Getter
 */

void Hexfield::setOccupation(std::shared_ptr < Unit > unit) {
    occupation = unit;
    isOccupied = true;
}

std::shared_ptr <Unit> Hexfield::getOccupation() {
    return occupation;
}

void Hexfield::setEngineObjectRef(std::shared_ptr < mgf::Node > EngineObjectRef) {
    this->mEngineObjectRef = EngineObjectRef;
}

void Hexfield::setEmtpy() {
    occupation.reset();
    isOccupied = false;
}

bool Hexfield::getIsOccupied() {
    return isOccupied;
}

