//
// Created by guenter on 24/06/15.
//

#ifndef ITP4_SETTINGS_H
#define ITP4_SETTINGS_H


#include <src/overlay/Overlay.h>
#include <src/scene/Node.h>
#include "../EngineHelper.h"

class Settings {
public:
    Settings();

    std::shared_ptr <mgf::Node> settingsScene;
    std::shared_ptr <mgf::Overlay> settingsOverlay;

    void createSettingsOverlay(std::shared_ptr<EngineHelper> engine);

    void destroy();
};


#endif //ITP4_SETTINGS_H
