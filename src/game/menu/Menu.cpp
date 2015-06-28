//
// Created by guenter on 23/06/15.
//

#include <src/overlay/Button.h>
#include "Menu.h"

Menu::Menu() {
    std::cout << "Entered menu constructor." << std::endl;
}

void Menu::create(std::shared_ptr<EngineHelper> engine) {
    std::cout << "Creating menu..." << std::endl;

    engine->actualScene.reset(new mgf::Node("menuScene"));
    engine->overlay.reset(new mgf::Overlay());

    /*
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

    /*
     * Set mouse pointer
     */
    engine->pointer.reset(new mgf::Label("mouse"));
    engine->pointer->setBackground("res/images/Mouse.png");
    engine->pointer->translate(glm::vec2(-10.f, -10.f));

    /*
     * Add elements to Overlay
     */
    engine->overlay->add(quitBtn);
    engine->overlay->add(startBtn);
    engine->overlay->add(settingsBtn);
    engine->overlay->add(engine->pointer);
}

void Menu::destroy() {
    std::cout << "Destroying menu..." << std::endl;
}