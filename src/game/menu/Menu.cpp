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
    float width = 0.0;
    float height = 0.0;
    float dividend = 0.4;

    if (engine->isCurrentDisplayMode()) dividend = 0.5;
    std::cout << dividend << std::endl;

    std::shared_ptr<mgf::Button> startBtn(new mgf::Button("startBtn"));
    startBtn->setBackground("res/images/elemente/play.png");
    width = (dividend/engine->w->getAspectRatio() + startBtn->getScale()[0]);
    height = (0.2f/engine->w->getAspectRatio() + startBtn->getScale()[1]);
    std::cout << width <<"x"<< height << " (Start Button)" << std::endl;
    startBtn->translate(glm::vec2(width, height));
    engine->overlay->add(startBtn);

    std::shared_ptr<mgf::Button> settingsBtn(new mgf::Button("settingsBtn"));
    settingsBtn->setBackground("res/images/elemente/settings.png");
    width = (dividend/engine->w->getAspectRatio() + settingsBtn->getScale()[0]);
    height += 0.1;
    std::cout << width <<"x"<< height << " (Settings Button)" << std::endl;
    settingsBtn->translate(glm::vec2(width, height));
    engine->overlay->add(settingsBtn);

    std::shared_ptr<mgf::Button> quitBtn(new mgf::Button("quitBtn"));
    quitBtn->setBackground("res/images/elemente/quit.png");
    width = (dividend/engine->w->getAspectRatio() + quitBtn->getScale()[0]);
    height += 0.1;
    std::cout << width <<"x"<< height << " (Quit Button)" <<  std::endl;
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

