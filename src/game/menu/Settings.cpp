//
// Created by guenter on 24/06/15.
//

#include <src/overlay/Button.h>
#include "Settings.h"
#include "../EngineHelper.h"

Settings::Settings() {

}

void Settings::createSettingsOverlay(std::shared_ptr<EngineHelper> engine) {
    // Set Scene and Overlay
    engine->actualScene.reset(new mgf::Node("settingsScene"));
    engine->overlay.reset(new mgf::Overlay());

    // Create buttons
    std::shared_ptr <mgf::Button> saveBtn(new mgf::Button("saveBtn"));
    saveBtn->setBackground("res/images/elemente/save.png");
    saveBtn->translate(glm::vec2(0.4f, 0.9f));


    std::shared_ptr <mgf::Button> backBtn(new mgf::Button("backBtn"));
    backBtn->setBackground("res/images/elemente/back.png");
    backBtn->translate(glm::vec2(0.6f, 0.9f));

    // Add buttons to overlay
    engine->overlay->add(saveBtn);
    engine->overlay->add(backBtn);
}
