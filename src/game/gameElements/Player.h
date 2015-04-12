//
// Created by Lukas Stanek on 12/04/15.
//

#ifndef ITP4_PLAYER_H
#define ITP4_PLAYER_H


#include <iostream>
#include <vector>

class Player {
public:
    Player();

    string getName() const {
        return name;
    }

    void setName(string name) {
        Player::name = name;
    }

    vec4 getColor() const {
        return color;
    }

    void setColor(vec4 color) {
        Player::color = color;
    }

private:
    std::string name;
    glm::vec4 color;


};


#endif //ITP4_PLAYER_H
