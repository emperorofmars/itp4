//
// Created by Lukas on 12.04.2015.
//

#include "startUp.h"

int startUp(){
    shared_ptr<Game> game = game.reset(new Game());

    game->initGame();


    shared_ptr<GameLoop> loop = loop.reset(new GameLoop(game));



}