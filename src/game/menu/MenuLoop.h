//
// Created by guenter on 24/06/15.
//

#ifndef ITP4_MENULOOP_H
#define ITP4_MENULOOP_H


#include "../EngineHelper.h"
#include "../states/Context.h"

class MenuLoop {
public:
    MenuLoop();

    int run(std::shared_ptr < EngineHelper > engine);

private:
    std::shared_ptr <Context> mStateContext;

    bool quit;

    //Graphics stuff
    std::shared_ptr <mgf::Window> w;
    std::shared_ptr <mgf::Renderer> renderer;

    std::shared_ptr <mgf::Node> actualScene;
    std::shared_ptr <mgf::Overlay> overlay;

    std::shared_ptr <EngineHelper> mEngine;

    void processMenuLeftClick();
};


#endif //ITP4_MENULOOP_H
