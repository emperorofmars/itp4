/*
** Author:  Lukas Stanek
** File:    Game.h
** Project: Turn Based Strategy Game
*/


#ifndef GAME_H
#define GAME_H


#include "gameElements/Player.h"
#include "gameElements/Hexfield.h"
#include "gameElements/UnitManager.h"

class Game {
public:
    void initGame();


    std::shared_ptr<Player> getPlayer(int i);
    void setMPlayers(Player mPlayers[]);

private:
    std::shared_ptr<Player> mPlayers[2];
    std::shared_ptr<Player> mWinner;
    UnitManager* mUnitManager;


    int mRounds;

    time_t mStarted;
    time_t mEnded;

    std::shared_ptr<Hexfield> mFirstField;

    void generatePlayingField();
    void writeStatsToDb();
};


#endif //ITP4_GAME_H
