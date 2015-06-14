/*
** Author:  Lukas Stanek on 14.06.15.
** File:    ChanceSimulator.h
** Project: Turn based Strategy Game
*/

#ifndef ITP4_CHANCESIMULATOR_H
#define ITP4_CHANCESIMULATOR_H


#include <memory>
#include <random>

class ChanceSimulator {
public:
    static std::shared_ptr<ChanceSimulator> getInstance();

    double getRandomHit();
    float getRandomCoord();
    float getRandomFloat(float min, float max);

private:
    ChanceSimulator();
    static std::shared_ptr<ChanceSimulator> instance;

    std::default_random_engine generator;

};


#endif //ITP4_CHANCESIMULATOR_H
