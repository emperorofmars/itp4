//
// Created by guenter on 24/06/15.
//

#ifndef ITP4_SETTINGS_H
#define ITP4_SETTINGS_H


#include <src/overlay/Overlay.h>
#include <src/scene/Node.h>

class Settings {
public:
    Settings();

    std::shared_ptr <mgf::Node> settingsScene;
    std::shared_ptr <mgf::Overlay> settingsOverlay;

    void create();

    void destroy();
};


#endif //ITP4_SETTINGS_H
