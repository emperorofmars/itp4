/*
** Author:  Lukas Stanek
** File:    Game.cpp
** Project: Turn Based Strategy Game
*/


#include "Game.h"

void Game::initGame() {


    generatePlayingField();

}

void Game::start() {

}

void Game::generatePlayingField() {
    int size = 24;

    //init size of field
    field.resize(size);
    for(int i = 0; i<size; ++i){
        field[i].resize(size);
    }

    for(int i = 0; i<size; ++i){
        for(int j = 0; j < size; ++j){
            Hexfield *newField = new Hexfield();
            field[i].push_back(newField);

        }
    }



}

void Game::writeStatsToDb() {

}
