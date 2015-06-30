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
    float x = 0.0;
    float y = 0.0;
    float dividend = 0.4;

    if (engine->isCurrentDisplayMode()) dividend = 0.5;
    std::cout << dividend << std::endl;

    std::shared_ptr<mgf::Label> titleLbl(new mgf::Label("titleLbl"));
    titleLbl->setBackground("res/images/elemente/transparent.png");
    titleLbl->setFont("res/fonts/main.ttf");
    titleLbl->setText("Clash of Mages");
    titleLbl->setColor(glm::vec3(255,165,0)); // some green
    x = (dividend/engine->w->getAspectRatio() + titleLbl->getScale()[0]);
    titleLbl->scale(glm::vec2(4,2));
    titleLbl->translate(glm::vec2(x, 0.0f));
    engine->overlay->add(titleLbl);

    std::shared_ptr<mgf::Button> startBtn(new mgf::Button("startBtn"));
    startBtn->setBackground("res/images/elemente/play.png");
    x = (dividend/engine->w->getAspectRatio() + startBtn->getScale()[0]);
    y = (0.3f/engine->w->getAspectRatio() + startBtn->getScale()[1]);
    std::cout << x <<"x"<< y << " (Start Button)" << std::endl;
    startBtn->translate(glm::vec2(x, y));
    engine->overlay->add(startBtn);

    std::shared_ptr<mgf::Button> creditsBtn(new mgf::Button("creditsBtn"));
    creditsBtn->setBackground("res/images/elemente/credits.png");
    x = (dividend/engine->w->getAspectRatio() + creditsBtn->getScale()[0]);
    y += 0.1;
    std::cout << x <<"x"<< y << " (Settings Button)" << std::endl;
    creditsBtn->translate(glm::vec2(x, y));
    engine->overlay->add(creditsBtn);

//    std::shared_ptr<mgf::Button> settingsBtn(new mgf::Button("settingsBtn"));
//    settingsBtn->setBackground("res/images/elemente/settings.png");
//    x = (dividend/engine->w->getAspectRatio() + settingsBtn->getScale()[0]);
//    y += 0.1;
//    std::cout << x <<"x"<< y << " (Settings Button)" << std::endl;
//    settingsBtn->translate(glm::vec2(x, y));
//    engine->overlay->add(settingsBtn);

    std::shared_ptr<mgf::Button> quitBtn(new mgf::Button("quitBtn"));
    quitBtn->setBackground("res/images/elemente/quit.png");
    x = (dividend/engine->w->getAspectRatio() + quitBtn->getScale()[0]);
    y += 0.1;
    std::cout << x <<"x"<< y << " (Quit Button)" <<  std::endl;
    quitBtn->translate(glm::vec2(x, y));
    engine->overlay->add(quitBtn);

    /*
     * Set mouse pointer
     */
    engine->pointer.reset(new mgf::Label("mouse"));
    engine->pointer->setBackground("res/images/Mouse.png");
    engine->pointer->translate(glm::vec2(-10.f, -10.f));
    std::cout << x <<"x"<< y << " (Quit Button)" <<  std::endl;
    /*
     * Add elements to Overlay
     */
    engine->overlay->add(engine->pointer);
}

