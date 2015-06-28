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


int MenuLoop::run() {
    quit = false;
    float current = 0, last = 0, frametime = 0;

    bool mouseMidDown = false;
    bool mouseLeftDown = false;
    bool mouseRightDown = false;


    while (!quit) {

        input->update();
        quit = (input->getQuit());

        setPointer();

        //###############################################  Controls
        bool leftClick = input->getMouseClick()[0];
        bool rightClick = input->getMouseClick()[2];
        bool middleClick = input->getMouseClick()[1];

        if (middleClick) {
            mouseMidDown = true;
        }
        if (leftClick) {
            mouseLeftDown = true;
        }
        if (rightClick) {
            mouseRightDown = true;
        }

//        if (mouseMidDown && !middleClick) {
//            eventsQueue.push(InputEvent::EVENT_MIDDLECLICK);
//            mouseMidDown = false;
//        } else
        if (mouseLeftDown && !leftClick) {
            processLeftClick();
            //eventsQueue.push(InputEvent::EVENT_LEFTCLICK);
            mouseLeftDown = false;
        }
//        else if (mouseRightDown && !rightClick) {
//            eventsQueue.push(InputEvent::EVENT_RIGHTCLICK);
//            mouseRightDown = false;
//        } else {
//            eventsQueue.push(InputEvent::EVENT_NOEVENT);
//        }

//        if (!eventsQueue.empty()) {
//            //LOG_F_TRACE(GAME_LOG_PATH, "Event processing");
//            mStateContext->handle(eventsQueue.front());
//            eventsQueue.pop();
//        }
//

//###############################################  Rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)));

        actualScene->render(renderer); //rendering on gpu happens here
        overlay->render(renderer);


        w->swap(); //display the rendered image on screen

//###############################################  Calculate fps
        current = SDL_GetTicks();
        frametime = current - last;
        last = current;
        //std::cerr << "FPS: " << 1000.f / frametime << std::endl;	//show fps
    }
//###############################################  Gameloop end

    LOG_F_TRACE(GAME_LOG_PATH, "starting clean up!");
    cleanUp();

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

void MenuLoop::init() {
    w.reset(new mgf::Window("Clash of Mages - Menu", 1000, 800, 0, 0));
    input.reset(new mgf::InputTopDown);

    p.reset(new mgf::ShaderProgram);
    p->addShader("res/shader/vertex_shader.glsl", GL_VERTEX_SHADER);
    p->addShader("res/shader/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    p->createProgram();

    cam.reset(new mgf::CameraTopDown(40, w->getAspectRatio(), 1000.f, 0.1f));
    cam->setPos(glm::vec3(25.f, 40.f, 35.f));

    renderer.reset(new mgf::Renderer(w, cam, p));

    root.reset(new mgf::Node("root"));
    actualScene.reset(new mgf::Node("scene"));

    root->add(l.load("res/models/assets/alt/Assets.obj"));

    root->print();

    createOverlay();


}


void MenuLoop::createOverlay() {
//#### Overlay
    overlay.reset(new mgf::Overlay());

    /**
     * Create buttons
     */
    std::shared_ptr<mgf::Button> startBtn(new mgf::Button("startBtn"));
    startBtn->setBackground("res/images/elemente/play.png");

    startBtn->translate(glm::vec2(0.4f, 0.1f));

    std::shared_ptr<mgf::Button> settingsBtn(new mgf::Button("settingsBtn"));
    settingsBtn->setBackground("res/images/elemente/settings.png");
    settingsBtn->translate(glm::vec2(0.4f, 0.2f));

    std::shared_ptr<mgf::Button> quitBtn(new mgf::Button("quitBtn"));
    quitBtn->setBackground("res/images/elemente/quit.png");
    quitBtn->translate(glm::vec2(0.4f, 0.3f));

    /**
     * Set mouse pointer
     */
    pointer.reset(new mgf::Label("mouse"));
    pointer->setBackground("res/images/Mouse.png");
    pointer->translate(glm::vec2(-10.f, -10.f));

    /**
     * Add elements to Overlay
     */

    overlay->add(quitBtn);
    overlay->add(startBtn);
    overlay->add(settingsBtn);
    overlay->add(pointer);
    overlay->add(background);

}

void MenuLoop::cleanUp() {

}


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