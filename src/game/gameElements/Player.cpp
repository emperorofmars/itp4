//
// Created by Lukas Stanek on 12/04/15.
//

#include "Player.h"
#include "../../tbs.h"

using namespace std;

Player::Player(std::string name) {
    this->name = name;
    this->maxMana = 100;
    this->curMana = 100;
}


/*
 * Setter & Getter
 */

int Player::getId() {
    return id;
}

void Player::setId(int id) {
    this->id = id;
}


string Player::getName() {
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

void Player::setNext(shared_ptr < Player > player) {
    mNext = player;
}

shared_ptr <Player> Player::getNext() {
    return mNext;
}


std::shared_ptr <std::vector<std::shared_ptr < Unit>>>

Player::getUnits() {
    return mUnits;
}

void Player::setUnits(std::shared_ptr < vector < std::shared_ptr < Unit >> > units) {
    this->mUnits = units;
}


std::shared_ptr <Unit> Player::getBase() {
    return baseTower;
}

void Player::setBase(std::shared_ptr < Unit > base) {
    this->baseTower = base;
}

int Player::getMaxMana() const {
    return maxMana;
}

void Player::setMaxMana(int maxMana) {
    Player::maxMana = maxMana;
}

int Player::getCurMana() const {
    return curMana;
}

void Player::setCurMana(int curMana) {
    Player::curMana = curMana;
}

bool Player::useMana(int amount){
    LOG_F_TRACE(GAME_LOG_PATH, "cur/max ", curMana, "/", maxMana);
    if((curMana - amount) < 0){
        return false;
    }else{
        curMana -= amount;
        return true;
    }
}

void Player::gainMana(int amount){
    curMana += amount;
}

Player::~Player() {
    mNext.reset();
    baseTower->getCurrentHexfield()->setEmtpy();
    baseTower.reset();
    mUnits.reset();

    LOG_F_TRACE(GAME_LOG_PATH, "player destroyed");
}

bool Player::allDead() {
    bool allDead = true;

    for(int i = 0; i < mUnits->size(); ++i){
        if(!mUnits->at(i)->isDead()){
            allDead = false;
        }
    }

    return allDead;
}
