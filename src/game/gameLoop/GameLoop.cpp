/*
** Author:  Lukas Stanek
** File:    GameLoop.cpp
** Project: Turn Based Strategy Game
*/


#include <src/collision/MouseRay.h>
#include <src/collision/RayPlane.h>
#include "GameLoop.h"
#include "../Game.h"
#include "../EngineHelper.h"
#include "../../tbs.h"

GameLoop::GameLoop(std::shared_ptr<Game> game) {
    mGame = game;
}

int GameLoop::run(std::shared_ptr<EngineHelper> engine) {
//###############################################  Gameloop
    float current = 0, last = 0, frametime = 0;
    bool quit = false;
    bool mouseMidDown = false;
    while(quit != true){
//###############################################  Update
        engine->input->update();
        quit = engine->input->getQuit();
        engine->cam->update(engine->input->getPosition(), engine->input->getMouseRelative());
        bool leftClick = engine->input->getMouseClick()[0];
        bool rightClick = engine->input->getMouseClick()[2];
        bool middleClick = engine->input->getMouseClick()[1];

        if(middleClick){
            mouseMidDown = true;
        }
        if(mouseMidDown && !middleClick){
            mGame->nextTurn();
            mouseMidDown = false;
        }

        if(leftClick && mGame->getSelectedState()){
            mGame->setSelectedState(false);
        }

        if(leftClick && !mGame->getSelectedState()){
            glm::vec3 mray = mgf::calculateMouseRay(engine->cam->getP(), engine->cam->getV(), engine->input->getMouseAbsolute(), glm::vec2(1000, 800));
            glm::vec3 mpoint = mgf::colLinePlane(engine->cam->getPos(), mray, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
            std::shared_ptr<Hexfield> clickedHex = mGame->getHexAt(mGame->getFirstField(), mpoint[2], mpoint[0]);
            if(clickedHex->getIsOccupied()){
                mGame->setSelectedState(true);
                mGame->setSelectedUnit(clickedHex->getOccupation());
            }else{
                LOG_F_TRACE(GAME_LOG_PATH, "nothing on that field");
            }
        }

        if(rightClick && mGame->getSelectedState()){
            if(mGame->getSelectedUnit()->getOwner() != mGame->getCurrentPlayerId()) continue;

            glm::vec3 mray = mgf::calculateMouseRay(engine->cam->getP(), engine->cam->getV(), engine->input->getMouseAbsolute(), glm::vec2(1000, 800));
            glm::vec3 mpoint = mgf::colLinePlane(engine->cam->getPos(), mray, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

            LOG_F_TRACE(GAME_LOG_PATH, "trying to move unit");
            std::shared_ptr<Hexfield> dest = mGame->getHexAt(mGame->getFirstField(), mpoint[2], mpoint[0]);
            LOG_F_TRACE(GAME_LOG_PATH, "pos: ", dest->mPosition[1], " / ", dest->mPosition[0]);
            mGame->getSelectedUnit()->printStats();
            mGame->unitMovementWrapper(mGame->getSelectedUnit(), dest);
            mGame->setSelectedState(false);
        }

//###############################################  Rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)));

        engine->actualScene->render(engine->renderer); //rendering on gpu happens here

        engine->w->swap(); //display the rendered image on screen



//###############################################  Calculate fps
        current = SDL_GetTicks();
        frametime = current - last;
        last = current;
        //std::cerr << "FPS: " << 1000.f / frametime << std::endl;	//show fps
    }
//###############################################  Gameloop end


    return 0;
}