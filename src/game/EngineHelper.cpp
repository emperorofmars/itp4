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
#include "gameElements/Hexfield.h"

EngineHelper::EngineHelper() {
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
    actualScene.reset(new mgf::Node("scene"));


    root->add(l.load("res/models/assets/alt/Assets.obj"));

    root->print();

//#### Overlay
    overlay.reset(new mgf::Overlay());

    std::shared_ptr <mgf::Button> endTurnBtn(new mgf::Button("endTurnBtn"));
//    endTurnBtn->setColor(glm::vec3(1.f, 0.5f, 0.5f));
//    endTurnBtn->setFont("res/fonts/main.ttf");
//    endTurnBtn->setText("End Turn");
    endTurnBtn->setBackground("res/images/elemente/nextround.png");
    endTurnBtn->translate(glm::vec2(-0.05f, -0.05f));

    std::shared_ptr <mgf::Button> quitBtn(new mgf::Button("quitBtn"));
//    quitBtn->setColor(glm::vec3(1.f, 0.5f, 0.5f));
//    quitBtn->setFont("res/fonts/main.ttf");
//    quitBtn->setText("Quit Game");
    quitBtn->setBackground("res/images/elemente/quit.png");
    quitBtn->translate(glm::vec2(0.85f, -0.05f));

    std::shared_ptr <mgf::Button> createInfantry(new mgf::Button("infantryBtn"));
//    createInfantry->setColor(glm::vec3(1.f, 0.5f, 0.5f));
//    createInfantry->setFont("res/fonts/main.ttf");
//    createInfantry->setText("Infantry");
    createInfantry->setBackground("res/images/elemente/infantry.png");
    createInfantry->translate(glm::vec2(-0.05f, 0.65f));

    std::shared_ptr <mgf::Button> createCavalry(new mgf::Button("cavalryBtn"));
//    createCavalry->setColor(glm::vec3(1.f, 0.5f, 0.5f));
//    createCavalry->setFont("res/fonts/main.ttf");
//    createCavalry->setText("Cavalry");
    createCavalry->setBackground("res/images/elemente/cavalry.png");
    createCavalry->translate(glm::vec2(0.05f, 0.65f));

    std::shared_ptr <mgf::Button> createArtillery(new mgf::Button("artilleryBtn"));
//    createArtillery->setColor(glm::vec3(1.f, 0.5f, 0.5f));
//    createArtillery->setFont("res/fontss/main.ttf");
//    createArtillery->setText("Artillery");
    createArtillery->setBackground("res/images/elemente/artillery.png");
    createArtillery->translate(glm::vec2(0.15f, 0.65f));

    std::shared_ptr <mgf::Button> settings(new mgf::Button("settingsBtn"));
    settings->setBackground("res/images/elemente/settings.png");
    settings->translate(glm::vec2(0.85f, 0.65f));

    pointer.reset(new mgf::Label("mouse"));
    pointer->setBackground("res/images/Mouse.png");
    pointer->translate(glm::vec2(-10.f, -10.f));

    overlay->add(createInfantry);
    overlay->add(createCavalry);
    overlay->add(createArtillery);
    overlay->add(quitBtn);
    overlay->add(endTurnBtn);
    overlay->add(settings);
    overlay->add(pointer);

//#### Setting up Sunlight
    // NEW LIGHT:
    std::shared_ptr<mgf::Node> light(new mgf::LightNode("sun"));
    light->setLight(mgf::SUN_LIGHT, 2, 2, glm::vec3(1.f, 1.f, 1.f), glm::vec3(5.f, 15.f, 15.f), glm::vec3(0.f, -10.f, -5.f), 30);
    actualScene->add(light);

    // OLD LIGHT:
//    std::shared_ptr <mgf::Light> light(new mgf::Light());
//    light->mColor = glm::vec3(1.f, 1.f, 1.f);
//    light->mStrengthDiffuse = 2;
//    light->mPosition = glm::vec3(5.f, 15.f, 15.f);
//    renderer->addLight(light, glm::mat4(1));
//    light->mType = 2;
//    light->mColor = glm::vec3(0.4f, 0.4f, 0.4f);
//    light->mDirection = glm::vec3(0.f, -10.f, -5.f);
//    renderer->addLight(light, glm::mat4(1));

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
