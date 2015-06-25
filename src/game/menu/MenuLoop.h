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
    int run();
    void init();

private:
    std::shared_ptr <Context> mStateContext;

    void processLeftClick();
    void createOverlay();

    void cleanUp();

    bool quit;
    //Graphix stuff
    std::shared_ptr <mgf::Window> w;
    std::shared_ptr <mgf::IInput> input;
    std::shared_ptr <mgf::ShaderProgram> p;
    std::shared_ptr <mgf::ICamera> cam;
    std::shared_ptr <mgf::Renderer> renderer;
    mgf::Loader l;

    std::shared_ptr <mgf::Node> root;
    std::shared_ptr <mgf::Node> actualScene;
    std::shared_ptr <mgf::Overlay> overlay;
    std::shared_ptr <mgf::Label> pointer;

    std::shared_ptr <mgf::IOverlayElement> getOverlayOnPos();
    void setPointer();
    glm::vec3 getMousePos();
};


#endif //ITP4_MENULOOP_H
