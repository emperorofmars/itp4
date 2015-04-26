//
// Created by lukas on 26.04.15.
//

#ifndef ITP4_ENGINEHELPER_H
#define ITP4_ENGINEHELPER_H


#include <src/scene/Loader.h>
#include <src/util/Input.h>

class EngineHelper {
public:
    std::shared_ptr<mgf::Window> w;
    std::shared_ptr<mgf::Input> input;
    std::shared_ptr<mgf::ShaderProgram> p;
    std::shared_ptr<mgf::Camera> cam;
    std::shared_ptr<mgf::Renderer> renderer;
    mgf::Loader l;

    std::shared_ptr<mgf::Node> root;
    std::shared_ptr<mgf::Node> actualScene;

    EngineHelper();
};


#endif //ITP4_ENGINEHELPER_H
