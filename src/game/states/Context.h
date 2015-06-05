/*
** Author:  Lukas Stanek on 04.06.15.
** File:    Context.h
** Project: Turn based Strategy Game
*/

#ifndef ITP4_CONTEXT_H
#define ITP4_CONTEXT_H


#include <memory>
#include <vector>
#include <string>
#include "State.h"
#include "../constants.h"


class State;

class Context {
public:
    static std::shared_ptr<Context> getInstance();

    void injectGameReference(std::shared_ptr<Game> game);
    void setCurrentState(States s);
    std::shared_ptr<State> getCurrentState();
    void handle(InputEvent e);
    void initialize();
private:
    //Singleton handling
    Context();
    static std::shared_ptr<Context> instance;

    //actual implementation
    std::shared_ptr<State> mCurrentState;

    std::vector< std::shared_ptr<State> > mStates;


};


#endif //ITP4_CONTEXT_H
