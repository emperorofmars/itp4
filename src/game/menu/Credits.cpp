//
// Created by guenter on 6/30/15.
//

#include <ostream>
#include <iostream>
#include <src/scene/Node.h>
#include "Credits.h"
#include "Menu.h"
#include "MenuLoop.h"

Credits::Credits(std::shared_ptr<EngineHelper> engine): mEngine(engine) {
    //mStateContext = Context::getInstance();
    createCreditsOverlay();
}

void Credits::createCreditsOverlay() {
    std::cout << "Creating credits overlay." << std::endl;
    // Set Scene and Overlay
    mEngine->actualScene.reset(new mgf::Node("creditsScene"));
    mEngine->overlay.reset(new mgf::Overlay());

    /*
     * Create elements for overlay
     */
    float width = 0.0f;
    float height = 0.2f;
    float dividend = 0.4f;

    if (mEngine->isCurrentDisplayMode()) dividend = 0.5f;
    std::cout << dividend << std::endl;

    // Create labels
    std::shared_ptr <mgf::Label> credit1(new mgf::Label("credit1"));
    credit1->setBackground("res/images/elemente/transparent.png");
    credit1->setFont("res/fonts/main.ttf");
    credit1->setText("Engine:\nMartin Schwarz");
    width = (dividend/mEngine->w->getAspectRatio() + credit1->getScale()[0]);
    std::cout << width << "x" << height << " (Fullscreen Label)" << std::endl;
    credit1->translate(glm::vec2(width, height));
    mEngine->overlay->add(credit1);

    std::shared_ptr <mgf::Label> credit2(new mgf::Label("credit2"));
    credit1->setBackground("res/images/elemente/transparent.png");
    credit1->setFont("res/fonts/main.ttf");
    credit1->setText("Logic:\nLukas Stanek");
    height += 0.05f;
    credit2->translate(glm::vec2(width, height));
    mEngine->overlay->add(credit2);

    std::shared_ptr <mgf::Label> credit3(new mgf::Label("credit3"));
    credit1->setBackground("res/images/elemente/transparent.png");
    credit1->setFont("res/fonts/main.ttf");
    credit1->setText("Guenter Kubicki");
    height += 0.05f;
    credit3->translate(glm::vec2(width, height));
    mEngine->overlay->add(credit3);

    // Create buttons
    backBtn.reset(new mgf::Button("backBtn"));
    backBtn->setBackground("res/images/elemente/back.png");
    height += 0.05f;
    backBtn->translate(glm::vec2(width, height));

    saveBtn.reset(new mgf::Button("saveBtn"));
    saveBtn->setBackground("res/images/elemente/save.png");
    saveBtn->translate(glm::vec2(width + 0.2f, height)); // height stays the same as back button

    // Add buttons to overlay
    mEngine->overlay->add(backBtn);
    mEngine->overlay->add(saveBtn);
    mEngine->overlay->add(mEngine->pointer);
}

int Credits::run() {
    mBack = false;

    bool    mouseMidDown = false,
            mouseLeftDown = false,
            mouseRightDown = false;

    bool running = false;

    while (!mBack) {
        if (!running) {
            std::cout << "CreditsLoop running." << std::endl;
            running = true;
        }

        mEngine->input->update();
        mBack = (mEngine->input->getQuit());

        mEngine->setPointer();

        /*
         * Controls
         */
        bool leftClick = mEngine->input->getMouseClick()[0];
        bool midClick = mEngine->input->getMouseClick()[1];
        bool rightClick = mEngine->input->getMouseClick()[2];

//        if (midClick) mouseMidDown = true;
        if (leftClick) mouseLeftDown = true;
//        if (rightClick) mouseRightDown = true;

        if (mouseLeftDown && !leftClick) {
            processCreditsLeftClick();
            mouseLeftDown = false;
        }

        /*
         * Rendering
         */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)));

        mEngine->actualScene->render(mEngine->renderer); //rendering on gpu happens here
        mEngine->overlay->render(mEngine->renderer);

        mEngine->w->swap(); //display the rendered image on screen
    }
    return 0;
}

int Credits::quit() {
    Menu menu;
    menu.create(mEngine);    // creates menu overlay

    MenuLoop menuLoop(mEngine);
    menuLoop.run();

    return 0;
}

void Credits::processCreditsLeftClick() {
    std::shared_ptr<mgf::IOverlayElement> elm = mEngine->getOverlayOnPos();

    if (elm) {
        if (elm->getName() == "backBtn") {
            std::cout << "Back button clicked." << std::endl;
            quit();
        }
    }
}
