//
// Created by nbollom on 25/05/16.
//

#include "game.hpp"
#include "spells.hpp"
#include "weapons.hpp"
#include "shields.hpp"
#include "armors.hpp"
#include "offensiveattributes.hpp"
#include "defensiveattributes.hpp"
#include "itemattributes.hpp"
#include "specials.hpp"
#include "itemofs.hpp"
#include "character.hpp"
#include "newgame.hpp"
#include "monsters.hpp"
#include "titles.hpp"
#include "races.hpp"
#include "classes.hpp"
#include "boringitems.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <utils.hpp>
#include <algorithm>
#include "jsonserialiser.hpp"

using namespace std;
using namespace game;
using namespace data;
using namespace file;

#define NPOS std::string::npos

template <typename T>
T Square(T x) {
    return x * x;
}

inline uint64_t EquipPrice(const uint64_t level) {
    return 5 * level * level
           + 10 * level
           + 20;
}

inline void AddToInventory(Character &character, const Stack &item) {
    bool found = false;
    for (auto& i: character.Inventory) {
        if (i.name == item.name) {
            i.count += item.count;
            found = true;
            break;
        }
    }
    if (!found) {
        character.Inventory.emplace_back(item);
    }
}

inline uint64_t RandomLow(const std::shared_ptr<std::mt19937_64> &engine, const uint64_t num) {
    return min(engine->operator()() % num, engine->operator()() % num);
}

inline std::string Plural(std::string s) {
    const size_t size = s.size();
    if (size > 1 && s.substr(size - 1) == "y") {
        return s.replace(size - 1, NPOS, "ies");
    }
    if (size > 2 && s.substr(size - 2) == "us") {
        return s.replace(size - 2, NPOS, "i");
    }
    if ((size > 2 && s.substr(size - 2) == "ch") || (size > 1 && (s.substr(size - 1) == "x" || s.substr(size - 1) == "s"))) {
        return s + "es";
    }
    if (size > 1 && s.substr(size - 1) == "f") {
        return s.replace(size - 1, NPOS, "ves");
    }
    if (size > 3 && (s.substr(size - 3) == "man" || s.substr(size - 3) == "Man")) {
        return s.replace(size - 2, NPOS, "en");
    }
    return s + "s";
}

inline std::string Indefinite(const std::string &name, const uint64_t count) {
    if (count == 1) {
        static std::string characters = "AEIOUÜaeiouü";
        const char c = name.front();
        if (characters.find(c) != NPOS) {
            return "an " + name;
        }
        return "a " + name;
    }
    return std::to_string(count) + " " + Plural(name);
}

inline std::string Definite(std::string name, const uint64_t count) {
    if (count > 1) {
        name = std::to_string(count) + " " + Plural(name);
    }
    return "the " + name;
}

inline bool Odds(const std::shared_ptr<std::mt19937_64> &engine, const uint64_t chance, const uint64_t out_of) {
    return (engine->operator()() % out_of) < chance;
}

Game::Game(): character() {
    random_device random;
    engine = make_shared<mt19937_64>(random());
    game_state = GameStateNone;
}

void Game::SetDaemonMode() {
    const function<void(int)> term_callback = [this](int){
        Close();
    };
    AddSignalCallback(SIGTERM, term_callback);
    AddSignalCallback(SIGINT, term_callback);
    AddSignalCallback(SIGQUIT, term_callback);
    AddSignalCallback(SIGKILL, term_callback);
}

LoadError Game::LoadGame(string filename_path) {
    filename = std::move(filename_path);
    if (std::ifstream file(filename); file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        try {
            deserialize(buffer.str(), character);
        }
        catch (const std::exception &e) {
            return LoadErrorNotValidSaveFile;
        }
    }
    game_state = GameStateReady; //if loaded successfully
    return LoadErrorNone;
}

SaveError Game::SaveGame(const string& filename_path) {
    if (!filename_path.empty()) {
        filename = filename_path;
    }
    if (filename.empty()) {
        return SaveErrorInvalidPath;
    }
    std::ofstream file(filename);
    file << serialise(character);
    file.close();
    return SaveErrorNone;
}

