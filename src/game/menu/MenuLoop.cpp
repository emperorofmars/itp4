//
// Created by guenter on 24/06/15.
//

#include <iostream>
#include "MenuLoop.h"
#include "../EngineHelper.h"

MenuLoop::MenuLoop() {
    mStateContext = Context::getInstance();
}

int MenuLoop::run(std::shared_ptr <EngineHelper> engine) {
    bool quit = false;

    while (!quit) {
        std::cout << "MenuLoop running." << std::endl;

        engine->input->update();
        quit = (engine->input->getQuit());

        engine->setPointer();

        //###############################################  Controls
        bool leftClick = engine->input->getMouseClick()[0];
        bool rightClick = engine->input->getMouseClick()[2];
        bool middleClick = engine->input->getMouseClick()[1];

        if (middleClick) {
            mouseMidDown = true;
        }
        if (leftClick) {
            mouseLeftDown = true;
        }
        if (rightClick) {
            mouseRightDown = true;
        }

        if (mouseMidDown && !middleClick) {
            eventsQueue.push(InputEvent::EVENT_MIDDLECLICK);
            mouseMidDown = false;
        } else if (mouseLeftDown && !leftClick) {
            eventsQueue.push(InputEvent::EVENT_LEFTCLICK);
            mouseLeftDown = false;
        } else if (mouseRightDown && !rightClick) {
            eventsQueue.push(InputEvent::EVENT_RIGHTCLICK);
            mouseRightDown = false;
        } else {
            eventsQueue.push(InputEvent::EVENT_NOEVENT);
        }

        if (!eventsQueue.empty()) {
            //LOG_F_TRACE(GAME_LOG_PATH, "Event processing");
            mStateContext->handle(eventsQueue.front());
            eventsQueue.pop();
        }


//###############################################  Rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)));

        engine->actualScene->render(engine->renderer); //rendering on gpu happens here
        engine->overlay->render(engine->renderer);


        engine->w->swap(); //display the rendered image on screen

//###############################################  Calculate fps
        current = SDL_GetTicks();
        frametime = current - last;
        last = current;
        //std::cerr << "FPS: " << 1000.f / frametime << std::endl;	//show fps
    }
//###############################################  Gameloop end

    LOG_F_TRACE(GAME_LOG_PATH, "starting clean up!");
    mGame->cleanUp();

    LOG_F_TRACE(GAME_LOG_PATH, "cleanup complete, exiting");

    return 0;
}
