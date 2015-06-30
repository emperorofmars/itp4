//
// Created by guenter on 6/30/15.
//

#ifndef ITP4_CREDITS_H
#define ITP4_CREDITS_H


#include <src/overlay/Button.h>
#include "../EngineHelper.h"
#include "../states/Context.h"

class Credits {
private:

    void createCreditsOverlay();

    void processCreditsLeftClick();

    std::shared_ptr<EngineHelper> mEngine;
    std::shared_ptr<Context> mStateContext;
    bool mBack;

public:
    Credits(std::shared_ptr<EngineHelper> engine);
    int run();
    std::shared_ptr<mgf::Button> backBtn;
    std::shared_ptr<mgf::Button> saveBtn;

    int quit();
};


#endif //ITP4_CREDITS_H
