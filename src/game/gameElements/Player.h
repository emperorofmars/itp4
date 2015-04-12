//
// Created by Lukas Stanek on 12/04/15.
//

#ifndef ITP4_PLAYER_H
#define ITP4_PLAYER_H


#include <iostream>
#include <vector>

class Player {
public:

    std::string &getName() const {
        return name;
    }

    void setName(std::string &name) {
        Player::name = name;
    }

    std::vector const &getColor() const {
        return color;
    }

    void setColor(std::vector const &color) {
        Player::color = color;
    }

private:
    std::string name;
    std::vector color;


};


#endif //ITP4_PLAYER_H
