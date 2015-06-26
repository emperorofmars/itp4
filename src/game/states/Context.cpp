/*
** Author:  Lukas Stanek on 04.06.15.
** File:    Context.cpp
** Project: Turn based Strategy Game
*/

#include "Context.h"
#include "../../libs/mlog.h"
#include "../../tbs.h"
#include "IdleState.h"
#include "SelectedState.h"
#include "MovingState.h"
#include "FightState.h"

using namespace std;

/*
 * Singleton Implementation
 */
std::shared_ptr <Context> Context::instance;

std::shared_ptr <Context> Context::getInstance() {

    if (instance == nullptr) {
        instance = std::shared_ptr<Context>(new Context());
        instance->initialize();
    }
    //static shared_ptr<Context> instance (new Context());
    return instance;
}


/*
 * Actual Impl
 */

Context::Context() {

}

void Context::setCurrentState(States s) {
    LOG_F_TRACE(GAME_LOG_PATH, "New State ");

    switch (s) {
        case States::STATE_IDLE:
            mCurrentState = mStates[0];
            break;
        case States::STATE_SELECTED:
            mCurrentState = mStates[1];
            break;
        case States::STATE_MOVING:
            mCurrentState = mStates[2];
            break;
        case States::STATE_FIGHT:
            mCurrentState = mStates[3];
            break;
    }
    LOG_F_TRACE(GAME_LOG_PATH, mCurrentState->getName());
}

std::shared_ptr <State> Context::getCurrentState() {
    return mCurrentState;
}

void Context::injectGameReference(std::shared_ptr < Game > game) {
    for (std::shared_ptr <State> state : mStates) {
        state->setGame(game);
    }

}

void Context::handle(InputEvent e) {
    mCurrentState->handleEvent(e);
}

void Context::initialize() {
    mStates.push_back(std::shared_ptr<State>(new IdleState(getInstance())));
    mStates.push_back(std::shared_ptr<State>(new SelectedState(getInstance())));
    mStates.push_back(std::shared_ptr<State>(new MovingState(getInstance())));
    //newState.reset(new FightState(getInstance()));
    //mStates.push_back(newState);

    mCurrentState = mStates[0];

    LOG_F_TRACE(GAME_LOG_PATH, "States loaded");
    for (int i = 0; i < mStates.size(); ++i) {
        LOG_F_TRACE(GAME_LOG_PATH, mStates[i]->getName());
    }

}
