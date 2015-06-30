//
// Created by guenter on 23/06/15.
//

#include <src/overlay/Button.h>
#include "Menu.h"

Menu::Menu() {
    std::cout << "Creating menu." << std::endl;
}

Menu::~Menu() {
    root.reset();
    actualScene.reset();
    menuOverlay.reset();
}

void Menu::create(std::shared_ptr<EngineHelper> engine) {

    engine->actualScene.reset(new mgf::Node("menuScene"));
    engine->overlay.reset(new mgf::Overlay());

    /*
     * Create buttons
     */
    float width;
    float height;
    std::shared_ptr<mgf::Button> startBtn(new mgf::Button("startBtn"));

    startBtn->setBackground("res/images/elemente/play.png");
    width = (0.4/engine->w->getAspectRatio() + startBtn->getScale()[0]);
    height = (0.2/engine->w->getAspectRatio() + startBtn->getScale()[1]);
    std::cout << width <<"x"<< height << std::endl;
    startBtn->translate(glm::vec2(width, height));
    engine->overlay->add(startBtn);

    std::shared_ptr<mgf::Button> settingsBtn(new mgf::Button("settingsBtn"));
    settingsBtn->setBackground("res/images/elemente/settings.png");
    width = (0.4/engine->w->getAspectRatio() + settingsBtn->getScale()[0]);
//    height = (0.3/engine->w->getAspectRatio() + settingsBtn->getScale()[1]);
    height += 0.1;
    std::cout << width <<"x"<< height << std::endl;
    settingsBtn->translate(glm::vec2(width, height));
    engine->overlay->add(settingsBtn);

    std::shared_ptr<mgf::Button> quitBtn(new mgf::Button("quitBtn"));
    quitBtn->setBackground("res/images/elemente/quit.png");
    width = (0.4/engine->w->getAspectRatio() + quitBtn->getScale()[0]);
//    height = (0.4/engine->w->getAspectRatio() + quitBtn->getScale()[1]);
    height += 0.1;
    std::cout << width <<"x"<< height << std::endl;
    quitBtn->translate(glm::vec2(width, height));
    engine->overlay->add(quitBtn);

    /*
     * Set mouse pointer
     */
    engine->pointer.reset(new mgf::Label("mouse"));
    engine->pointer->setBackground("res/images/Mouse.png");
    engine->pointer->translate(glm::vec2(-10.f, -10.f));

    /*
     * Add elements to Overlay
     */
    engine->overlay->add(engine->pointer);
}

