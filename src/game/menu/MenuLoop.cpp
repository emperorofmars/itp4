//
// Created by guenter on 24/06/15.
//

#include <iostream>
#include "MenuLoop.h"
#include "../EngineHelper.h"

int MenuLoop::run(std::shared_ptr <EngineHelper> engine) {
    bool quit = false;

    while (!quit) {
        std::cout << "MenuLoop running." << std::endl;

        quit = (engine->input->getQuit());
    }

    return 0;
}

MenuLoop::MenuLoop() {
    mStateContext = Context::getInstance();
}
