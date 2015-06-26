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

/*
 * TODO: engine helper nehmen
 * gleiches window, camera etc benutzen
 * dann eine createGameOverlay und createMenuOverlay func machen
 * und eine destroy von beidem
 */

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
    actualScene.reset(new mgf::Node("scene"));


    root->add(l.load("res/models/assets/alt/Assets.obj"));

    root->print();

    createMenuOverlay();

    printStatus(2, "EngineHelper object");
}

void EngineHelper::createMenuOverlay() {
    printStatus(1, "menu overlay");

    //#### Overlay
    overlay.reset(new mgf::Overlay());

    /**
     * Create buttons
     */
    std::shared_ptr<mgf::Button> startBtn(new mgf::Button("startBtn"));
    startBtn->setBackground("res/images/elemente/play.png");
    startBtn->translate(glm::vec2(0.4f, 0.1f));

    std::shared_ptr<mgf::Button> settingsBtn(new mgf::Button("settingsBtn"));
    settingsBtn->setBackground("res/images/elemente/settings.png");
    settingsBtn->translate(glm::vec2(0.4f, 0.2f));

    std::shared_ptr<mgf::Button> quitBtn(new mgf::Button("quitBtn"));
    quitBtn->setBackground("res/images/elemente/quit.png");
    quitBtn->translate(glm::vec2(0.4f, 0.3f));

    /**
     * Set mouse pointer
     */
    pointer.reset(new mgf::Label("mouse"));
    pointer->setBackground("res/images/Mouse.png");
    pointer->translate(glm::vec2(-10.f, -10.f));

    /**
     * Add elements to Overlay
     */

    overlay->add(quitBtn);
    overlay->add(startBtn);
    overlay->add(settingsBtn);
    overlay->add(pointer);

    printStatus(2, "menu overlay");
}

//void EngineHelper::processMenuLeftClick() {
//    std::shared_ptr<mgf::IOverlayElement> elm = getOverlayOnPos();
//
//    if (elm) {
//        if (elm->getName() == "startBtn") {
//            startUp();
//        } else if (elm->getName() == "quitBtn") {
//            quit = true;
//        }
//    }
//}

void EngineHelper::createGameOverlay() {
    printStatus(1, "game overlay");
    //#### Overlay
    overlay.reset(new mgf::Overlay());

    /**
     * Create buttons
     */
    std::shared_ptr <mgf::Button> endTurnBtn(new mgf::Button("endTurnBtn"));
    endTurnBtn->setBackground("res/images/elemente/nextround.png");
    endTurnBtn->translate(glm::vec2(0.85f, 0.65f));

    std::shared_ptr <mgf::Button> quitBtn(new mgf::Button("quitBtn"));
    quitBtn->setBackground("res/images/elemente/quit.png");
    quitBtn->translate(glm::vec2(0.85f, -0.05f));

    std::shared_ptr <mgf::Button> createInfantry(new mgf::Button("infantryBtn"));
    createInfantry->setBackground("res/images/elemente/infantry.png");
    createInfantry->translate(glm::vec2(-0.05f, 0.65f));

    std::shared_ptr <mgf::Button> createCavalry(new mgf::Button("cavalryBtn"));
    createCavalry->setBackground("res/images/elemente/cavalry.png");
    createCavalry->translate(glm::vec2(0.05f, 0.65f));

    std::shared_ptr <mgf::Button> createArtillery(new mgf::Button("artilleryBtn"));
    createArtillery->setBackground("res/images/elemente/artillery.png");
    createArtillery->translate(glm::vec2(0.15f, 0.65f));

    /**
     * Create game status Labels:
     */

    // Health
    std::shared_ptr <mgf::Label> statusHealth(new mgf::Label("statusHealth"));
    statusHealth->setBackground("res/images/elemente/health.png");
    statusHealth->translate(glm::vec2(-0.05f, -0.05f));

    health.reset(new mgf::Label("health"));
    health->setFont("res/fonts/main.ttf");
    health->translate(glm::vec2(0.07f, -0.05f));

    // Mana
    std::shared_ptr <mgf::Label> statusMana(new mgf::Label("statusMana"));
    statusMana->setBackground("res/images/elemente/mana.png");
    statusMana->translate(glm::vec2(0.3, -0.05f));

    mana.reset(new mgf::Label("mana"));
    mana->setFont("res/fonts/main.ttf");
    mana->translate(glm::vec2(0.4f, -0.05f));

    // Player
    player.reset(new mgf::Label("label"));
    player->setFont("res/fonts/main.ttf");
    player->setLayer(0);
    player->translate(glm::vec2(-0.05f, 0.02));

    /**
     * Set mouse pointer
     */
    pointer.reset(new mgf::Label("mouse"));
    pointer->setBackground("res/images/Mouse.png");
    pointer->translate(glm::vec2(-10.f, -10.f));

    /**
     * Add elements to Overlay
     */
    overlay->add(createInfantry);
    overlay->add(createCavalry);
    overlay->add(createArtillery);
    overlay->add(quitBtn);
    overlay->add(endTurnBtn);
    overlay->add(statusHealth);
    overlay->add(health);
    overlay->add(statusMana);
    overlay->add(mana);
    overlay->add(player);
    overlay->add(pointer);

//#### Setting up Sunlight
    std::shared_ptr<mgf::Node> light(new mgf::LightNode("sun"));
    light->setLight(mgf::SUN_LIGHT, 2, 2, glm::vec3(1.f, 1.f, 1.f), glm::vec3(5.f, 15.f, 15.f), glm::vec3(0.f, -10.f, -5.f), 30);
    actualScene->add(light);

    printStatus(2, "game overlay");
}

void EngineHelper::destroyMenu() {

}

void EngineHelper::destroyGame() {

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




void EngineHelper::createField() {}
void EngineHelper::clearField(){}
void EngineHelper::initEngine(){}

void EngineHelper::printStatus(int status, std::string object) {
    if (status == 1) {
        std::cout << "Creating " << object << "..." << std::endl;
    } else if (status == 2) {
        std::cout << "Created " << object << "." << std::endl;
    }
}
