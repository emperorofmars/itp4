/*
** Author:  Lukas Stanek on 04.06.15.
** File:    IdleState.cpp
** Project: Turn based Strategy Game
*/

#include "IdleState.h"
#include "../../tbs.h"



void IdleState::handleEvent(InputEvent event) {
    State::handleEvent(event);


    if(event == InputEvent::EVENT_LEFTCLICK){
        LOG_F_TRACE(GAME_LOG_PATH, "IDLE -- Leftclick processing");
        handleLeftClick();
    }



}


void IdleState::handleLeftClick() {

    std::shared_ptr<Hexfield> clickedHex = mGame->getHexAtMousePos();

    if(clickedHex->getIsOccupied()){
        mGame->selectUnit(clickedHex->getOccupation());

        LOG_F_TRACE(GAME_LOG_PATH, "occupied");
        //TODO highlight unit
        mContext->setCurrentState(States::STATE_SELECTED);
        LOG_F_TRACE(GAME_LOG_PATH, "SELECTED -- unit selected");
    }else{

        LOG_F_TRACE(GAME_LOG_PATH, "IDLE -- empty field");
    }
}
