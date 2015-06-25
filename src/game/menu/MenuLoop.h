//
// Created by guenter on 24/06/15.
//

#ifndef ITP4_MENULOOP_H
#define ITP4_MENULOOP_H


#include "../EngineHelper.h"
#include "../states/Context.h"

class MenuLoop {
public:
    MenuLoop();
    int run(std::shared_ptr <EngineHelper> engine);

    std::deque <int> input;
private:
    std::shared_ptr <Context> mStateContext;
};


#endif //ITP4_MENULOOP_H
