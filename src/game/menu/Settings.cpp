//
// Created by guenter on 24/06/15.
//

#include <src/overlay/Button.h>
#include "Settings.h"
#include "../EngineHelper.h"

Settings::Settings(std::shared_ptr<EngineHelper> engine): mEngine(engine) {
    mStateContext = Context::getInstance();
}

void Settings::createSettingsOverlay() {
    std::cout << "Creating settings overlay." << std::endl;
    // Set Scene and Overlay
    mEngine->actualScene.reset(new mgf::Node("settingsScene"));
    mEngine->overlay.reset(new mgf::Overlay());

    // Create buttons
    std::shared_ptr <mgf::Button> saveBtn(new mgf::Button("saveBtn"));
    saveBtn->setBackground("res/images/elemente/save.png");
    saveBtn->translate(glm::vec2(0.5f, 0.5f));


    std::shared_ptr <mgf::Button> backBtn(new mgf::Button("backBtn"));
    backBtn->setBackground("res/images/elemente/back.png");
    backBtn->translate(glm::vec2(0.3f, 0.5f));

    // Add buttons to overlay
    mEngine->overlay->add(saveBtn);
    mEngine->overlay->add(backBtn);
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

        leftClick ? mouseLeftDown = true : mouseLeftDown = false;
        midClick ? mouseMidDown = true : mouseMidDown = false;
        rightClick ? mouseRightDown = true : mouseRightDown = false;

        if (mouseLeftDown && !leftClick) {
            mEngine->processSettingsLeftClick();
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
