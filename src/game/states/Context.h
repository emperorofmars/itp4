/*
** Author:  Lukas Stanek on 04.06.15.
** File:    Context.h
** Project: Turn based Strategy Game
*/

#ifndef ITP4_CONTEXT_H
#define ITP4_CONTEXT_H


#include <bits/shared_ptr.h>
#include <bits/stl_vector.h>
#include <bits/stringfwd.h>
#include <bits/basic_string.h>
#include "State.h"

class Context {
public:
    static std::shared_ptr<Context> getInstance();

    static enum states {STATE_IDLE, STATE_SELECTED, STATE_MOVING, STATE_FIGHT};

    void setCurrentState(states);
    std::shared_ptr<State> getCurrentState();

private:
    //Singleton handling
    Context(states);
    static std::shared_ptr<Context> instance;

    //actual implementation
    std::shared_ptr<State> mCurrentState;

    std::vector<std::shared_ptr<State>> mStates;



};


#endif //ITP4_CONTEXT_H
