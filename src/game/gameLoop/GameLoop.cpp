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
    bool mouseLeftDown = false;
    bool mouseRightDown = false;
    while(quit != true){
//###############################################  Update
        engine->input->update();
        quit = engine->input->getQuit();
        engine->cam->update(engine->input->getPosition(), engine->input->getMouseRelative());

//###############################################  Controls
        bool leftClick = engine->input->getMouseClick()[0];
        bool rightClick = engine->input->getMouseClick()[2];
        bool middleClick = engine->input->getMouseClick()[1];

        if(middleClick){
            mouseMidDown = true;
        }
        if(leftClick){
            mouseLeftDown = true;
        }
        if(rightClick){
            mouseRightDown = true;
        }

        if(mouseMidDown && !middleClick){
            mGame->nextTurn();
            mouseMidDown = false;
        }


        if(!leftClick && mouseLeftDown){
            glm::vec3 mpoint = engine->getMousePos();

            std::shared_ptr<Hexfield> clickedHex = mGame->getHexAt(mGame->getFirstField(), mpoint[2], mpoint[0]);

            if(clickedHex->getIsOccupied()){
                mGame->setSelectedState(true);
                mGame->setSelectedUnit(clickedHex->getOccupation());
            }else{
                mGame->setSelectedState(false);
                LOG_F_TRACE(GAME_LOG_PATH, "nothing on that field");
            }

            mouseLeftDown = false;
        }

        if(mGame->getSelectedState() && !rightClick && mouseRightDown){
            std::shared_ptr<Unit> selectedUnit = mGame->getSelectedUnit();
            if(selectedUnit->getOwner() != mGame->getCurrentPlayerId()) continue;

            mouseRightDown = false;
            LOG_F_TRACE(GAME_LOG_PATH, "locating clicked hex");

            glm::vec3 mpoint = engine->getMousePos();
            std::shared_ptr<Hexfield> dest = mGame->getHexAt(mGame->getFirstField(), mpoint[2], mpoint[0]);

            LOG_F_TRACE(GAME_LOG_PATH, "pos: ", dest->mPosition[1], " / ", dest->mPosition[0]);


            if(dest->getIsOccupied()){
                if(selectedUnit->isInRange(dest) && dest->getOccupation()->getOwner() != mGame->getCurrentPlayerId()){
                    LOG_F_TRACE(GAME_LOG_PATH, "Target is enemy and in range");
                    selectedUnit->attack(dest->getOccupation());
                    continue;
                }else{
                    LOG_F_TRACE(GAME_LOG_PATH, "Target NOT in Range or friendly!");
                }
            }

            mGame->unitMovementWrapper(selectedUnit, dest);


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

    LOG_F_TRACE(GAME_LOG_PATH, "starting clean up!");
    mGame->cleanUp();

    LOG_F_TRACE(GAME_LOG_PATH, "cleanup complete, exiting");

    return 0;
}