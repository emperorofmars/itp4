/*
** Author:  Lukas Stanek on 04.06.15.
** File:    State.cpp
** Project: Turn based Strategy Game
*/

#include "State.h"

void State::setGame(std::shared_ptr<Game> ptr) {
    mGame = ptr;
}

State::State(std::shared_ptr<Context> ctx) {
    mContext = ctx;

}

void State::handleEvent(InputEvent event) {

}

void State::handleMiddleClick() {
    mGame->nextTurn();
}

void State::handleLeftClick() {
    //ignoring by default
}

void State::handleRightClick() {
    //ignoring by default
}
