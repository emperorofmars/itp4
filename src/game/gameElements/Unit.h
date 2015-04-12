//
// Created by Lukas Stanek on 12/04/15.
//

#ifndef ITP4_UNIT_H
#define ITP4_UNIT_H


#include <iosfwd>
#include <string>
#include "Player.h"
#include "Hexfield.h"

class Unit {
public:
    Hexfield moveTo(Hexfield field);

    Unit copy();

private:
    std::string type;
    std::string name;

    int maxHP;
    int curHP;

    int dmg;
    int range;
    int hitChance;

    int movement;
    int remainingMovement;

    int sightRadius;
    int manaCost;

    int timesDefended;

    Player owner;
    int renderId;




};


#endif //ITP4_UNIT_H
