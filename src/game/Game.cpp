/*
** Author:  Lukas Stanek
** File:    Game.cpp
** Project: Turn Based Strategy Game
*/


#include "Game.h"

void Game::initGame() {

    players[0] = new Player("Player1");
    players[1] = new Player("Player2");

    players[0].setColor(vec4(1.0f,1.0f,0, 1.0f));
    players[1].setColor(vec4(1.0f,0,1.0f, 1.0f));


    generatePlayingField();

}

void Game::start() {

}

void Game::generatePlayingField() {
    int size = 24;


    for(int i = 0; i<size; ++i){
        for(int j = 0; j < size; ++j){
            Hexfield *newField = new Hexfield();

            newField->position[0] = i*10;
            newField->position[1] = j*10;

            if(!i%2){
                newField->position[1] += 5;
            }

            field[i].push_back(newField);
        }
    }

    for(int i = 0; i<size; ++i){
        for(int i = 0; i<size; ++i){
            Hexfield *hexfield = field[i][j];

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

    //Render!

}

void Game::writeStatsToDb() {

}
