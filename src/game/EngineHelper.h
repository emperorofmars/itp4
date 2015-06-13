//
// Created by lukas on 26.04.15.
//

#ifndef ITP4_ENGINEHELPER_H
#define ITP4_ENGINEHELPER_H


#include "src/scene/Loader.h"
#include "src/input/IInput.h"
#include "gameElements/Hexfield.h"

class Hexfield;

class EngineHelper {
public:
    std::shared_ptr<mgf::Window> w;
    std::shared_ptr<mgf::IInput> input;
    std::shared_ptr<mgf::ShaderProgram> p;
    std::shared_ptr<mgf::ICamera> cam;
    std::shared_ptr<mgf::Renderer> renderer;
    mgf::Loader l;

    std::shared_ptr<mgf::Node> root;
    std::shared_ptr<mgf::Node> actualScene;

    EngineHelper();
    glm::vec3 getMousePos();
};


#endif //ITP4_ENGINEHELPER_H
