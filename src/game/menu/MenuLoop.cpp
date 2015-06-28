//
// Created by guenter on 24/06/15.
//

#include <iostream>
#include <src/camera/CameraTopDown.h>
#include <src/input/InputTopDown.h>
#include <src/overlay/Button.h>
#include <src/collision/MouseRay.h>
#include <src/collision/RayPlane.h>
#include "MenuLoop.h"
#include "../EngineHelper.h"
#include "../../tbs.h"
#include "../startUp.h"
#include "Menu.h"
#include "Settings.h"

MenuLoop::MenuLoop() {
    mStateContext = Context::getInstance();
}


int MenuLoop::run(std::shared_ptr<EngineHelper> engine) {
    mEngine = engine;
    std::cout << "Starting menu loop..." << std::endl;

    quit = false;
    float current = 0, last = 0, frametime = 0;

    bool mouseMidDown = false;
    bool mouseLeftDown = false;
    bool mouseRightDown = false;

    bool running = false;

    while (!quit) {
        if (!running) {
            std::cout << "MenuLoop running." << std::endl;
            running = true;
        }

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

        if (mouseLeftDown && !leftClick) {
            processMenuLeftClick();
            mouseLeftDown = false;
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
//###############################################  MenuLoop end

    return 0;
}

void MenuLoop::processMenuLeftClick() {
    std::shared_ptr<mgf::IOverlayElement> elm = mEngine->getOverlayOnPos();

    if (elm) {
        if (elm->getName() == "startBtn") {
            startUp(mEngine);
        } else if (elm->getName() == "settingsBtn") {
            std::cout << "Settings starting now!" << std::endl;
            Settings settings(mEngine);
            settings.run();
        } else if (elm->getName() == "quitBtn") {
            exit(0);
        }
    }
}