shared_ptr<NewGame> Game::StartNewGame() {
    return make_shared<NewGame>(engine, [this](const Character& character){
        this->character = character;
        this->character.Level = 1;
        this->character.Experience = 0;
        std::uniform_int_distribution<uint8_t> dist(0, 8);
        this->character.MAX_HP = dist(*engine) + character.CON / 6;
        this->character.MAX_MP = dist(*engine) + character.INT / 6;
        this->character.Equipment[Weapon] = "Sharp Stick";
        for (uint8_t i = Shield; i <= Sollerets; i++) {
            this->character.Equipment[i] = {std::string(), 0};
        }
        this->character.Gold = 0;
        this->character.Experience = 0;
        this->character.MaxQuestProgress = 0;
        this->character.CurrentAction = CurrentActionLoading;
        this->character.CurrentActionLabel = "Loading.";
        this->character.CurrentProgress = 0;
        this->character.MaxProgress = 2000;

        this->character.Queue.push_back({QueueItemTask, "Experiencing an enigmatic and foreboding night vision", 10});
        this->character.Queue.push_back({QueueItemTask, "Much is revealed about that wise old bastard you'd underestimated", 6});
        this->character.Queue.push_back({QueueItemTask, "A shocking series of events leaves you alone and bewildered, but resolute", 6});
        this->character.Queue.push_back({QueueItemTask, "Drawing upon an unexpected reserve of determination, you set out on a long and dangerous journey", 4});
        this->character.Queue.push_back({QueueItemPlot, "Loading", 2});
        this->character.Plot.emplace_back("Prologue");
        game_state = GameStateReady;
    });
}

void Game::Tick(uint64_t ms) {
    if (game_state == GameStateReady) {
        while (ms > 0) {
            const uint64_t progress = min(ms, static_cast<uint64_t>(100));
            const bool gain = character.CurrentAction == CurrentActionKill;
            if (character.CurrentProgress >= character.MaxProgress) {

                if(character.CurrentAction == CurrentActionLoading) {
                    character.MaxProgress = 0;
                }

                // gain XP / level up
                if (gain && character.Experience >= GetLevelUpMaxValue()) {
                    LevelUp();
                }
                else {
                    character.Experience += character.MaxProgress / 1000;
                }

                // advance quest
                if (gain && character.Plot.size() > 1) {
                    if (character.CurrentQuestProgress >= character.MaxQuestProgress) {
                        CompleteQuest();
                    }
                    else if (!character.Quests.empty()) {
                        character.CurrentQuestProgress += character.MaxProgress / 1000;
                    }
                }
                // advance plot
                if (gain && character.CurrentPlotProgress >= GetPlotMaxValue()) {
                    InterplotCinematic();
                }
                else {
                    character.CurrentPlotProgress += character.MaxProgress / 1000;
                }

                Dequeue();
            }
            else {
                character.CurrentProgress += progress;
            }
            ms -= progress;
        }
    }
}

