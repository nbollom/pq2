//
// Created by nbollom on 25/05/16.
//

#ifndef PQ2_GAME_H
#define PQ2_GAME_H

#include <cstdint>
#include <random>

class Game {

private:
    std::random_device random;

public:
    Game();
    void tick(uint64_t ms); //advances the game clock by the specified milliseconds;

};

#endif //PQ2_GAME_H
