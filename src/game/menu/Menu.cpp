//
// Created by guenter on 23/06/15.
//

#include <src/overlay/Button.h>
#include "Menu.h"

Menu::Menu() {
    actualScene.reset(new mgf::Node("menuScene"));
    menuOverlay.reset(new mgf::Overlay());

    // Create buttons
    std::shared_ptr <mgf::Button> playBtn(new mgf::Button("playBtn"));
    playBtn->setBackground("res/images/elemente/play.png");

    std::shared_ptr <mgf::Button> settingsBtn(new mgf::Button("settingsBtn"));
    settingsBtn->setBackground("res/images/elemente/settings.png");

    std::shared_ptr <mgf::Button> quitBtn(new mgf::Button("quitBtn"));
    quitBtn->setBackground("res/images/elemente/quit.png");

    // Add buttons to overlay
    menuOverlay->add(playBtn);
    menuOverlay->add(settingsBtn);
    menuOverlay->add(quitBtn);
}