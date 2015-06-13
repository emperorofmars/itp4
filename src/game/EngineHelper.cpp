//
// Created by lukas on 26.04.15.
//

#include "src/camera/CameraTopDown.h"
#include "src/input/InputTopDown.h"
#include "src/collision/MouseRay.h"
#include "src/collision/RayPlane.h"
#include "EngineHelper.h"
#include "gameElements/Hexfield.h"

EngineHelper::EngineHelper() {
    w.reset(new mgf::Window("Clash of Mages", 1000, 800, 0, 0));
    input.reset(new mgf::InputTopDown);

    p.reset(new mgf::ShaderProgram);
    p->addShader("res/shader/vertex_shader.glsl", GL_VERTEX_SHADER);
    p->addShader("res/shader/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    p->createProgram();

    cam.reset(new mgf::CameraTopDown(90, w->getAspectRatio(), 1000.f, 0.1f));
    cam->setPos(glm::vec3(25.f, 20.f, 35.f));

    renderer.reset(new mgf::Renderer(w, cam, p));

    root.reset(new mgf::Node("root"));
    //root->add(l.load("res/models/cube/cube.obj"));
    //root->add(l.load("res/models/hex/hex.obj"));
    //root->add(l.load("res/models/scene/scene.obj"));
    //root->add(l.load("res/models/tower/tower.obj"));
    root->add(l.load("res/models/assets/Assets.obj"));
    root->print();

    actualScene.reset(new mgf::Node("scene"));

    std::shared_ptr<mgf::Light> light(new mgf::Light());
    light->mColor = glm::vec3(0.7f, 0.8f, 1.f);
    light->mPosition = glm::vec3(5.f, 15.f, 15.f);
    renderer->addLight(light, glm::mat4(1));
    light->mColor = glm::vec3(0.7f, 0.8f, 1.f);
    light->mPosition = glm::vec3(0.f, 10.f, -5.f);
    renderer->addLight(light, glm::mat4(1));


}

glm::vec3 EngineHelper::getMousePos() {
    glm::vec3 mray = mgf::calculateMouseRay(cam->getP(), cam->getV(), input->getMouseAbsolute(), glm::vec2(1000, 800));
    glm::vec3 mpoint = mgf::colLinePlane(cam->getPos(), mray, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

    return mpoint;
}
