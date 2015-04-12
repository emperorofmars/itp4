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


    shared_ptr<Player> getMPlayer(int i);
    void setMPlayers(Player mPlayers[]);

private:
    Player mPlayers[];
    shared_ptr<Player> mWinner;


    int mRounds;

    time_t mStarted;
    time_t mEnded;

    shared_ptr<Hexfield> mFirstField;

    GameLoop mLoop;

    void generatePlayingField();
    void writeStatsToDb();
};


#endif //ITP4_GAME_H
