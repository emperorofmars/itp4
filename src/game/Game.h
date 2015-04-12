/*
** Author:  Lukas Stanek
** File:    Game.h
** Project: Turn Based Strategy Game
*/


#ifndef ITP4_GAME_H
#define ITP4_GAME_H


#include "gameElements/Player.h"
#include "gameLoop/GameLoop.h"
#include "gameElements/Hexfield.h"

class Game {
public:
    void initGame();
    void start();



private:
    Player players[];
    Player winner;

    int rounds;

    time_t started;
    time_t ended;

    std::vector< std::vector<Hexfield*> > field;

    GameLoop loop;

    void generatePlayingField();
    void writeStatsToDb();
};


#endif //ITP4_GAME_H
