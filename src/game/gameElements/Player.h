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
    std::shared_ptr<Player> mNext;
    std::shared_ptr< std::vector < std::shared_ptr<Unit> > > mUnits;

    void setName(std::string name);
    std::string getName();
    //void setColor(vec4 color);
    //glm::vec4 getColor();
    void setNext(std::shared_ptr<Player> player);
    std::shared_ptr<Player> getNext();

    std::shared_ptr<std::vector < std::shared_ptr<Unit>>> getUnits();
    void setUnits(std::shared_ptr<std::vector< std::shared_ptr<Unit> > >);

private:
    std::string name;
    //glm::vec4 color;


};


#endif //ITP4_PLAYER_H
