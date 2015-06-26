//
// Created by lukas on 26.04.15.
//

#ifndef ITP4_ENGINEHELPER_H
#define ITP4_ENGINEHELPER_H


#include "src/scene/Loader.h"
#include "src/input/IInput.h"
#include "gameElements/Hexfield.h"
#include <src/overlay/Overlay.h>
#include <src/overlay/Label.h>


class Hexfield;

class EngineHelper {
public:
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
    std::shared_ptr <mgf::Label> health;
    std::shared_ptr <mgf::Label> mana;
    std::shared_ptr <mgf::Label> player;


    EngineHelper();

    glm::vec3 getMousePos();

    void setPointer();

    std::shared_ptr<mgf::IOverlayElement> getOverlayOnPos();

    void createField();

    void clearField();

    void initEngine();


    void createMenuOverlay();

    void createGameOverlay();

    void destroyMenu();

    void destroyGame();

    void printStatus(int status, std::string object);

    void processMenuLeftClick();
};


#endif //ITP4_ENGINEHELPER_H
