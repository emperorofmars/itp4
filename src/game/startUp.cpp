//
// Created by Lukas on 12.04.2015.
//

#include "startUp.h"
#include "Game.h"
#include "gameLoop/GameLoop.h"

using namespace std;

int startUp(){
    cout << "creating new Game" << endl;
    std::shared_ptr<Game> game(new Game());


    game->initGame();

    cout << "first player: " << game->getPlayer(0)->getName() << endl;
    cout << "second player: " << game->getPlayer(1)->getName() << endl;


    cout << "creating Game Loop element" << endl;
    std::shared_ptr<GameLoop> loop(new GameLoop(game));



}