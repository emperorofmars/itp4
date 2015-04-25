/*
** Author:  Lukas Stanek
** File:    GameLoop.cpp
** Project: Turn Based Strategy Game
*/


#include "GameLoop.h"
#include "../Game.h"

GameLoop::GameLoop(std::shared_ptr<Game> game) {
    mGame = game;
}

int GameLoop::run() {
    bool exit = false;


    while(!exit){

        int lastAction = input.front();




    }



    return 0;
}