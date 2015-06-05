/*
** Author:  Lukas Stanek on 04.06.15.
** File:    SelectedState.cpp
** Project: Turn based Strategy Game
*/

#include "SelectedState.h"
#include "../../tbs.h"

void SelectedState::handleEvent(InputEvent event) {
    State::handleEvent(event);

    if(event == InputEvent::EVENT_RIGHTCLICK){
        handleRightClick();
    }

    if(event == InputEvent::EVENT_MIDDLECLICK){
        State::handleMiddleClick();
    }

    if(event == InputEvent::EVENT_LEFTCLICK){
        handleLeftClick();
    }
}


void SelectedState::handleRightClick() {
    std::shared_ptr<Unit> selectedUnit = mGame->getSelectedUnit();
    if(selectedUnit->getOwner() != mGame->getCurrentPlayerId()) return;

    LOG_F_TRACE(GAME_LOG_PATH, "locating clicked hex");

    std::shared_ptr<Hexfield> dest = mGame->getHexAtMousePos();

    LOG_F_TRACE(GAME_LOG_PATH, "pos: ", dest->mPosition[1], " / ", dest->mPosition[0]);

    if(dest->getIsOccupied()){
        if(selectedUnit->isInRange(dest) && dest->getOccupation()->getOwner() != mGame->getCurrentPlayerId()){
            LOG_F_TRACE(GAME_LOG_PATH, "Target is enemy and in range");
            selectedUnit->attack(dest->getOccupation());
            return;
        }else{
            LOG_F_TRACE(GAME_LOG_PATH, "Target NOT in Range or friendly!");
        }
    }

    selectedUnit->setDestination(dest);
    mContext->setCurrentState(States::STATE_MOVING);
    //mGame->unitMovementWrapper(selectedUnit, dest);

}


void SelectedState::handleLeftClick() {
    std::shared_ptr<Hexfield> clickedHex = mGame->getHexAtMousePos();

    if(clickedHex->getIsOccupied()){
        mGame->setSelectedUnit(clickedHex->getOccupation());
        //TODO highlight unit
    }else{
        mContext->setCurrentState(States::STATE_IDLE);
        LOG_F_TRACE(GAME_LOG_PATH, "IDLE -- deselection");
    }
}
