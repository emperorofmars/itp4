//
// Created by Lukas Stanek on 12/04/15.
//

#ifndef ITP4_UNIT_H
#define ITP4_UNIT_H


#include <iosfwd>
#include <string>
#include "Player.h"
#include "Hexfield.h"

class Hexfield;
class Player;

class Unit {
public:
    Hexfield moveTo(Hexfield field);

    Unit();
    Unit(std::shared_ptr<Unit> original);
    std::shared_ptr<Unit> clone();

private:
    std::shared_ptr<Player> owner;
    int renderId;

    //FINAL VALUES
    std::string type;
    std::string name;
    int maxHP;
    int dmg;
    int range;
    int hitChance;
    int movement;
    int sightRadius;
    int manaCost;

    //VARIABLE VALUES
    int curHP;
    int remainingMovement;
    int timesDefended;




public:
    std::string getType();
    std::string getName();
    int getMaxHP();
    int getCurHp();
    int getDmg();
    int getRange();
    int getHitChance();
    int getMovement();
    int getRemainingMovement();
    int getSightRadius();
    int getManaCost();
    int getTimesDefended();

    void setType(std::string);
    void setName(std::string);
    void setMaxHP(int);
    void setCurHP(int);
    void setDmg(int);
    void setRange(int);
    void setHitChance(int);
    void setMovement(int);
    void setRemainingMovement(int);
    void setSightRadius(int);
    void setManaCost(int);
    void setTimesDefended(int);


};


#endif //ITP4_UNIT_H
