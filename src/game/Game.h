/*
** Author:  Lukas Stanek
** File:    Game.h
** Project: Turn Based Strategy Game
*/


#ifndef GAME_H
#define GAME_H


#define LEFTCLICK 1
#define RIGHTCLICK 2
#define MIDDLECLICK 3


#include "gameElements/Player.h"
#include "gameElements/Hexfield.h"
#include "gameElements/UnitManager.h"

class Game {
public:
    Game();
    void initGame();

    int setupField(std::shared_ptr<mgf::Node> root, std::shared_ptr<mgf::Node> actualScene,
    std::shared_ptr<Hexfield> hexfield);

    int unitMovementWrapper(std::shared_ptr<Unit> unit, std::shared_ptr<Hexfield> destination);

    void nextTurn();
    void produceUnit(std::string unitName, int playerId);

    std::shared_ptr<Player> getPlayer(int i);
    void setMPlayers(Player mPlayers[]);

    int getCurrentPlayerId();

    std::shared_ptr<Hexfield> getFirstField();
    std::shared_ptr<Hexfield> getHexAt(std::shared_ptr<Hexfield> current, float x, float y);
    std::shared_ptr<Hexfield> getNextFreeField(std::shared_ptr<Hexfield> currentField);

    bool getSelectedState();
    void setSelectedState(bool selectedState);

    std::shared_ptr<Unit> getSelectedUnit();
    void setSelectedUnit(std::shared_ptr<Unit>);

    void setEngine(std::shared_ptr<EngineHelper> engine);

    std::shared_ptr< std::vector < std::shared_ptr< Unit > > > mUnitHolder1;
    std::shared_ptr< std::vector < std::shared_ptr< Unit > > > mUnitHolder2;
private:
    std::shared_ptr<Player> mPlayers[2];
    std::shared_ptr<Player> mWinner;
    UnitManager* mUnitManager;
    int mCurrentPlayerId;
    std::shared_ptr<EngineHelper> engine;

    bool SELECTED_STATE;
    std::shared_ptr<Unit> mselectedUnit;

    int mRounds;

    time_t mStarted;
    time_t mEnded;

    std::shared_ptr<Hexfield> mFirstField;

    void generatePlayingField();
    void writeStatsToDb();


};




#endif //ITP4_GAME_H

