//
// Created by Lukas Stanek on 12/04/15.
//

#include "Player.h"

using namespace std;

Player::Player(std::string name) {
    this->name = name;
}





/*
 * Setter & Getter
 */

string Player::getName(){
    return name;
}

void Player::setName(string name) {
    Player::name = name;
}

//vec4 Player::getColor(){
//    return color;
//}

//void Player::setColor(vec4 color){
//    Player::color = color;
//}

void Player::setNext(shared_ptr<Player> player) {
    mNext = player;
}

shared_ptr<Player> Player::getNext() {
    return mNext;
}


