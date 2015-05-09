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


    std::shared_ptr<Player> getPlayer(int i);
    void setMPlayers(Player mPlayers[]);

    int setupField(std::shared_ptr<mgf::Node> root, std::shared_ptr<mgf::Node> actualScene,
                   std::shared_ptr<Hexfield> hexfield);

    int unitMovementWrapper(std::shared_ptr<Unit> unit, std::shared_ptr<Hexfield> destination);

    std::shared_ptr<Hexfield> getFirstField();
    std::shared_ptr<Hexfield> getHexAt(std::shared_ptr<Hexfield> current, float x, float y);

    bool getSelectedState();
    void setSelectedState(bool selectedState);

    std::shared_ptr<Unit> getSelectedUnit();
    void setSelectedUnit(std::shared_ptr<Unit>);

    std::shared_ptr< std::vector < std::shared_ptr< Unit > > > mUnitHolder1;
    std::shared_ptr< std::vector < std::shared_ptr< Unit > > > mUnitHolder2;
private:
    std::shared_ptr<Player> mPlayers[2];
    std::shared_ptr<Player> mWinner;
    UnitManager* mUnitManager;
    int mCurrentPlayer;

    bool SELECTED_STATE;
    std::shared_ptr<Unit> mselectedUnit;


    int mRounds;

    time_t mStarted;
    time_t mEnded;

    std::shared_ptr<Hexfield> mFirstField;

    void generatePlayingField();
    void writeStatsToDb();

    void nextTurn();


//    //TODO research what kind of event data is given from engine
//    std::shared_ptr<int> clicked;
//
//    typedef enum { STATE_DEFAULT, STATE_SELECTED, NUM_STATES } state_t;
//
//    typedef state_t state_func_t( std::shared_ptr<int> clicked );
//
//    state_t do_state_default(std::shared_ptr<int> clicked);
//    state_t do_state_selected(std::shared_ptr<int> clicked);
//
//    state_func_t* const state_table[ NUM_STATES ] = {
//            do_state_default, do_state_selected
//    };
//
//    state_t run_state( state_t cur_state, std::shared_ptr<int> clicked ) {
//        return state_table[ cur_state ]( clicked );
//    };

};




#endif //ITP4_GAME_H

