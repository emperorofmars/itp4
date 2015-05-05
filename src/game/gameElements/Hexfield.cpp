//
// Created by Lukas on 18.04.2015.
//

#include <sstream>
#include "Hexfield.h"

Hexfield::Hexfield() {
    mTerrain = 0;
    mPosition[0] = 0;
    mPosition[1] = 0;
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

/**
 * Setter & Getter
 */

void Hexfield::setOccupation(std::shared_ptr<Unit> unit) {
    isOccupied = unit;
    unit->setCurrentHexfield(std::shared_ptr<Hexfield>(this));
}

std::shared_ptr<Unit> Hexfield::getOccupation() {
    return isOccupied;
}

void Hexfield::setEngineObjectRef(std::shared_ptr<mgf::Node> EngineObjectRef) {
    this->mEngineObjectRef = EngineObjectRef;
}

void Hexfield::setEmtpy() {
    isOccupied.reset();
}
