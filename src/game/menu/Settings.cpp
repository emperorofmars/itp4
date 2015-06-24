//
// Created by guenter on 24/06/15.
//

#include <src/overlay/Button.h>
#include "Settings.h"

Settings::Settings() {

}

void Settings::create() {
    // Set Scene and Overlay
    settingsScene.reset(new mgf::Node("settingsScene"));
    settingsOverlay.reset(new mgf::Overlay());

    // Create buttons
    std::shared_ptr <mgf::Button> saveBtn(new mgf::Button("saveBtn"));
    saveBtn->setBackground("res/images/elemente/save.png");

    std::shared_ptr <mgf::Button> backBtn(new mgf::Button("backBtn"));
    backBtn->setBackground("res/images/elemente/back.png");

    // Add buttons to overlay
    settingsOverlay->add(saveBtn);
    settingsOverlay->add(backBtn);
}
