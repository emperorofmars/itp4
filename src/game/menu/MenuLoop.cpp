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

MenuLoop::MenuLoop() {
    mStateContext = Context::getInstance();
}


int MenuLoop::run(std::shared_ptr<EngineHelper> engine) {
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
            processLeftClick();
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
//###############################################  Gameloop end

    LOG_F_TRACE(GAME_LOG_PATH, "starting clean up!");
//    cleanUp();

    LOG_F_TRACE(GAME_LOG_PATH, "cleanup complete, exiting");

    return 0;
}

void MenuLoop::processLeftClick() {
    //TODO check overlay etc

    std::shared_ptr<mgf::IOverlayElement> elm = getOverlayOnPos();
    if (elm) {
        //TODO process element
        if (elm->getName() == "startBtn") {
            startUp();
        } else if (elm->getName() == "quitBtn") {
            quit = true;
        }

    }
}

//void MenuLoop::init() {
//    w.reset(new mgf::Window("Clash of Mages - Menu", 1000, 800, 0, 0));
//    input.reset(new mgf::InputTopDown);
//
//    p.reset(new mgf::ShaderProgram);
//    p->addShader("res/shader/vertex_shader.glsl", GL_VERTEX_SHADER);
//    p->addShader("res/shader/fragment_shader.glsl", GL_FRAGMENT_SHADER);
//    p->createProgram();
//
//    cam.reset(new mgf::CameraTopDown(40, w->getAspectRatio(), 1000.f, 0.1f));
//    cam->setPos(glm::vec3(25.f, 40.f, 35.f));
//
//    renderer.reset(new mgf::Renderer(w, cam, p));
//
//    root.reset(new mgf::Node("root"));
//    actualScene.reset(new mgf::Node("scene"));
//
//    root->add(l.load("res/models/assets/alt/Assets.obj"));
//
//    root->print();
//
//    createOverlay();
//}

glm::vec3 MenuLoop::getMousePos() {
    glm::vec3 mray = mgf::calculateMouseRay(cam->getP(), cam->getV(), input->getMouseAbsolute(), glm::vec2(1000, 800));
    glm::vec3 mpoint = mgf::colLinePlane(cam->getPos(), mray, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

    return mpoint;
}

void MenuLoop::setPointer() {
    pointer->setPos(glm::vec2(input->getMouseAbsoluteNDC(w->getResolution())[0],
                              input->getMouseAbsoluteNDC(w->getResolution())[1] / w->getAspectRatio()));

}

std::shared_ptr<mgf::IOverlayElement> MenuLoop::getOverlayOnPos() {
    std::shared_ptr<mgf::IOverlayElement> elm = overlay->getMouseOverNDC
            (input->getMouseAbsoluteNDC(w->getResolution()), w->getAspectRatio());
    return elm;
}