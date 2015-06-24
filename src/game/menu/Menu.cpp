//
// Created by guenter on 23/06/15.
//

#include <src/overlay/Button.h>
#include "Menu.h"

Menu::Menu() {
    actualScene.reset(new mgf::Node("scene"));

    menuOverlay.reset(new mgf::Overlay());

    std::shared_ptr <mgf::Button> saveBtn(new mgf::Button("saveBtn"));
    saveBtn->setBackground("res/images/elemente/save.png");

    menuOverlay->add(saveBtn);
}