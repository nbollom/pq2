#include <utility>

//
// Created by nbollom on 25/05/16.
//

#include "game.h"
#include "spells.h"
#include "weapons.h"
#include "shields.h"
#include "armors.h"
#include "offensiveattributes.h"
#include "defensiveattributes.h"
#include "itemattributes.h"
#include "specials.h"
#include "itemofs.h"
#include "character.h"
#include "newgame.h"
#include "monsters.h"
#include "titles.h"
#include "races.h"
#include "boringitems.h"
#include <iostream>
#include <utils.h>
#include <algorithm>

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
        this->character.Experience = 0;
        this->character.MaxQuestProgress = 1; // Temporary until a quest is set
        this->character.CurrentAction = CurrentActionLoading;
        this->character.CurrentActionLabel = "Loading.";
        this->character.MaxProgress = 2000;

        this->character.Queue.push({QueueItemTask, {"Experiencing an enigmatic and foreboding night vision", 10}});
        this->character.Queue.push({QueueItemTask, {"Much is revealed about that wise old bastard you'd underestimated", 6}});
        this->character.Queue.push({QueueItemTask, {"A shocking series of events leaves you alone and bewildered, but resolute", 6}});
        this->character.Queue.push({QueueItemTask, {"Drawing upon an unexpected reserve of determination, you set out on a long and dangerous journey", 4}});
        this->character.Queue.push({QueueItemTask, {"Loading", 2}});
        /*
            fTask.Caption := '';
            fQuest.Caption := '';
            fQueue.Items.Clear;

            Task('Loading.',2000); // that dot is spotted for later...
            Q('task|10|Experiencing an enigmatic and foreboding night vision');
            Q('task|6|Much is revealed about that wise old bastard you''d underestimated');
            Q('task|6|A shocking series of events leaves you alone and bewildered, but resolute');
            Q('task|4|Drawing upon an unexpected reserve of determination, you set out on a long and dangerous journey');
            Q('task|2|Loading');

            PlotBar.Max := 26;
            with Plots.Items.Add do begin
            Caption := 'Prologue';
            StateIndex := 0;
            end;
        */
        game_state = GameStateReady;
    });
}

