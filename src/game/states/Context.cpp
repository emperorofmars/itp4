/*
** Author:  Lukas Stanek on 04.06.15.
** File:    Context.cpp
** Project: Turn based Strategy Game
*/

#include "Context.h"
#include "../../libs/mlog.h"
#include "../../tbs.h"
#include "IdleState.h"

using namespace std;

/*
 * Singleton Implementation
 */

std::shared_ptr<Context> Context::getInstance() {
    if(instance == NULL){
        instance = new Context(STATE_IDLE);
    }

    return instance;
}


/*
 * Actual Impl
 */

Context::Context(states) {
    std::shared_ptr<State> newState = std::shared_ptr<State>(new IdleState());
    mStates.push_back(newState);



    mCurrentState = mStates[0];
}

void Context::setCurrentState(states state) {
    switch(state){
        case STATE_IDLE: mCurrentState = mStates[0]; break;
        case STATE_SELECTED: ; break;
        case STATE_MOVING: ; break;
        case STATE_FIGHT: ; break;
        default: LOG_D_ERROR(GAME_LOG_PATH, "No valid State"); break;
    }
}

std::shared_ptr<State> Context::getCurrentState() {
    return mCurrentState;
}