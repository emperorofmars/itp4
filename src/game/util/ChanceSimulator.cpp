/*
** Author:  Lukas Stanek on 14.06.15.
** File:    ChanceSimulator.cpp
** Project: Turn based Strategy Game
*/

#include "ChanceSimulator.h"

std::shared_ptr<ChanceSimulator> ChanceSimulator::instance;


std::shared_ptr<ChanceSimulator> ChanceSimulator::getInstance() {
    if(instance == nullptr){
        instance = std::shared_ptr<ChanceSimulator>(new ChanceSimulator());
    }
    return instance;
}


ChanceSimulator::ChanceSimulator() {
}


//#### Actual Implementation

double ChanceSimulator::getRandom() {

    std::uniform_real_distribution<double> distribution(0.0, 100.0);
    return distribution(generator);
}
