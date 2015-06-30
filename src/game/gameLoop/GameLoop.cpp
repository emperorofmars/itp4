/*
** Author:  Lukas Stanek
** File:    GameLoop.cpp
** Project: Turn Based Strategy Game
*/


#include "src/collision/MouseRay.h"
#include "src/collision/RayPlane.h"
#include <queue>
#include "GameLoop.h"
#include "../Game.h"
#include "../EngineHelper.h"
#include "src/helper/Helper.h"
#include "../../tbs.h"


GameLoop::GameLoop(std::shared_ptr<Game> game): mGame(game) {
    std::cout << "GameLoop constructor." << std::endl;
    mStateContext = Context::getInstance();
    std::cout << "GameLoop instance set." << std::endl;
    mStateContext->injectGameReference(mGame);
    std::cout << "GameLoop game reference injected." << std::endl;
    LOG_F_TRACE(GAME_LOG_PATH, "context adress ", mStateContext.get());

}

GameLoop::~GameLoop() {
    std::cout << "GameLoop Destructor." << std::endl;
    mGame.reset();
    mStateContext.reset();
}

int GameLoop::run(std::shared_ptr<EngineHelper> engine) {
//###############################################  Gameloop
    float current = 0, last = 0, frametime = 0;
    bool quit = false;
    bool mouseMidDown = false;
    bool mouseLeftDown = false;
    bool mouseRightDown = false;

    std::queue<InputEvent> eventsQueue;

    while (!quit) {
//###############################################  Update
        engine->input->update();
        quit = (engine->input->getQuit() || mGame->getQuit());

        engine->cam->update(engine->input->getPosition(), engine->input->getMouseRelative());

        if(mGame->dmgedUnit[0] != NULL){
            mGame->unitDmgCounter[0]++;

            if(mGame->unitDmgCounter[0] > 15){
                mGame->dmgedUnit[0]->getUnitNode()->resetMaterial();
                mGame->dmgedUnit[0].reset();
            }

        }

        if(mGame->dmgedUnit[1] != NULL){
            mGame->unitDmgCounter[1]++;

            if(mGame->unitDmgCounter[1] > 15){
                std::shared_ptr<mgf::Material> newmat(new mgf::Material);
                newmat->mDiffuseColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
                mGame->dmgedUnit[1]->getUnitNode()->setMaterial(newmat);
                mGame->dmgedUnit[1].reset();
            }

        }

//###############################################  Pointer
        engine->setPointer();

//###############################################  Controls
        bool leftClick = engine->input->getMouseClick()[0];
        bool rightClick = engine->input->getMouseClick()[2];
        bool middleClick = engine->input->getMouseClick()[1];

        if (middleClick) {
            mouseMidDown = true;
        }
        if (leftClick) {
            mouseLeftDown = true;
        }
        if (rightClick) {
            mouseRightDown = true;
        }

        if (mouseMidDown && !middleClick) {
            eventsQueue.push(InputEvent::EVENT_MIDDLECLICK);
            mouseMidDown = false;
        } else if (mouseLeftDown && !leftClick) {
            eventsQueue.push(InputEvent::EVENT_LEFTCLICK);
            mouseLeftDown = false;
        } else if (mouseRightDown && !rightClick) {
            eventsQueue.push(InputEvent::EVENT_RIGHTCLICK);
            mouseRightDown = false;
        } else {
            eventsQueue.push(InputEvent::EVENT_NOEVENT);
        }

        if (!eventsQueue.empty()) {
            //LOG_F_TRACE(GAME_LOG_PATH, "Event processing");
            mStateContext->handle(eventsQueue.front());
            eventsQueue.pop();
        }

//##### Check game status

        if(gameFinished()){
            mGame->quitGame();
        }

//###############################################  Rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, glm::value_ptr(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)));

        engine->actualScene->render(engine->renderer); //rendering on gpu happens here
        engine->overlay->render(engine->renderer);


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

    mStateContext->cleanUp();
    mStateContext.reset();

    LOG_F_TRACE(GAME_LOG_PATH, "cleanup complete, exiting");

    return 0;
}

bool GameLoop::checkOutOfBounds(glm::vec3 position) {
    LOG_F_TRACE(GAME_LOG_PATH, "pos: ", mgf::vec3_toStr(position));

    if (position[0] < 0.f || position[0] > 48.f) {
        return true;
    } else if (position[1] < 5.f || position[1] > 60.f) {
        return true;
    } else if (position[2] < 20.f || position[2] > 70.f) {
        return true;
    }

    return false;
}

bool GameLoop::gameFinished() {
    int loser;

    for(int i = 0; i<2; ++i){
        if((mGame->getPlayer(i)->allDead() && mGame->getPlayer(i)->getCurMana() < 5) ||
           mGame->getPlayer(i)->getBase()->isDead()){
            loser = i;
            return true;
        }
    }


    return false;
}
