/*
** Author:  Lukas Stanek on 04.06.15.
** File:    MovingState.h
** Project: Turn based Strategy Game
*/

#ifndef ITP4_MOVINGSTATE_H
#define ITP4_MOVINGSTATE_H


#include "State.h"

class MovingState : public State {

public:
    MovingState(const std::shared_ptr<Context> &ctx) : State(ctx) {
        mName = "MOVING";
    }

    virtual void handleEvent(InputEvent event) override;
private:
    float mStepSizeX = 0;
    float mStepSizeY = 0;
    glm::vec3 mFinalTranslation;
    glm::vec3 mActualTranslationAdded;

};


#endif //ITP4_MOVINGSTATE_H
