//
// Created by nbollom on 25/05/16.
//

#pragma once

#include <cstdint>
#include <random>
#include <memory>
#include "types.hpp"
#include "newgame.hpp"

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
    [[nodiscard]] static std::string Sick(int64_t level, const std::string& name);
    [[nodiscard]] static std::string Young(int64_t level, const std::string& name);
    [[nodiscard]] static std::string Big(int64_t level, const std::string& name);
    [[nodiscard]] static std::string Special(int64_t level, const std::string& name);

    [[nodiscard]] std::string InterestingItem() const;

public:
    Game();
#ifndef _WIN32
    void SetDaemonMode();
#endif
    file::LoadError LoadGame(const std::string& filename_path);
    file::SaveError SaveGame(const std::string& filename_path = "");
    [[nodiscard]] std::shared_ptr<NewGame> StartNewGame();
    void Tick(uint64_t ms); //advances the game clock by the specified milliseconds;
    void Close();

    [[nodiscard]] game::GameState GetState() const;
    Character GetCharacter();

    [[nodiscard]] uint64_t GetLevelUpMaxValue() const;
    [[nodiscard]] uint64_t GetEncumbrance();
    [[nodiscard]] uint64_t GetEncumbranceMaxValue() const;
    [[nodiscard]] uint64_t GetPlotMaxValue() const;

};
