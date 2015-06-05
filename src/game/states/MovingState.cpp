/*
** Author:  Lukas Stanek on 04.06.15.
** File:    MovingState.cpp
** Project: Turn based Strategy Game
*/

#include "MovingState.h"
#include "../../tbs.h"

void MovingState::handleEvent(InputEvent event) {

    std::shared_ptr<Unit> movingUnit = mGame->getSelectedUnit();
    glm::vec3 currentTranslation = movingUnit->getUnitNode()->getTranslation();

    if(movingUnit->getDestination() == nullptr){
        mContext->setCurrentState(States::STATE_SELECTED);
        return;
    }

    bool standingOnDestination = (currentTranslation == movingUnit->getDestination()->mPositionVector);
    bool noMovesRemaining = (movingUnit->getRemainingMovement() < 0);
    if(noMovesRemaining || standingOnDestination){
        mContext->setCurrentState(States::STATE_SELECTED);
        return;
    }



    bool checkpointReached = (currentTranslation == movingUnit->getCurrentHexfield()->mPositionVector);


    if(checkpointReached){
        //movingUnit->setRemainingMovement(movingUnit->getRemainingMovement()-1);
        movingUnit->moveTo(movingUnit);

        glm::vec3 destTranslation = movingUnit->getCurrentHexfield()->mPositionVector;

        glm::vec3 diff = currentTranslation - destTranslation;

        mStepSizeX = diff[0]/10;
        mStepSizeY = diff[2]/10;

        mActualTranslationAdded[0] = mStepSizeX*(-1);
        mActualTranslationAdded[2] = mStepSizeY*(-1);



        LOG_F_TRACE(GAME_LOG_PATH, "calc Stepsize X: ", mStepSizeX);
        LOG_F_TRACE(GAME_LOG_PATH, "calc Stepsize Y: ", mStepSizeY);
    }


    mFinalTranslation = currentTranslation + mActualTranslationAdded;


    float tolerance = 0.11f;
    glm::vec3 destTranslation = movingUnit->getCurrentHexfield()->mPositionVector;

    if(mFinalTranslation[0] <= destTranslation[0] + tolerance &&
            mFinalTranslation[0] >= destTranslation[0] - tolerance){
        mFinalTranslation[0] = destTranslation[0];
    }

    if(mFinalTranslation[2] <= destTranslation[2] + tolerance &&
       mFinalTranslation[2] >= destTranslation[2] - tolerance){
        mFinalTranslation[2] = destTranslation[2];
    }


    movingUnit->getUnitNode()->setTranslation(mFinalTranslation);

}
