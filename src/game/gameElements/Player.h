//
// Created by Lukas Stanek on 12/04/15.
//

#ifndef ITP4_PLAYER_H
#define ITP4_PLAYER_H


#include <iostream>
#include <vector>

#include <memory>
#include "Unit.h"

class Unit;

class Player {
public:
    Player(std::string name);

    ~Player();

    std::shared_ptr <Player> mNext;
    std::shared_ptr <std::vector<std::shared_ptr < Unit>> >
    mUnits;

    int getId();

    void setId(int id);

    void setName(std::string name);

    std::string getName();

    //void setColor(vec4 color);
    //glm::vec4 getColor();
    void setNext(std::shared_ptr <Player> player);

    std::shared_ptr <Player> getNext();

    std::shared_ptr <std::vector<std::shared_ptr < Unit>>>

    getUnits();

    void setUnits(std::shared_ptr <std::vector<std::shared_ptr < Unit>>

    >);

    void setBase(std::shared_ptr <Unit> base);

    std::shared_ptr <Unit> getBase();

    int getMaxMana() const;
    void setMaxMana(int maxMana);
    int getCurMana() const;
    void setCurMana(int curMana);
    bool useMana(int amount);
    void gainMana(int amount);
private:
    int id;
    std::string name;
    std::shared_ptr <Unit> baseTower;

    int maxMana;
    int curMana;
    //glm::vec4 color;


};


#endif //ITP4_PLAYER_H
