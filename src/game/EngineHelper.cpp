//
// Created by lukas on 26.04.15.
//


#include <src/overlay/Label.h>
#include <src/overlay/Button.h>
#include <src/overlay/Overlay.h>
#include <src/scene/LightNode.h>
#include <SDL_video.h>
#include "src/camera/CameraTopDown.h"
#include "src/input/InputTopDown.h"
#include "src/collision/MouseRay.h"
#include "src/collision/RayPlane.h"
#include "EngineHelper.h"
#include "startUp.h"
#include "menu/Menu.h"
#include "menu/Settings.h"
#include "menu/MenuLoop.h"

EngineHelper::EngineHelper() {
    printStatus(1, "EngineHelper object");

    readConfig();
    w.reset(new mgf::Window("Clash of Mages", mWindowWidth, mWindowHeight, mFullscreen, 0));
    input.reset(new mgf::InputTopDown);

    p.reset(new mgf::ShaderProgram);
    p->addShader("res/shader/vertex_shader.glsl", GL_VERTEX_SHADER);
    std::cout << "fragment shader..." << std::endl;
//    p->addShader("res/shader/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    p->addShader("res/shader/fragment_shader_intel.glsl", GL_FRAGMENT_SHADER);
    std::cout << "fragment shader set!" << std::endl;
    p->createProgram();

    cam.reset(new mgf::CameraTopDown(40, w->getAspectRatio(), 1000.f, 0.1f));
    cam->setPos(glm::vec3(25.f, 40.f, 35.f));

    renderer.reset(new mgf::Renderer(w, cam, p));

    root.reset(new mgf::Node("root"));
    root->add(l.load("res/models/assets/alt/Assets.obj"));
    root->print();

    printStatus(2, "EngineHelper object");
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


std::shared_ptr<mgf::IOverlayElement> EngineHelper::getOverlayOnPos() {
    std::shared_ptr<mgf::IOverlayElement> elm = overlay->getMouseOverNDC
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

void EngineHelper::readConfig() {
    bool fallback = false;

    std::string line;
    std::ifstream file("res/settings.txt");

    if (file.is_open()) {
        while (getline(file, line)) {

            auto tmp = line.find('=');

            std::string key = line.substr(0, tmp);
            std::string val = line.substr(++tmp, std::string::npos);

            std::cout << key << " " << val << std::endl;
            if (!setConfig(key, val)) fallback = true;
        }

    } else {
        fallback = true;
        std::cout << "settings not found" << std::endl;
    }

    if (fallback) {
        std::cout << "using fallback" << std::endl;
        mWindowWidth = 1000;
        mWindowHeight = 800;
        mFullscreen = false;
    }
}

bool EngineHelper::setConfig(std::string key, std::string value) {
    if (key == "resolution") {
        auto index = value.find('x');

        std::string widthStr = value.substr(0, index);
        std::string lengthStr = value.substr(++index, std::string::npos);

        int width = std::atoi(widthStr.c_str());
        int height = std::atoi(lengthStr.c_str());

        mWindowWidth = width;
        mWindowHeight = height;

        return true;
    } else if (key == "fullscreen") {
        if (value == "yes") {
            mFullscreen = true;
        } else {
            mFullscreen = false;
        }
        return true;
    }

    return false;
}

bool EngineHelper::isCurrentDisplayMode() {
    int i, currentW=0, currentH=0;
    SDL_DisplayMode current;
    SDL_Init(SDL_INIT_VIDEO);

// Get current display mode of all displays.
    for (i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

        int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

        if (should_be_zero != 0)
// In case of error...
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

        else {
// On success, print the current display mode.
            currentW = current.w;
            currentH = current.h;
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", i, current.w, current.h,
                    current.refresh_rate);
        }

    }

// Clean up and exit the program.
//    SDL_Quit();

    std::cout << "Current display width: " << currentW
    << "\nCurrent display height: " << currentH
    << "\nSet game width: " << mWindowWidth
    << "\nSet game height: " << mWindowHeight << std::endl;

    return (currentW == mWindowWidth) && (currentH == mWindowHeight);
}