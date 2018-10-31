#include <utility>

//
// Created by nbollom on 25/05/16.
//

#include "game.h"
#include "spells.h"
#include "offensiveattributes.h"
#include "defensiveattributes.h"
#include "character.h"
#include "newgame.h"
#include <iostream>
#include "utils.h"

using namespace std;
using namespace game;
using namespace data;
using namespace file;

template <typename T>
inline T Square(T x) {
    return x * x;
}

Game::Game() {
    random_device random;
    engine = make_shared<mt19937_64>(random());
    game_state = GameStateNone;

    // NOTE: Temporary for debugging game screen
    auto ng = StartNewGame();
    ng->ConfirmCharacter();
}

void Game::SetDaemonMode() {
    function<void(int)> term_callback = [this](int signal){
        Close();
    };
    AddSignalCallback(SIGTERM, term_callback);
    AddSignalCallback(SIGINT, term_callback);
    AddSignalCallback(SIGQUIT, term_callback);
    AddSignalCallback(SIGKILL, term_callback);
}

LoadError Game::LoadGame(string filename_path) {
    filename = std::move(filename_path);
    // TODO: Load game state from file
    game_state = GameStateReady; //if loaded successfully
    return LoadErrorNone;
}

SaveError Game::SaveGame(string filename_path) {
    if (!filename_path.empty()) {
        filename = filename_path;
    }
    if (filename.empty()) {
        return SaveErrorInvalidPath;
    }
    return SaveErrorNone;
}

shared_ptr<NewGame> Game::StartNewGame() {
    return make_shared<NewGame>(engine, [this](Character character){
        this->character = character;
        this->character.Level = 1;
        this->character.Experience = 0;
        std::uniform_int_distribution<uint8_t> dist(0, 8);
        this->character.MAXHP = dist(*engine) + character.CON / 6;
        this->character.MAXMP = dist(*engine) + character.INT / 6;
        this->character.Equipment[Weapon] = {"Sharp Stick", 0};
        for (uint8_t i = Shield; i <= Sollerets; i++) {
            this->character.Equipment[i] = {"", 0};
        }
        this->character.CurrentProgress = 0;
        this->character.Gold = 0;
        game_state = GameStateReady;
    });
}

void Game::Tick(uint64_t ms) {
    if (game_state == GameStateReady) {

    }
}

GameState Game::GetState() {
    return game_state;
}

void Game::Close() {
    cout << "Closing" << endl;
    SaveGame();
    game_state = GameStateFinished;
}

Character Game::GetCharacter() {
    return character;
}

uint64_t Game::GetLevelUpMaxValue() {
    // 20 mins per level
    return 20 * character.Level * 60;
}

uint64_t Game::GetEncumbrance() {
    uint64_t encumbrance = 0;
    for (auto& item: character.Inventory) {
        encumbrance += item.count;
    }
    return encumbrance;
}

uint64_t Game::GetEncumbranceMaxValue() {
    return 10 + character.STR;
}

void Game::LevelUp() {
    character.Level += 1;
    std::uniform_int_distribution<uint8_t> dist(0, 4);
    character.MAXHP += character.CON / 3 + 1 + dist(*engine);
    character.MAXMP += character.INT / 3 + 1 + dist(*engine);
    WinStat();
    WinStat();
    WinSpell();
    character.Experience = 0;
    // TODO: raise events (updatestats, updatespells)
    SaveGame();
}

void Game::WinStat() {
    auto odds = static_cast<uint8_t>((*engine)() % 2);
    int8_t stat = 0;
    uint64_t *stat_pointers[] = {
            &character.STR,
            &character.CON,
            &character.DEX,
            &character.INT,
            &character.WIS,
            &character.CHA,
            &character.MAXHP,
            &character.MAXMP,
    };
    if (odds < 1) {
        stat = static_cast<int8_t>((*engine)() % 8);
    }
    else {
        int64_t t = 0;
        for (auto i = 0; i <= 5; i++) {
            t += Square(*stat_pointers[i]);
        }
        t = static_cast<int8_t>((*engine)() % t);
        stat = -1;
        while (t >= 0) {
            stat += 1;
            t -= Square(*stat_pointers[stat]);
        }
    }
    *stat_pointers[stat] += 1;
}

void Game::WinSpell() {
    uint64_t min_amount = min(character.WIS + character.Level, character.Spells.size());
    uint64_t random_number = min((*engine)() % min_amount, (*engine)() % min_amount);
    character.Spells[static_cast<int>(random_number)].count += 1;
}

