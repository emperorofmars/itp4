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
    interfaceInt = false;
}

void State::handleEvent(InputEvent event) {

    if(event == InputEvent::EVENT_MIDDLECLICK){
        handleMiddleClick();
    }else if(event == InputEvent::EVENT_LEFTCLICK){
        LOG_F_TRACE(GAME_LOG_PATH, "General State: handling left click event");
        interfaceInt = handleInterfaceClick();
        return;
    }

    interfaceInt = false;
}

void State::handleMiddleClick() {
    mGame->nextTurn();
}

void State::handleLeftClick() {


}

bool State::handleInterfaceClick(){
    LOG_F_TRACE(GAME_LOG_PATH, "handle left click");
    std::shared_ptr<mgf::IOverlayElement> element = mGame->getOverlayInteraction();

    if(element){
        return reactToInterfaceInteraction(element);
    }

    return false;
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


bool State::reactToInterfaceInteraction(std::shared_ptr<mgf::IOverlayElement> element) {
    LOG_F_TRACE(GAME_LOG_PATH, "clicked on UI");
    if(element->getName() == "endTurnBtn"){
        LOG_F_TRACE(GAME_LOG_PATH, "NextTurn Button pushed");
        mGame->nextTurn();
        return true;
    }else if(element->getName() == "infantryBtn"){
        LOG_F_TRACE(GAME_LOG_PATH, "button: produce IN");
        mGame->produceUnit("Infanterie", mGame->getCurrentPlayerId());

        return true;
    }else if(element->getName() == "cavalryBtn") {
        LOG_F_TRACE(GAME_LOG_PATH, "button: produce CA");
        mGame->produceUnit("Kavallerie", mGame->getCurrentPlayerId());

        return true;
    }else if(element->getName() == "artilleryBtn") {
        LOG_F_TRACE(GAME_LOG_PATH, "button: produce AT");
        mGame->produceUnit("Artillerie", mGame->getCurrentPlayerId());

        return true;
    }else if(element->getName() == "quitBtn") {
        LOG_F_TRACE(GAME_LOG_PATH, "button: Quit");
        mGame->quitGame();
        return true;
    }

    return false;
}
