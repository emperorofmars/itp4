/*
** Author:  Lukas Stanek on 04.06.15.
** File:    SelectedState.cpp
** Project: Turn based Strategy Game
*/

#include "SelectedState.h"
#include "../../tbs.h"

void SelectedState::handleEvent(InputEvent event) {
    State::handleEvent(event);

    if (interfaceInt) {
        return;
    }

    if (event == InputEvent::EVENT_RIGHTCLICK) {
        handleRightClick();
    }

    if (event == InputEvent::EVENT_LEFTCLICK) {
        handleLeftClick();
    }
}


void SelectedState::handleRightClick() {
    std::shared_ptr <Unit> selectedUnit = mGame->getSelectedUnit();
    if (selectedUnit->getOwner() != mGame->getCurrentPlayerId()) return;

    LOG_F_TRACE(GAME_LOG_PATH, "locating clicked hex");

    std::shared_ptr <Hexfield> dest = mGame->getHexAtMousePos();

    LOG_F_TRACE(GAME_LOG_PATH, "pos: ", dest->mPosition[1], " / ", dest->mPosition[0]);

    if (dest->getIsOccupied()) {
        if (selectedUnit->isInRange(dest)
            && dest->getOccupation()->getOwner() != mGame->getCurrentPlayerId()
            && selectedUnit->getRemainingMovement() > 0) {

            LOG_F_TRACE(GAME_LOG_PATH, "Target is enemy and in range");
            bool hit = selectedUnit->attack(dest->getOccupation());

            if(hit){
                mGame->dmgedUnit[0] = dest->getOccupation();
                mGame->unitDmgCounter[0] = 0;
                std::shared_ptr<mgf::Material> newmat(new mgf::Material);
                newmat->mDiffuseColor = glm::vec4(1.f, 0.f, 0.f, 1.f);
                dest->getOccupation()->getUnitNode()->setMaterial(newmat);
            }
            if (dest->getIsOccupied()) {
                bool counterHit = dest->getOccupation()->counterAttack(selectedUnit);
                if(counterHit){
                    mGame->dmgedUnit[1] = selectedUnit;
                    mGame->unitDmgCounter[1] = 0;
                    std::shared_ptr<mgf::Material> newmat(new mgf::Material);
                    newmat->mDiffuseColor = glm::vec4(1.f, 0.f, 0.f, 1.f);
                    selectedUnit->getUnitNode()->setMaterial(newmat);
                }
            }

            if (selectedUnit->getCurHp() <= 0) {
                mGame->deselectUnit();
                mContext->setCurrentState(States::STATE_IDLE);
            }

            return;
        } else {
            LOG_F_TRACE(GAME_LOG_PATH, "Target NOT in Range or friendly or No Moves remaining!");
        }
    }

    selectedUnit->setDestination(dest);
    mContext->setCurrentState(States::STATE_MOVING);

}


void SelectedState::handleLeftClick() {

    std::shared_ptr <Hexfield> clickedHex = mGame->getHexAtMousePos();

    if (clickedHex->getIsOccupied()) {
        mGame->deselectUnit();
        mGame->selectUnit(clickedHex->getOccupation());
    } else {
        mContext->setCurrentState(States::STATE_IDLE);
        mGame->deselectUnit();
        LOG_F_TRACE(GAME_LOG_PATH, "IDLE -- deselection");
    }
}
