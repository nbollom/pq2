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
    Character character;

    void LevelUp();
    void WinStat();
    void WinSpell();
    void WinItem();
    void WinEquip();
    void CompleteAct();
    void InterplotCinematic();
    void Dequeue();
    void MonsterTask();
    void CompleteQuest();
    static std::string Sick(int64_t level, const std::string& name);
    static std::string Young(int64_t level, const std::string& name);
    static std::string Big(int64_t level, const std::string& name);
    static std::string Special(int64_t level, const std::string& name);



    std::string InterestingItem() const;

public:
    Game();
    void SetDaemonMode();
    file::LoadError LoadGame(std::string filename_path);
    file::SaveError SaveGame(const std::string& filename_path = "");
    std::shared_ptr<NewGame> StartNewGame();
    void Tick(uint64_t ms); //advances the game clock by the specified milliseconds;
    void Close();

    game::GameState GetState() const;
    Character GetCharacter();

    uint64_t GetLevelUpMaxValue() const;
    uint64_t GetEncumbrance();
    uint64_t GetEncumbranceMaxValue() const;
    uint64_t GetPlotMaxValue() const;

};

#endif //PQ2_GAME_H
