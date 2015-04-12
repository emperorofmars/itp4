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
    shared_ptr<Player> mNext;

    void setName(std::string name);
    std::string getName();
    void setColor(vec4 color);
    glm::vec4 getColor();
    void setNext(shared_ptr<Player> player);
    shared_ptr<Player> getNext();

private:
    std::string name;
    glm::vec4 color;


};


#endif //ITP4_PLAYER_H
