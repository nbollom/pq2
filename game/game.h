//
// Created by nbollom on 25/05/16.
//

#ifndef PQ2_GAME_H
#define PQ2_GAME_H

#include <cstdint>
#include <random>
#include <memory>
#include "types.h"
#include "newgame.h"

class Game {

private:
    std::shared_ptr<std::mt19937_64> engine;
    std::string filename;
    game::GameState game_state;
    std::shared_ptr<Character> character;

public:
    Game();
    void SetDaemonMode();
    file::LoadError LoadGame(std::string filename_path);
    file::SaveError SaveGame(std::string filename_path = "");
    std::shared_ptr<NewGame> StartNewGame();
    void Tick(uint64_t ms); //advances the game clock by the specified milliseconds;
    void Close();

    game::GameState GetState();
    std::shared_ptr<Character> GetCharacter();

};

#endif //PQ2_GAME_H
