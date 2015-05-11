//
// Created by Lukas Stanek on 12/04/15.
//

#include <unistd.h>
#include "Unit.h"
#include "../../tbs.h"
#include "../EngineHelper.h"

Unit::Unit(){

}

Unit::Unit(std::shared_ptr<Unit> original) {
    type = original->type;
    name = original->name;

    maxHP = original->maxHP;
    dmg = original->dmg;
    range = original->range;
    hitChance = original->hitChance;
    movement = original->movement;
    sightRadius = original->sightRadius;
    manaCost = original->manaCost;

    //setting variable values to Max
    curHP = maxHP;
    timesDefended = 0;
    remainingMovement = movement;
}

std::shared_ptr<Unit> Unit::clone(){
    std::shared_ptr<Unit> unit(new Unit);

    unit->type = type;
    unit->name = name;

    unit->maxHP = maxHP;
    unit->dmg = dmg;
    unit->range = range;
    unit->hitChance = hitChance;
    unit->movement = movement;
    unit->sightRadius = sightRadius;
    unit->manaCost = manaCost;

    //setting variable values to Max
    unit->curHP = maxHP;
    unit->timesDefended = 0;
    unit->remainingMovement = movement;

    return unit;
}


std::shared_ptr<Hexfield> Unit::moveTo(std::shared_ptr<Hexfield> destination, std::shared_ptr<Unit> self) {
    float destinationXPos = destination->mPosition[1];
    float destinationYPos = destination->mPosition[0];

    LOG_F_TRACE(GAME_LOG_PATH, "POS: ", mCurrentHexfield->mPosition[1], "/", mCurrentHexfield->mPosition[0]);
    LOG_F_TRACE(GAME_LOG_PATH, "moving.. (dest: ", destination->mPosition[1], "/", destination->mPosition[0], ")");

    std::shared_ptr<Hexfield> nearestHex;
    float minDist;
    float curDist = INFINITY;

    minDist = std::abs(destinationXPos - mCurrentHexfield->mPosition[1])
              + std::abs(destinationYPos - mCurrentHexfield->mPosition[0]);

    nearestHex = mCurrentHexfield;
    //DEBUG var
    int i = 0;
    for(std::shared_ptr<Hexfield> neighbor : mCurrentHexfield->linkedTo){
        if(neighbor == NULL) continue;

        float xPos = neighbor->mPosition[1];
        float yPos = neighbor->mPosition[0];

        curDist = std::abs(destinationXPos - xPos)
                  + std::abs(destinationYPos - yPos);

        if(curDist < minDist){
            LOG_F_TRACE(GAME_LOG_PATH, i, "new low at ", neighbor->mPosition[1], "/", neighbor->mPosition[0]);
            minDist = curDist;
            nearestHex = neighbor;
        }
        ++i;
    }

    LOG_F_TRACE(GAME_LOG_PATH, "finished look up loop");


    if(nearestHex == mCurrentHexfield || remainingMovement <= 0){
    //if(nearestHex == mCurrentHexfield){
        LOG_F_TRACE(GAME_LOG_PATH, "final destination reached");
        return mCurrentHexfield;
    }

    mCurrentHexfield->setEmtpy();
    LOG_F_TRACE(GAME_LOG_PATH, "nearest hex is ", nearestHex->mPosition[1], "/", nearestHex->mPosition[0]);
    nearestHex->setOccupation(self);
    self->setCurrentHexfield(nearestHex);
    remainingMovement--;

    LOG_F_TRACE(GAME_LOG_PATH, "rem move ", remainingMovement);

    nearestHex = moveTo(destination, self);

    return nearestHex;
}


// Getter & Setter

std::string Unit::getType() {
    return type;
}

std::string Unit::getName() {
    return name;
}

int Unit::getMaxHP() {
    return maxHP;
}

int Unit::getCurHp() {
    return curHP;
}

int Unit::getDmg() {
    return dmg;
}

int Unit::getRange() {
    return range;
}

int Unit::getHitChance() {
    return hitChance;
}

int Unit::getMovement() {
    return movement;
}

int Unit::getRemainingMovement() {
    return remainingMovement;
}

int Unit::getSightRadius() {
    return sightRadius;
}

int Unit::getManaCost() {
    return manaCost;
}

int Unit::getTimesDefended() {
    return timesDefended;
}


void Unit::setType(std::string string) {
    type = string;
}

void Unit::setName(std::string string) {
    name = string;
}

void Unit::setMaxHP(int i) {
    maxHP = i;
}

void Unit::setCurHP(int i) {
    curHP = i;
}

void Unit::setDmg(int i) {
    dmg = i;
}

void Unit::setRange(int i) {
    range = i;
}

void Unit::setHitChance(int i) {
    hitChance = i;
}

void Unit::setMovement(int i) {
    movement = i;
}

void Unit::setRemainingMovement(int i) {
    remainingMovement = i;
}

void Unit::setSightRadius(int i) {
    sightRadius = i;
}

void Unit::setManaCost(int i) {
    manaCost = i;
}

void Unit::setTimesDefended(int i) {
    timesDefended = i;
}

void Unit::setCurrentHexfield(std::shared_ptr<Hexfield> hexfield) {
    mCurrentHexfield.reset();
    LOG_F_TRACE(GAME_LOG_PATH, hexfield->mPosition[1], "/", hexfield->mPosition[0]);
    mCurrentHexfield = hexfield;
}

std::shared_ptr<Hexfield> Unit::getCurrentHexfield() {
    return mCurrentHexfield;
}

void Unit::setUnitNode(std::shared_ptr<mgf::Node> node) {
    mUnitNode = node;
}

std::shared_ptr<mgf::Node> Unit::getUnitNode() { return mUnitNode; }

void Unit::printStats() {
    std::cout << type << std::endl
    << name << std::endl
    << curHP << "/" << maxHP << std::endl
    << dmg << std::endl
    << range << std::endl
    << hitChance << std::endl
    << remainingMovement << "/" << movement << std::endl
    << sightRadius << std::endl
    << manaCost << std::endl;

}
