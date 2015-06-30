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
#include "../startUp.h"
#include "Settings.h"

MenuLoop::MenuLoop(std::shared_ptr<EngineHelper> engine): mEngine(engine) {
    //mStateContext = Context::getInstance();
    startGame = false;
    //mStateContext = Context::getInstance();
}


int MenuLoop::run() {
    std::cout << "Starting menu loop..." << std::endl;

    quit = false;
    float current = 0, last = 0, frametime = 0;

//    bool mouseMidDown = false;
    bool mouseLeftDown = false;
//    bool mouseRightDown = false;

    bool running = false;

    while (!quit) {
        if (!running) {
            std::cout << "MenuLoop running." << std::endl;
            running = true;
        }

        mEngine->input->update();
        quit = (mEngine->input->getQuit());

        mEngine->setPointer();

        //###############################################  Controls
        bool leftClick = mEngine->input->getMouseClick()[0];
//        bool rightClick = mEngine->input->getMouseClick()[2];
//        bool middleClick = mEngine->input->getMouseClick()[1];

//        if (middleClick) {
//            mouseMidDown = true;
//        }
        if (leftClick) {
            mouseLeftDown = true;
        }
//        if (rightClick) {
//            mouseRightDown = true;
//        }

        if (mouseLeftDown && !leftClick) {
            processMenuLeftClick();
            mouseLeftDown = false;
        }

//###############################################  Rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)));

        mEngine->actualScene->render(mEngine->renderer); //rendering on gpu happens here
        mEngine->overlay->render(mEngine->renderer);


        mEngine->w->swap(); //display the rendered image on screen

//###############################################  Calculate fps
        current = SDL_GetTicks();
        frametime = current - last;
        last = current;
        //std::cerr << "FPS: " << 1000.f / frametime << std::endl;	//show fps
    }
//###############################################  MenuLoop end


    if(startGame){
        startUp(mEngine);
        return 0;
    }
    return 1;

}

void MenuLoop::processMenuLeftClick() {
    std::shared_ptr<mgf::IOverlayElement> elm = mEngine->getOverlayOnPos();

    if (elm) {
        if (elm->getName() == "startBtn") {
            startGame = true;
            quit = true;
        } else if (elm->getName() == "settingsBtn") {
            std::cout << "Settings starting now!" << std::endl;
            Settings settings(mEngine);
            std::cout << "DEBUG settings 01" << std::endl;
            settings.run();
        } else if (elm->getName() == "quitBtn") {
            std::cout << "Exiting now!" << std::endl;
            exit(0);
        }
    }
}