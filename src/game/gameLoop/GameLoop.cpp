/*
** Author:  Lukas Stanek
** File:    GameLoop.cpp
** Project: Turn Based Strategy Game
*/


#include "GameLoop.h"
#include "../Game.h"

GameLoop::GameLoop(Game game) {
    mGame.reset(&game);
}

Player GameLoop::run() {
    bool exit = false;
    std::shared_ptr<int> input;
    std::shared_ptr<Player> currentPlayer = mGame->getPlayer(0);

    while(!exit){
        if(input != NULL){


        }



    }

}