void Game::Tick(uint64_t ms) {
    if (game_state == GameStateReady) {
        /*
            gain := Pos('kill|',fTask.Caption) = 1;
            with TaskBar do begin
              if Position >= Max then begin
                ClearAllSelections;

                if Kill.SimpleText = 'Loading....' then Max := 0;

                // gain XP / level up
                if gain then with ExpBar do if Position >= Max
                then LevelUp
                else Position := Position + TaskBar.Max div 1000;
                with ExpBar do Hint := IntToStr(Max-Position) + ' XP needed for next level';

                // advance quest
                if gain then if Plots.Items.Count > 1 then with QuestBar do if Position >= Max then begin
                  CompleteQuest;
                end else if Quests.Items.Count > 0 then begin
                  Position := Position + TaskBar.Max div 1000;
                  Hint := IntToStr(100 * Position div Max) + '% complete';
                end;

                // advance plot
                if gain then with PlotBar do if Position >= Max
                then InterplotCinematic
                else Position := Position + TaskBar.Max div 1000;

                //Time.Caption := FormatDateTime('h:mm:ss',PlotBar.Position / (24.0 * 60 * 60));
                PlotBar.Hint := RoughTime(PlotBar.Max-PlotBar.Position) + ' remaining';
                //PlotBar.Hint := FormatDateTime('h:mm:ss" remaining"',(PlotBar.Max-PlotBar.Position) / (24.0 * 60 * 60));

                Dequeue();
              end else with TaskBar do begin
                elapsed := LongInt(timeGetTime) - LongInt(Timer1.Tag);
                if elapsed > 100 then elapsed := 100;
                if elapsed < 0 then elapsed := 0;
                Position := Position + elapsed;
              end;
            end;
            Timer1.Tag := timeGetTime;
        */
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

uint64_t Game::GetPlotMaxValue() {
    return 60 * 60 * (1 + 5 * character.Plot.size());
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
    auto odds = static_cast<uint8_t>(engine->operator()() % 2);
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
    auto spells = get_spells();
    uint64_t min_amount = min(character.WIS + character.Level, spells.size());
    uint64_t random_number = min(engine->operator()() % min_amount, engine->operator()() % min_amount);
    auto spell = spells[static_cast<int>(random_number)];
    bool existing = false;
    for (auto& curr_spell: character.Spells) {
        if (curr_spell.name == spell) {
            curr_spell.count++;
            existing = true;
            break;
        }
    }
    if (!existing) {
        data::Stack new_spell = {spell, 1};
        character.Spells.emplace_back(new_spell);
    }
}

void Game::WinItem() {
    data::Stack item = {InterestingItem() + " of " + get_random_item_of(engine), 1};
    character.Inventory.emplace_back(item);
}

void Game::WinEquip() {
    Equipment equipment_type = static_cast<Equipment>(engine->operator()() % static_cast<uint64_t>(Sollerets + 1));
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
        Attribute attr = get_better(engine);
        int64_t qual = attr.value;
        std::string modifier = attr.label;
        if (std::find(modifiers.begin(), modifiers.end(), modifier) != modifiers.end()) {
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
    uint64_t count = character.Plot.size();
    std::string roman = GetRomanNumerals(count + 1);
    std::string act_name = "Act " + roman;
    character.Plot.emplace_back(act_name);
    WinItem();
    WinEquip();
    SaveGame();
}

std::string Game::InterestingItem() {
    return get_random_item_attribute(engine) + " " + get_random_special(engine);
}

void Game::InterplotCinematic() {
    uint64_t r = engine->operator()() % 3;
    switch (r) {
        case 0:
            character.Queue.push({QueueItemTask, {"Exhausted, you arrive at a friendly oasis in a hostile land", 1}});
            character.Queue.push({QueueItemTask, {"You greet old friends and meet new allies", 2}});
            character.Queue.push({QueueItemTask, {"You are privy to a council of powerful do-gooders", 2}});
            character.Queue.push({QueueItemTask, {"There is much to be done. You are chosen!", 1}});
            break;
        case 1: {
            character.Queue.push({QueueItemTask, {"Your quarry is in sight, but a mighty enemy bars your path!", 1}});
            std::string nemesis;
                uint64_t level = character.Level + 3;
                uint64_t lev = 0;
                for (int i = 0; i < 5; ++i) {
                    Monster m = get_random_monster(engine);
                    if (nemesis.empty() || abs(static_cast<long long int>(level - m.level)) < abs(static_cast<long long int>(level - lev))) {
                        nemesis = m.name;
                        lev = m.level;
                    }
                }
                nemesis = GenerateRandomName(engine) + " the " + nemesis;
            character.Queue.push({QueueItemTask, {"A desperate struggle commences with " + nemesis, 4}});
            r = engine->operator()() % 3;
            switch (r) {
                case 0:
                    character.Queue.push({QueueItemTask, {"Locked in grim combat with " + nemesis, 2}});
                    break;
                case 1:
                    character.Queue.push({QueueItemTask, {nemesis + "seems to have the upper hand!", 2}});
                    break;
                default:
                    character.Queue.push({QueueItemTask, {"You seem to gain the advantage over " + nemesis, 2}});
            }
            character.Queue.push({QueueItemTask, {"Victory! " + nemesis + " is slain! Exhausted, you lose conciousness", 3}});
            character.Queue.push({QueueItemTask, {"You awake in a friendly place, but the road awaits", 2}});
            break;
        }
        default: {
            std::string nemesis = get_random_impressive_title(engine);
            if (engine->operator()() % 2) {
                nemesis.append(" of the " + get_random_race(engine).name);
            } else {
                nemesis.append(" of " + GenerateRandomName(engine));
            }
            character.Queue.push({QueueItemTask, {"Oh sweet relief! You've reached the protection of the good " + nemesis, 2}});
            character.Queue.push({QueueItemTask, {"There is rejoicing, and an unnerving encouter with " + nemesis + " in private", 3}});
            character.Queue.push({QueueItemTask, {"You forget your " + get_random_boring_item(engine) + " and go back to get it", 2}});
            character.Queue.push({QueueItemTask, {"What''s this!? You overhear something shocking!", 2}});
            character.Queue.push({QueueItemTask, {"Could " + nemesis + " be a dirty double-dealer?", 2}});
            character.Queue.push({QueueItemTask, {"Who can possibly be trusted with this news!? ... Oh yes, of course", 3}});
        }
    }
    character.Queue.push({QueueItemPlot, {"Loading", 1}});
}

