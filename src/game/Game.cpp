/*
** Author:  Lukas Stanek
** File:    Game.cpp
** Project: Turn Based Strategy Game
*/


#include "Game.h"

using namespace std;

void Game::initGame() {

    mPlayers[0] = new Player("Player1");
    mPlayers[1] = new Player("Player2");

    //mPlayers[0].setColor(vec4(1.0f,1.0f,0, 1.0f));
    //mPlayers[1].setColor(vec4(1.0f,0,1.0f, 1.0f));

    mPlayers[0]->setNext(mPlayers[1]);
    mPlayers[1]->setNext(mPlayers[0]);

    generatePlayingField();

}


void Game::generatePlayingField() {
    std::vector< std::vector< shared_ptr<Hexfield> > > field;
    int size = 24;


    for(int i = 0; i<size; ++i){
        for(int j = 0; j < size; ++j){
            shared_ptr<Hexfield> newField = new Hexfield();

            newField->mPosition[0] = i*10;
            newField->mPosition[1] = j*10;

            if(!i%2){
                newField->mPosition[1] += 5;
            }

            field[i].push_back(newField);
        }
    }

    for(int i = 0; i<size; ++i){
        for(int j = 0; j<size; ++j){
            shared_ptr<Hexfield> hexfield = field[i][j];

            if(i>0){
                hexfield->linkedTo[0] = field[i-1][j];
            }

            if(i>0 && j<size){
                hexfield->linkedTo[1] = field[i-1][j+1];
            }

            if(j<size-1){
                hexfield->linkedTo[2] = field[i][j+1];
            }

            if(i < size-1 && j < size-1){
                hexfield->linkedTo[3] = field[i+1][j+1];
            }

            if(i < size-1){
                hexfield->linkedTo[4] = field[i+1][j];
            }

            if(j > 0){
                hexfield->linkedTo[5] = field[i][j-1];
            }


        }
    }

    mFirstField = field[0][0];

}

void Game::writeStatsToDb() {
    // TODO Write game stats to some persistent storage
}


/*
 * Setter & Getter
 */

shared_ptr<Player> Game::getPlayer(int i) {
    shared_ptr<Player> player;

    switch(i){
        case 0: player.reset(&mPlayers[0]); break;
        case 1: player.reset(&mPlayers[1]); break;
        default: player.reset(NULL); break;
    }
    return player;
}

