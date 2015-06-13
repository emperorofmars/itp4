/*
** Author:  Lukas Stanek on 04.06.15.
** File:    State.cpp
** Project: Turn based Strategy Game
*/

#include "State.h"
#include "../../tbs.h"

void State::setGame(std::shared_ptr<Game> ptr) {
    mGame = ptr;
}

State::State(std::shared_ptr<Context> ctx) {
    mContext = ctx;
    mName = "State";
}

void State::handleEvent(InputEvent event) {

    if(event == InputEvent::EVENT_MIDDLECLICK){
        handleMiddleClick();
    }else if(event == InputEvent::EVENT_LEFTCLICK){
        LOG_F_TRACE(GAME_LOG_PATH, "General State: handling left click event");
        handleInterfaceClick();
    }

}

void State::handleMiddleClick() {
    mGame->nextTurn();
}

void State::handleLeftClick() {


}

void State::handleInterfaceClick(){
    LOG_F_TRACE(GAME_LOG_PATH, "handle left click");
    std::shared_ptr<mgf::IOverlayElement> element = mGame->getOverlayInteraction();

    if(element){
        reactToInterfaceInteraction(element);
    }
}


void State::handleRightClick() {
    //ignoring by default
}

std::string State::getName() {
    return mName;
}

State::~State() {
    LOG_F_TRACE(GAME_LOG_PATH, "Destroying State ", getName());
}


void State::reactToInterfaceInteraction(std::shared_ptr<mgf::IOverlayElement> element) {
    if(element->getName() == "endTurn"){
        mGame->nextTurn();
    }

}