GameState Game::GetState() const {
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

uint64_t Game::GetLevelUpMaxValue() const {
    // 20 minutes per level
    return 20 * character.Level * 60;
}

uint64_t Game::GetEncumbrance() {
    uint64_t encumbrance = 0;
    for (const auto& item: character.Inventory) {
        encumbrance += item.count;
    }
    return encumbrance;
}

uint64_t Game::GetEncumbranceMaxValue() const {
    return 10 + character.STR;
}

uint64_t Game::GetPlotMaxValue() const {
    if (character.Plot.size() <= 1) {
        return 26;
    }
    return 60 * 60 * (1 + 5 * character.Plot.size());
}

void Game::LevelUp() {
    character.Level += 1;
    std::uniform_int_distribution<uint8_t> dist(0, 4);
    character.MAX_HP += character.CON / 3 + 1 + dist(*engine);
    character.MAX_MP += character.INT / 3 + 1 + dist(*engine);
    WinStat();
    WinStat();
    WinSpell();
    character.Experience = 0;
    // TODO: raise events (updatestats, updatespells)
    SaveGame();
}

void Game::WinStat() {
    const auto odds = static_cast<uint8_t>(engine->operator()() % 2);
    int8_t stat = 0;
    uint64_t *stat_pointers[] = {
            &character.STR,
            &character.CON,
            &character.DEX,
            &character.INT,
            &character.WIS,
            &character.CHA,
            &character.MAX_HP,
            &character.MAX_MP,
    };
    if (odds < 1) {
        stat = static_cast<int8_t>(engine->operator()() % 8);
    }
    else {
        int64_t t = 0;
        for (auto i = 0; i <= 5; i++) {
            t += Square(*stat_pointers[i]);
        }
        t = abs(static_cast<int8_t>(engine->operator()())) % t;
        stat = -1;
        while (t >= 0) {
            stat += 1;
            t -= Square(*stat_pointers[stat]);
        }
    }
    *stat_pointers[stat] += 1;
}

void Game::WinSpell() {
    const auto spells = get_spells();
    const uint64_t min_amount = min(character.WIS + character.Level, spells.size());
    const uint64_t random_number = RandomLow(engine, min_amount);
    const auto& spell = spells[static_cast<int>(random_number)];
    bool existing = false;
    for (auto& curr_spell: character.Spells) {
        if (curr_spell.name == spell) {
            curr_spell.count++;
            existing = true;
            break;
        }
    }
    if (!existing) {
        Stack new_spell = {spell, 1};
        character.Spells.emplace_back(new_spell);
    }
}

void Game::WinItem() {
    AddToInventory(character, {InterestingItem() + " of " + get_random_item_of(engine), 1});
}

void Game::WinEquip() {
    auto equipment_type = static_cast<Equipment>(engine->operator()() % static_cast<uint64_t>(Sollerets + 1));
    std::function<const Item(std::shared_ptr<std::mt19937_64>)> get_item;
    std::function<const Attribute(std::shared_ptr<std::mt19937_64>)> get_better;
    std::function<const Attribute(std::shared_ptr<std::mt19937_64>)> get_worse;
    if (equipment_type == Weapon) {
        get_item = &get_random_weapon;
        get_better = &get_random_good_offensive_attribute;
        get_worse = &get_random_bad_offensive_attribute;
    }
    else {
        get_better = &get_random_good_defensive_attribute;
        get_worse = &get_random_bad_defensive_attribute;
        if (equipment_type == Shield) {
            get_item = &get_random_shield;
        }
        else {
            get_item = &get_random_armor;
        }
    }
    Item item;
    { // LPick
        uint64_t goal = character.Level;
        item = get_item(engine);
        for (int i = 0; i < 5; i++) {
            uint64_t best = item.level;
            Item s = get_item(engine);
            uint64_t b1 = s.level;
            if (abs(static_cast<long long int>(goal - best)) > abs(static_cast<long long int>(goal - b1))) {
                item = s;
            }
        }
    }
    std::string name = item.label;
    uint64_t quality = item.level;
    int64_t plus = character.Level - quality;
    if (plus < 0) {
        get_better = get_worse;
    }
    int count = 0;
    std::vector<std::string> modifiers;
    while (count < 2 && plus != 0) {
        auto [label, qual] = get_better(engine);
        std::string modifier = label;
        if (ranges::find(modifiers, modifier) != modifiers.end()) {
            break; //no repeats
        }
        if (abs(plus) < abs(qual)) {
            break;
        }
        modifiers.push_back(modifier);
        plus -= qual;
        count ++;
    }
    for (auto& modifier: modifiers) {
        name.insert(0, modifier + " ");
    }
    if (plus != 0) {
        name.insert(0, std::to_string(plus) + " ");
    }
    if (plus > 0) {
        name.insert(0, "+");
    }
    character.Equipment[equipment_type] = name;
}

void Game::CompleteAct() {
    character.CurrentPlotProgress = 0;
    const uint64_t count = character.Plot.size() - 1;
    const std::string roman = GetRomanNumerals(count + 1);
    std::string act_name = "Act " + roman;
    character.Plot.emplace_back(act_name);
    if (count > 1) {
        WinItem();
        WinEquip();
        SaveGame();
    }
}

std::string Game::InterestingItem() const {
    return get_random_item_attribute(engine) + " " + get_random_special(engine);
}

void Game::InterplotCinematic() {
    uint64_t r = engine->operator()() % 3;
    switch (r) {
        case 0:
            character.Queue.push_back({QueueItemTask, "Exhausted, you arrive at a friendly oasis in a hostile land", 1});
            character.Queue.push_back({QueueItemTask, "You greet old friends and meet new allies", 2});
            character.Queue.push_back({QueueItemTask, "You are privy to a council of powerful do-gooders", 2});
            character.Queue.push_back({QueueItemTask, "There is much to be done. You are chosen!", 1});
            break;
        case 1: {
            character.Queue.push_back({QueueItemTask, "Your quarry is in sight, but a mighty enemy bars your path!", 1});
            std::string nemesis;
                const uint64_t level = character.Level + 3;
                uint64_t lev = 0;
                for (int i = 0; i < 5; ++i) {
                    const Monster m = get_random_monster(engine);
                    if (nemesis.empty() || abs(static_cast<long long int>(level - m.level)) < abs(static_cast<long long int>(level - lev))) {
                        nemesis = m.name;
                        lev = m.level;
                    }
                }
                nemesis = GenerateRandomName(engine) + " the " + nemesis;
            character.Queue.push_back({QueueItemTask, "A desperate struggle commences with " + nemesis, 4});
            r = engine->operator()() % 3;
            switch (r) {
                case 0:
                    character.Queue.push_back({QueueItemTask, "Locked in grim combat with " + nemesis, 2});
                    break;
                case 1:
                    character.Queue.push_back({QueueItemTask, nemesis + "seems to have the upper hand!", 2});
                    break;
                default:
                    character.Queue.push_back({QueueItemTask, "You seem to gain the advantage over " + nemesis, 2});
            }
            character.Queue.push_back({QueueItemTask, "Victory! " + nemesis + " is slain! Exhausted, you lose consciousness", 3});
            character.Queue.push_back({QueueItemTask, "You awake in a friendly place, but the road awaits", 2});
            break;
        }
        default: {
            std::string nemesis = get_random_impressive_title(engine);
            if (engine->operator()() % 2) {
                nemesis.append(" of the " + get_random_race(engine).name);
            } else {
                nemesis.append(" of " + GenerateRandomName(engine));
            }
            character.Queue.push_back({QueueItemTask, "Oh sweet relief! You've reached the protection of the good " + nemesis, 2});
            character.Queue.push_back({QueueItemTask, "There is rejoicing, and an unnerving encounter with " + nemesis + " in private", 3});
            character.Queue.push_back({QueueItemTask, "You forget your " + get_random_boring_item(engine) + " and go back to get it", 2});
            character.Queue.push_back({QueueItemTask, "What''s this!? You overhear something shocking!", 2});
            character.Queue.push_back({QueueItemTask, "Could " + nemesis + " be a dirty double-dealer?", 2});
            character.Queue.push_back({QueueItemTask, "Who can possibly be trusted with this news!? ... Oh yes, of course", 3});
        }
    }
    character.Queue.push_back({QueueItemPlot, "Loading", 1});
}

void Game::Dequeue() {
    while (character.CurrentProgress >= character.MaxProgress) {
        if (character.CurrentAction == CurrentActionKill) {
            if (character.CurrentMonster.drop == "*") {
                WinItem();
            }
            else if (!character.CurrentMonster.drop.empty()) {
                Monster m = character.CurrentMonster;
                const std::string item = m.name + " " + m.drop;
                AddToInventory(character, {item, 1});
            }
        }
        else if (character.CurrentAction == CurrentActionBuying) {
            character.Gold -= EquipPrice(character.Level);
            WinEquip();
        }
        else if (character.CurrentAction == CurrentActionMarket || character.CurrentAction == CurrentActionSelling) {
            if (character.CurrentAction == CurrentActionSelling) {
                Stack item = character.Inventory.front();
                uint64_t amount = item.count * character.Level;
                if (item.name.find(" of ") != NPOS) {
                    amount *= (1 + RandomLow(engine, 10)) * (1 + RandomLow(engine, character.Level));
                }
                character.Inventory.erase(character.Inventory.begin());
                character.Gold += amount;
            }
            if (!character.Inventory.empty()) {
                const auto [name, count] = character.Inventory.front();
                character.CurrentActionLabel = "Selling " + Indefinite(name, count);
                character.CurrentAction = CurrentActionSelling;
                character.CurrentProgress = 0;
                character.MaxProgress = 1000;
                break;
            }
        }
        const CurrentActionType old = character.CurrentAction;
        character.CurrentAction = CurrentActionNone;
        if (!character.Queue.empty()) {
            const auto [type, label, ms] = character.Queue.front();
            std::string item_label = label;
            if (type == QueueItemTask || type == QueueItemPlot) {
                if (type == QueueItemPlot) {
                    CompleteAct();
                    item_label = "Loading " + character.Plot.back();
                }
                character.CurrentActionLabel = item_label;
                character.CurrentProgress = 0;
                character.MaxProgress = ms * 1000;
                character.Queue.pop_front();
            }
            else {
                throw std::runtime_error("Should never get here");
            }
        }
        else if (GetEncumbrance() >= GetEncumbranceMaxValue()) {
            character.CurrentActionLabel = "Heading to market to sell loot";
            character.CurrentAction = CurrentActionMarket;
            character.CurrentProgress = 0;
            character.MaxProgress = 4000;
        }
        else if (old != CurrentActionKill && old != CurrentActionHeading) {
            if (character.Gold > EquipPrice(character.Level)) {
                character.CurrentActionLabel = "Negotiating purchase of better equipment";
                character.CurrentProgress = 0;
                character.MaxProgress = 5000;
                character.CurrentAction = CurrentActionBuying;
            }
            else {
                character.CurrentActionLabel = "Heading to the killing fields";
                character.CurrentProgress = 0;
                character.MaxProgress = 4000;
                character.CurrentAction = CurrentActionHeading;
            }
        }
        else {
            MonsterTask();
        }
    }
}

void Game::MonsterTask() {
    int64_t level = character.Level;
    int64_t lev;
    Monster monster;
    bool definite = false;
    for (int64_t i = level; i > 0; i--) {
        if (Odds(engine, 2, 5)) {
            level += (engine->operator()() % 2) * 2 - 1;
        }
    }
    level = max(level, static_cast<int64_t>(1));
    if (Odds(engine, 1, 25)) {
        // use an NPC every once in a while
        std::string name = get_random_race(engine).name;
        if (Odds(engine, 1, 2)) {
            name = "passing " + name + " " + get_random_class(engine).name;
        }
        else {
            name = get_random_title(engine, true);
            definite = true;
        }
        lev = level;
        monster = {name, static_cast<uint64_t>(level), "*"};
    }
    else if ((!character.Quests.empty() && character.Quests.back().monster.has_value()) && Odds(engine, 1, 4)) {
        // use the quest monster
        monster = character.Quests.back().monster.value();
        lev = static_cast<int64_t>(monster.level);
    }
    else {
        // pick the monster out of so many random ones closest to the level we want
        monster = get_random_monster(engine);
        lev = static_cast<int64_t>(monster.level);
        for (int i = 5; i > 0; i--) {
            Monster m1 = get_random_monster(engine);
            if (abs(static_cast<long long int>(level - m1.level)) < abs(static_cast<long long int>(level - lev))) {
                monster = m1;
                lev = static_cast<int64_t>(monster.level);
            }
        }
    }
    std::string name = monster.name;
    int64_t qty = 1;
    if (level - lev > 10) {
        qty = (level + (engine->operator()() % level)) / max(lev, static_cast<int64_t>(1));
        qty = max(qty, static_cast<int64_t>(1));
        level = level / qty;
    }

    if (level - lev <= -10) {
        name = "imaginary" + name;
    }
    else if (level - lev < -5) {
        int64_t i = 10 + (level - lev);
        i = 5 - (engine->operator()() % (i + 1));
        name = Sick(i, Young((lev - level) - i, name));
    }
    else if (level - lev < 0 && engine->operator()() % 2 == 1) {
        name = Sick(level - lev, name);
    }
    else if (level - lev < 0) {
        name = Young(level - lev, name);
    }
    else if (level - lev >= 10) {
        name = "messianic " + name;
    }
    else if (level - lev > 5) {
        int64_t i = 10 - (level - lev);
        i = 5 - (engine->operator()() % (i + 1));
        name = Big(i, Special((level - lev) - i, name));
    }
    else if (level - lev > 0 && engine->operator()() % 2 == 1) {
        name = Big(level-lev, name);
    }
    else if (level - lev > 0) {
        name = Special(level - lev, name);
    }
    lev = level;
    level = lev * qty;

    if (!definite) {
        name = Indefinite(name, static_cast<uint64_t>(qty));
    }
    character.CurrentAction = CurrentActionKill;
    character.CurrentMonster = monster;
    character.CurrentActionLabel = "Executing " + name;
    character.CurrentProgress = 0;
    character.MaxProgress = (5 * level * 1000) / character.Level;
}

void Game::CompleteQuest() {
    uint64_t lev = 0;
    character.CurrentQuestProgress = 0;
    character.MaxQuestProgress = 50 + (engine->operator()() % 100);
    if (!character.Quests.empty()) {
        switch (engine->operator()() % 4) {
            case 0:
                WinSpell();
                break;
            case 1:
                WinEquip();
                break;
            case 2:
                WinStat();
                break;
            default:
                WinItem();
        }
    }
    while (character.Quests.size() > 99) {
        character.Quests.erase(character.Quests.begin());
    }
    Quest quest;
    switch (engine->operator()() % 5) {
        case 0: {
            const uint64_t level = character.Level;
            for (int i = 1; i <= 4; i++) {
                const Monster m = get_random_monster(engine);
                if (i == 1 || abs(static_cast<long long int>(m.level - level)) < abs(static_cast<long long int>(lev - level))) {
                    lev = m.level;
                    quest.monster = m;
                }
            }
            quest.label = "Exterminate " + Definite(quest.monster->name, 2);
            break;
        }
        case 1:
            quest.label = "Seek " + Definite(InterestingItem(), 1);
            break;
        case 2:
            quest.label = "Deliver this " + get_random_boring_item(engine);
            break;
        case 3:
            quest.label = "Fetch me " + Indefinite(get_random_boring_item(engine), 1);
            break;
        default:
            const uint64_t level = character.Level;
            Monster m;
            for (int i = 1; i <= 2; i++) {
                m = get_random_monster(engine);
                if (i == 1 || abs(static_cast<long long int>(m.level - level)) < abs(static_cast<long long int>(lev - level))) {
                    lev = m.level;
                }
            }
            quest.label = "Placate " + Definite(m.name, 2);
            break;
    }
    character.Quests.emplace_back(quest);
    SaveGame();
}

std::string Game::Sick(const int64_t level, const std::string& name) {
    std::string result = std::to_string(level) + name; // just in case
    if (level == -5 || level == 5) {
        return "dead " + name;
    }
    if (level == -4 || level == 4) {
        return "comatose " + name;
    }
    if (level == -3 || level == 3) {
        return "crippled " + name;
    }
    if (level == -2 || level == 2) {
        return "sick " + name;
    }
    if (level == -1 || level == 1) {
        return "undernourished " + name;
    }
    return result;
}

std::string Game::Young(const int64_t level, const std::string& name) {
    std::string result = std::to_string(level) + name; // just in case
    if (level == -5 || level == 5) {
        return "foetal " + name;
    }
    if (level == -4 || level == 4) {
        return "baby " + name;
    }
    if (level == -3 || level == 3) {
        return "preadolescent " + name;
    }
    if (level == -2 || level == 2) {
        return "teenage " + name;
    }
    if (level == -1 || level == 1) {
        return "underage " + name;
    }
    return result;
}

std::string Game::Big(const int64_t level, const std::string& name) {
    std::string result = std::to_string(level) + name; // just in case
    if (level == -1 || level == 1) {
        return "greater " + name;
    }
    if (level == -2 || level == 2) {
        return "massive " + name;
    }
    if (level == -3 || level == 3) {
        return "enormous " + name;
    }
    if (level == -4 || level == 4) {
        return "giant " + name;
    }
    if (level == -5 || level == 5) {
        return "titanic " + name;
    }
    return result;
}

std::string Game::Special(const int64_t level, const std::string& name) {
    std::string result = name; // just in case
    if (level == -1 || level == 1) {
        if (name.find(' ') != NPOS) {
            return "veteran " + name;
        }
        return "Battle-" + name;
    }
    if (level == -2 || level == 2) {
        return "cursed " + name;
    }
    if (level == -3 || level == 3) {
        if (name.find(' ') != NPOS) {
            return "warrior " + name;
        }
        return "Ware-" + name;
    }
    if (level == -4 || level == 4) {
        return "undead " + name;
    }
    if (level == -5 || level == 5) {
        return "demon " + name;
    }
    return result;
}


