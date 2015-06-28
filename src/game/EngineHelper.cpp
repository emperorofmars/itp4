//
// Created by lukas on 26.04.15.
//

#include <src/overlay/Label.h>
#include <src/overlay/Button.h>
#include <src/overlay/Overlay.h>
#include <src/scene/LightNode.h>
#include "src/camera/CameraTopDown.h"
#include "src/input/InputTopDown.h"
#include "src/collision/MouseRay.h"
#include "src/collision/RayPlane.h"
#include "EngineHelper.h"
#include "startUp.h"
#include "menu/Menu.h"

EngineHelper::EngineHelper() {
    printStatus(1, "EngineHelper object");

    w.reset(new mgf::Window("Clash of Mages", 1000, 800, 0, 0));
    input.reset(new mgf::InputTopDown);

    p.reset(new mgf::ShaderProgram);
    p->addShader("res/shader/vertex_shader.glsl", GL_VERTEX_SHADER);
    p->addShader("res/shader/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    p->createProgram();

    cam.reset(new mgf::CameraTopDown(40, w->getAspectRatio(), 1000.f, 0.1f));
    cam->setPos(glm::vec3(25.f, 40.f, 35.f));

    renderer.reset(new mgf::Renderer(w, cam, p));

    root.reset(new mgf::Node("root"));
//    actualScene.reset(new mgf::Node("menuScene"));

    root->add(l.load("res/models/assets/alt/Assets.obj"));

    root->print();

    printStatus(2, "EngineHelper object");
}

void EngineHelper::processMenuLeftClick() {
    std::shared_ptr<mgf::IOverlayElement> elm = getOverlayOnPos();

    if (elm) {
        if (elm->getName() == "startBtn") {
            startUp((std::shared_ptr<EngineHelper>) this);
        } else if (elm->getName() == "settingsBtn") {
            std::cout << "Settings starting now!" << std::endl;
        } else if (elm->getName() == "quitBtn") {
            exit(0);
        }
    }
}

glm::vec3 EngineHelper::getMousePos() {
    glm::vec3 mray = mgf::calculateMouseRay(cam->getP(), cam->getV(), input->getMouseAbsolute(), glm::vec2(1000, 800));
    glm::vec3 mpoint = mgf::colLinePlane(cam->getPos(), mray, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

    return mpoint;
}

void EngineHelper::setPointer() {
    pointer->setPos(glm::vec2(input->getMouseAbsoluteNDC(w->getResolution())[0],
                              input->getMouseAbsoluteNDC(w->getResolution())[1] / w->getAspectRatio()));

}


std::shared_ptr <mgf::IOverlayElement> EngineHelper::getOverlayOnPos() {
    std::shared_ptr <mgf::IOverlayElement> elm = overlay->getMouseOverNDC
            (input->getMouseAbsoluteNDC(w->getResolution()), w->getAspectRatio());
    return elm;
}

/*
 * For debugging.
 */
void EngineHelper::printStatus(int status, std::string object) {
    if (status == 1) {
        std::cout << "Creating " << object << "..." << std::endl;
    } else if (status == 2) {
        std::cout << "Created " << object << "." << std::endl;
    } else {
        std::cout << object << std::endl;
    }
}
