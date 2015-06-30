//
// Created by guenter on 24/06/15.
//

#include <src/overlay/Button.h>
#include "Settings.h"
#include "../EngineHelper.h"
#include "MenuLoop.h"
#include "Menu.h"

Settings::Settings(std::shared_ptr<EngineHelper> engine): mEngine(engine) {
    mStateContext = Context::getInstance();
    createSettingsOverlay();
}

void Settings::createSettingsOverlay() {
    std::cout << "Creating settings overlay." << std::endl;
    // Set Scene and Overlay
    mEngine->actualScene.reset(new mgf::Node("settingsScene"));
    mEngine->overlay.reset(new mgf::Overlay());

    /*
     * Create elements for overlay
     */
    float width = 0.0f;
    float height = 0.2f;
    float dividend = 0.3f;

    if (mEngine->isCurrentDisplayMode()) dividend = 0.4f;
    std::cout << dividend << std::endl;

    // Create labels
    std::shared_ptr <mgf::Label> settingFullscreen(new mgf::Label("settingFullscrn"));
    settingFullscreen->setBackground("res/images/elemente/fullscreen.png");
    width = (dividend/mEngine->w->getAspectRatio() + settingFullscreen->getScale()[0]);
//    height = (0.2f/mEngine->w->getAspectRatio() + settingFullscreen->getScale()[1]);
    std::cout << width << "x" << height << " (Fullscreen Label)" << std::endl;
    settingFullscreen->translate(glm::vec2(width, height));

    std::shared_ptr <mgf::Label> settingRes(new mgf::Label("settingRes"));
    settingRes->setBackground("res/images/elemente/resolution.png");
    height += 0.05f;
    settingRes->translate(glm::vec2(width, height));

    std::shared_ptr <mgf::Button> fullScreenChooseBtn(new mgf::Button("fullScreenChooseBtn"));
    fullScreenChooseBtn->setBackground("res/images/elemente/transparent.png");
    fullScreenChooseBtn->setText("No");
    fullScreenChooseBtn->translate(glm::vec2(width+0.3f, height));
    mEngine->overlay->add(fullScreenChooseBtn);

    // Create buttons
    backBtn.reset(new mgf::Button("backBtn"));
    backBtn->setBackground("res/images/elemente/back.png");
    height += 0.05f;
    backBtn->translate(glm::vec2(width, height));

    saveBtn.reset(new mgf::Button("saveBtn"));
    saveBtn->setBackground("res/images/elemente/save.png");
    saveBtn->translate(glm::vec2(width + 0.2f, height)); // height stays the same as back button

    // Add buttons to overlay
    mEngine->overlay->add(settingFullscreen);
    mEngine->overlay->add(settingRes);
    mEngine->overlay->add(backBtn);
    mEngine->overlay->add(saveBtn);
    mEngine->overlay->add(mEngine->pointer);
}

int Settings::run() {
    mBack = false;

    bool    mouseMidDown = false,
            mouseLeftDown = false,
            mouseRightDown = false;

    bool running = false;

    while (!mBack) {
        if (!running) {
            std::cout << "SettingsLoop running." << std::endl;
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

        if (midClick) mouseMidDown = true;
        if (leftClick) mouseLeftDown = true;
        if (rightClick) mouseRightDown = true;

        if (mouseLeftDown && !leftClick) {
            processSettingsLeftClick();
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

int Settings::quit() {
    Menu menu;
    menu.create(mEngine);    // creates menu overlay

    MenuLoop menuLoop(mEngine);
    menuLoop.run();

    return 0;
}

void Settings::processSettingsLeftClick() {
    std::shared_ptr<mgf::IOverlayElement> elm = mEngine->getOverlayOnPos();

    if (elm) {
        if (elm->getName() == "backBtn") {
            std::cout << "Back button clicked." << std::endl;
            quit();
        }
    }
}

