//
// Created by lukas on 26.04.15.
//

#include <src/camera/CameraTopDown.h>
#include <src/input/InputTopDown.h>
#include "EngineHelper.h"

EngineHelper::EngineHelper() {
    w.reset(new mgf::Window("Clash of Mages", 1000, 800, 0, 0));
    input.reset(new mgf::InputTopDown);

    p.reset(new mgf::ShaderProgram);
    p->addShader("res/shader/vertex_shader.glsl", GL_VERTEX_SHADER);
    p->addShader("res/shader/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    p->createProgram();

    cam.reset(new mgf::CameraTopDown(90, w->getAspectRatio(), 1000.f, 0.1f));

    renderer.reset(new mgf::Renderer(w, cam, p));

    root.reset(new mgf::Node("root"));
    root->add(l.load("res/models/cube/cube.obj"));
    root->add(l.load("res/models/hex/hex.obj"));
    root->add(l.load("res/models/scene/scene.obj"));
    root->print();

    actualScene.reset(new mgf::Node("scene"));

}
