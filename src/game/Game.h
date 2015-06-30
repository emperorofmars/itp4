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
    ~Game();

    void initGame();

    int setupField(std::shared_ptr <mgf::Node> root, std::shared_ptr <mgf::Node> actualScene,
                   std::shared_ptr <Hexfield> hexfield);

    int unitMovementWrapper(std::shared_ptr <Unit> unit, std::shared_ptr <Hexfield> destination);

    std::shared_ptr <Hexfield> getHexAtMousePos();


    void nextTurn();

    void produceUnit(std::string unitName, int playerId, bool useMana);

    void quitGame();

    bool getQuit();


    int cleanUp();

    int eraseField(std::shared_ptr <Hexfield> hex);

    int deleteUnits();

    void deleteRow(std::shared_ptr <Hexfield> firstField);

    void deleteAllLinks(std::shared_ptr <Hexfield> hex);

    std::shared_ptr <Player> getPlayer(int i);

    void setMPlayers(Player mPlayers[]);

    int getCurrentPlayerId();

    std::shared_ptr <Hexfield> getFirstField();

    std::shared_ptr <Hexfield> getHexAt(std::shared_ptr <Hexfield> current, float x, float y);

    std::shared_ptr <Hexfield> getNextFreeField(std::shared_ptr <Hexfield> currentField);

    bool getSelectedState();

    void setSelectedState(bool selectedState);

    std::shared_ptr <Unit> getSelectedUnit();

    void selectUnit(std::shared_ptr <Unit>);

    void deselectUnit();

    void generateEnvironment();


    std::shared_ptr <mgf::IOverlayElement> getOverlayInteraction();

    void setEngine(std::shared_ptr <EngineHelper> engine);

    std::shared_ptr <std::vector<std::shared_ptr < Unit>> >
    mUnitHolder1;
    std::shared_ptr <std::vector<std::shared_ptr < Unit>> >
    mUnitHolder2;

    void setStatusBar();

    void createGameOverlay();

    int unitDmgCounter[2];
    std::shared_ptr<Unit> dmgedUnit[2];
private:
    std::shared_ptr <Player> mPlayers[2];
    std::shared_ptr <Player> mWinner;
    UnitManager *mUnitManager;
    int mCurrentPlayerId;
    std::shared_ptr <EngineHelper> engine;

    bool quit;
    bool SELECTED_STATE;
    std::shared_ptr <Unit> mSelectedUnit;

    int mRounds;
    int mFieldSize;

    time_t mStarted;
    time_t mEnded;

    std::shared_ptr <Hexfield> mFirstField;

    void generatePlayingField();

    void writeStatsToDb();

    void cleanStatusBar();

    void setPlayerStatus();

    void cleanPlayerStatus();

    void resetStatusBar();
};


#endif //ITP4_GAME_H

