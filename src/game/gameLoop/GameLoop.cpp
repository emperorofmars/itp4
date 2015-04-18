/*
** Author:  Lukas Stanek
** File:    GameLoop.cpp
** Project: Turn Based Strategy Game
*/


#include "GameLoop.h"

GameLoop::GameLoop(Game game) {
    mGame.reset(game);
}

Player GameLoop::run() {
    bool exit = false;
    shared_ptr<int> input;
    shared_ptr<Player> currentPlayer = mGame->getPlayer(0);

    while(!exit){
        if(input != NULL){


        }



    }

}