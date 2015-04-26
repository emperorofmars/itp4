//
// Created by Lukas Stanek on 12/04/15.
//

#include "Unit.h"

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
    curHP = maxHP;
    timesDefended = 0;
    remainingMovement = movement;

    return unit;
}


Hexfield Unit::moveTo(Hexfield field) {
    return Hexfield();
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

