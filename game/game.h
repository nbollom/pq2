//
// Created by nbollom on 25/05/16.
//

#ifndef PQ2_GAME_H
#define PQ2_GAME_H

#include <cstdint>
#include <random>
#include <memory>
#include "newgame.h"

class Game {

private:
    std::shared_ptr<std::mt19937_64> engine;

public:
    Game();
    std::shared_ptr<NewGame> StartNewGame();
    void tick(uint64_t ms); //advances the game clock by the specified milliseconds;

};

#endif //PQ2_GAME_H
