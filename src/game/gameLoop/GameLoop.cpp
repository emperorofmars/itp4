/*
** Author:  Lukas Stanek
** File:    GameLoop.cpp
** Project: Turn Based Strategy Game
*/


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
    bool moveTest = true;
    while(quit != true){
//###############################################  Update
        engine->input->update();
        quit = engine->input->getQuit();
        engine->cam->update(engine->input->getPosition(), engine->input->getMouseRelative());


//###############################################  Rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)));

        engine->actualScene->render(engine->renderer); //rendering on gpu happens here

        engine->w->swap(); //display the rendered image on screen

//############ Movement Test
        if(moveTest){
            LOG_F_TRACE(GAME_LOG_PATH, "trying to move unit");
            std::shared_ptr<Hexfield> dest = mGame->getHexAt(mGame->getFirstField(), 17.5, 18);
            LOG_F_TRACE(GAME_LOG_PATH, "pos: ", dest->mPosition[1], " / ", dest->mPosition[0]);
            mGame->mUnitHolder1->at(0)->printStats();
            mGame->unitMovementWrapper(mGame->mUnitHolder1->at(0), dest);

            moveTest = false;
        }


//###############################################  Calculate fps
        current = SDL_GetTicks();
        frametime = current - last;
        last = current;
        //std::cerr << "FPS: " << 1000.f / frametime << std::endl;	//show fps
    }
//###############################################  Gameloop end


    return 0;
}