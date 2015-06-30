//
// Created by Lukas Stanek on 12/04/15.
//

#include <unistd.h>
#include "Unit.h"
#include "../../tbs.h"
#include "../EngineHelper.h"
#include "../util/ChanceSimulator.h"

Unit::Unit() {

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

std::shared_ptr<Unit> Unit::clone() {
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

    unit->modelName = modelName;
    return unit;
}


std::shared_ptr<Hexfield> Unit::moveTo(std::shared_ptr<Unit> self) {
    float destinationXPos = mDestination->mPosition[1];
    float destinationYPos = mDestination->mPosition[0];


    LOG_F_TRACE(GAME_LOG_PATH, "POS: ", mCurrentHexfield->mPosition[1], "/", mCurrentHexfield->mPosition[0]);
    LOG_F_TRACE(GAME_LOG_PATH, "moving.. (dest: ", mDestination->mPosition[1], "/", mDestination->mPosition[0], ")");

    std::shared_ptr<Hexfield> nearestHex;
    float minDist;
    float curDist = INFINITY;

    minDist = mCurrentHexfield->getDist(mDestination);
    nearestHex = mCurrentHexfield;

    //DEBUG var
    int i = 0;
    for (std::shared_ptr<Hexfield> neighbor : mCurrentHexfield->linkedTo) {
        if (neighbor == NULL) continue;

        curDist = neighbor->getDist(mDestination);

        if (curDist < minDist && !neighbor->getIsOccupied()) {
            LOG_F_TRACE(GAME_LOG_PATH, i, "new low at ", neighbor->mPosition[1], "/", neighbor->mPosition[0]);
            minDist = curDist;
            nearestHex = neighbor;
        }
        ++i;
    }

    LOG_F_TRACE(GAME_LOG_PATH, "finished look up loop");

    if (nearestHex == mCurrentHexfield || remainingMovement <= 0) {
        //if(nearestHex == mCurrentHexfield){
        LOG_F_TRACE(GAME_LOG_PATH, "final mDestination reached");
        mDestination.reset();
        return mCurrentHexfield;
    }

    mCurrentHexfield->setEmtpy();
    LOG_F_TRACE(GAME_LOG_PATH, "nearest hex is ", nearestHex->mPosition[1], "/", nearestHex->mPosition[0]);
    nearestHex->setOccupation(self);
    self->setCurrentHexfield(nearestHex);
    remainingMovement--;

    LOG_F_TRACE(GAME_LOG_PATH, "rem move ", remainingMovement);

    //nearestHex = moveTo(mDestination, self);

    return nearestHex;
}

bool Unit::isInRange(std::shared_ptr<Hexfield> target) {
    if (mCurrentHexfield == target) return false;

    std::shared_ptr<Hexfield> targetableHex = mCurrentHexfield;

    for (int i = 0; i < range; ++i) {
        targetableHex = checkRange(targetableHex, target);

        if (targetableHex == target) {
            return true;
        }
    }
    return false;

}

//TODO rename this method
std::shared_ptr<Hexfield> Unit::checkRange(std::shared_ptr<Hexfield> start,
                                           std::shared_ptr<Hexfield> target) {
    return start->getNearestNeighbor(target);
}

bool Unit::attack(std::shared_ptr<Unit> target) {
    LOG_F_TRACE(GAME_LOG_PATH, "attacking..");
    bool hit = false;

    //Drains all movement on Attack
    //remainingMovement -= remainingMovement;

    double chance = ChanceSimulator::getInstance()->getRandomHit();
    LOG_F_TRACE(GAME_LOG_PATH, "randomNumber: ", chance);
    if (chance <= hitChance) {
        hit = true;
    }
    //Printing Stats for debug
    printStats();

    if (hit) {
        LOG_F_TRACE(GAME_LOG_PATH, "HIT");
        target->getHit(this->dmg);
    } else {
        LOG_F_TRACE(GAME_LOG_PATH, "MISS");
    }

    return hit;
}


bool Unit::counterAttack(std::shared_ptr<Unit> attacker) {
    bool hit;
    if (timesDefended < 2) {
        LOG_F_TRACE(GAME_LOG_PATH, "Counter attack!");
        hit = attack(attacker);
        timesDefended++;
    } else {
        LOG_F_TRACE(GAME_LOG_PATH, "Defended to often.");
        hit = false;
    }

    return hit;
}

void Unit::getHit(int dmg) {
    //printStats();
    curHP -= dmg;
    if (curHP <= 0) {
        //TODO KILL UNIT
        LOG_F_TRACE(GAME_LOG_PATH, "Unit dead.");
        mUnitNode->setVisible(false);
        mCurrentHexfield->setEmtpy();
        mCurrentHexfield.reset();
        dead = true;
    }
}

// Getter & Setter
int Unit::getOwner() {
    return owner;
}

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

void Unit::setOwner(int id) {
    owner = id;
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
    << "Name: " << name << std::endl
    << "Health: " << curHP << "/" << maxHP << std::endl
    << "Dmg: " << dmg << std::endl
    << "Range: " << range << std::endl
    << "HitChange" << hitChance << std::endl
    << "Movement: " << remainingMovement << "/" << movement << std::endl
    << "SightRadius: " << sightRadius << std::endl
    << "ManaCost" << manaCost << std::endl
    << "TimesDefended: " << timesDefended << std::endl;

}


Unit::~Unit() {
    mCurrentHexfield.reset();
    mUnitNode.reset();
    LOG_F_TRACE(GAME_LOG_PATH, "Unit destroyed.");
}

void Unit::setDestination(std::shared_ptr<Hexfield> d) {
    mDestination = d;
}

std::shared_ptr<Hexfield> Unit::getDestination() {
    return mDestination;
}

void Unit::setModel(std::string string) {
    this->modelName = string;
}

std::string Unit::getModel() {
    return modelName;
}

bool Unit::isDead() const {
    return dead;
}
