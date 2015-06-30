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
    float height = 0.0f;
    float dividend = 0.4f;

    if (mEngine->isCurrentDisplayMode()) dividend = 0.5f;
    std::cout << dividend << std::endl;

    std::shared_ptr <mgf::Label> title1(new mgf::Label("title1"));
    title1->setBackground("res/images/elemente/transparent.png");
    title1->setFont("res/fonts/main.ttf");
    title1->setText("ITP 4");
    title1->setColor(glm::vec3(255,165,0));
    width = (dividend/mEngine->w->getAspectRatio() + title1->getScale()[0]);
    title1->scale(glm::vec2(2,1));
    title1->translate(glm::vec2(width,height));
//    width+=0.2f;
    mEngine->overlay->add(title1);

    // Create labels
    std::shared_ptr <mgf::Label> credit1(new mgf::Label("credit1"));
    credit1->setBackground("res/images/elemente/transparent.png");
    credit1->setFont("res/fonts/main.ttf");
    credit1->setText("Martin Schwarz");
    credit1->setColor(glm::vec3(255,165,0));
    width = (dividend/mEngine->w->getAspectRatio() + credit1->getScale()[0]);
    height += 0.12;
    std::cout << width << "x" << height << " (Fullscreen Label)" << std::endl;
    credit1->translate(glm::vec2(width, height));
    credit1->scale(glm::vec2(2,1));
    mEngine->overlay->add(credit1);

    std::shared_ptr <mgf::Label> credit2(new mgf::Label("credit2"));
    credit2->setBackground("res/images/elemente/transparent.png");
    credit2->setFont("res/fonts/main.ttf");
    credit2->setText("Lukas Stanek");
    credit2->setColor(glm::vec3(255,165,0));
    height += 0.1f;
    credit2->translate(glm::vec2(width, height));
    credit2->scale(glm::vec2(2,1));
    mEngine->overlay->add(credit2);

    std::shared_ptr <mgf::Label> credit3(new mgf::Label("credit3"));
    credit3->setBackground("res/images/elemente/transparent.png");
    credit3->setFont("res/fonts/main.ttf");
    credit3->setText("Guenter Kubicki");
    credit3->setColor(glm::vec3(255,165,0));
    height += 0.1f;
    credit3->translate(glm::vec2(width, height));
    credit3->scale(glm::vec2(2,1));
    mEngine->overlay->add(credit3);

    // Create buttons
    backBtn.reset(new mgf::Button("backBtn"));
    backBtn->setBackground("res/images/elemente/back.png");
    height += 0.15f;
    backBtn->translate(glm::vec2(width, height));

    // Add buttons to overlay
    mEngine->overlay->add(backBtn);
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
