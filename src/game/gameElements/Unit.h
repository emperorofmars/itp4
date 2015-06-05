//
// Created by Lukas Stanek on 12/04/15.
//

#ifndef ITP4_UNIT_H
#define ITP4_UNIT_H


#include <iosfwd>
#include <string>
#include <bits/stl_queue.h>
#include "Player.h"
#include "../../libs/mlog.h"
#include "Hexfield.h"
#include "../EngineHelper.h"

class Hexfield;
class Player;

class Unit {
public:
    std::shared_ptr<Hexfield> moveTo(std::shared_ptr<Hexfield> destination, std::shared_ptr<Unit> self);
    bool isInRange(std::shared_ptr<Hexfield> target);
    std::shared_ptr<Hexfield> checkRange(std::shared_ptr<Hexfield> start, std::shared_ptr<Hexfield> target);

    void attack(std::shared_ptr<Unit> target);
    void getHit(int dmg);

    Unit();
    ~Unit();
    Unit(std::shared_ptr<Unit> original);
    std::shared_ptr<Unit> clone();

    void printStats();

private:
    int owner;
    std::shared_ptr<Hexfield> mCurrentHexfield;
    std::shared_ptr<mgf::Node> mUnitNode;
    glm::vec3 destination;

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
    int getOwner();
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

    void setOwner(int id);
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
    void setCurrentHexfield(std::shared_ptr<Hexfield> hexfield);
    std::shared_ptr<Hexfield> getCurrentHexfield();

    void setUnitNode(std::shared_ptr<mgf::Node> node);
    std::shared_ptr<mgf::Node> getUnitNode();


};


#endif //ITP4_UNIT_H
