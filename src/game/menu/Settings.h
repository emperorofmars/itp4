//
// Created by guenter on 24/06/15.
//

#ifndef ITP4_SETTINGS_H
#define ITP4_SETTINGS_H


#include <src/overlay/Overlay.h>
#include <src/scene/Node.h>
#include "../EngineHelper.h"
#include "../states/Context.h"

class Settings {
public:
    Settings(std::shared_ptr<EngineHelper> engine);

    int run();

    std::shared_ptr<mgf::Button> backBtn;
    int quit();

private:
    std::shared_ptr <EngineHelper> mEngine;
    std::shared_ptr<Context> mStateContext;
    bool mBack;

    void createSettingsOverlay();

    void processSettingsLeftClick();
};


#endif //ITP4_SETTINGS_H
