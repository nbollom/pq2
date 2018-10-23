#include <utility>

#include <utility>

//
// Created by nbollom on 3/06/16.
//

#include <iostream>
#include <vector>
#include "newgame.h"
#include "races.h"
#include "classes.h"
#include "types.h"

using namespace std;
using namespace data;
using namespace ui;

NewGame::NewGame(shared_ptr<mt19937_64> randomengine, std::function<void(Character character)> complete_callback) {
    engine = std::move(randomengine);
    callback = std::move(complete_callback);
    GenerateName();
    character.CharacterRace = data::get_random_race(engine.get());
    character.CharacterClass = data::get_random_class(engine.get());
    RollEm();
}

void NewGame::RollEm() {
    RollStat(&character.STR);
    RollStat(&character.CON);
    RollStat(&character.DEX);
    RollStat(&character.INT);
    RollStat(&character.WIS);
    RollStat(&character.CHA);
}

void NewGame::RollStat(uint64_t *stat) {
    static uniform_int_distribution<uint64_t> distribution(0, 5);
    *stat = 3 + distribution(*engine) + distribution(*engine) + distribution(*engine);
}

void NewGame::GenerateName() {
    static vector<string> parts1 = {"br", "cr", "dr", "fr", "gr", "j", "kr", "l", "m", "n", "pr", "r", "sh", "tr", "v", "wh", "x", "y", "z"};
    static vector<string> parts2 = {"a", "a", "e", "e", "i", "i", "o", "o", "u", "u", "ae", "ie", "oo", "ou"};
    static vector<string> parts3 = {"b", "ck", "d", "g", "k", "m", "n", "p", "t", "v", "x", "z"};
    static uniform_int_distribution<unsigned long> distribution1(0, parts1.size() - 1);
    static uniform_int_distribution<unsigned long> distribution2(0, parts2.size() - 1);
    static uniform_int_distribution<unsigned long> distribution3(0, parts3.size() - 1);
    string result;
    for (int i = 0; i < 6; ++i) {
        string part;
        switch (i % 3) {
            case 0:
                part = parts1[distribution1(*engine)];
                break;
            case 1:
                part = parts2[distribution2(*engine)];
                break;
            case 2:
                part = parts3[distribution3(*engine)];
                break;
            default:break;
        }
        result.append(part);
    }
    result[0] = result[0] - (char)32;
    character.Name = result;
}

string NewGame::GetName() {
    return character.Name;
}

void NewGame::SetName(string name) {
    character.Name = std::move(name);
}

typedef vector<Race>::iterator RI;

vector<string> NewGame::GetAvailableRaces() {
    auto races = data::get_race_list();
    vector<string> raceNames;
    raceNames.reserve(races.size());
    for (auto r : races) {
        raceNames.push_back(r.name);
    }
    return raceNames;
}

string NewGame::GetRace() {
    return character.CharacterRace.name;
}

void NewGame::SetRace(string name) {
    auto races = data::get_race_list();
    for (auto r : races) {
        if (r.name == name) {
            character.CharacterRace = r;
            break;
        }
    }
}

vector<string> NewGame::GetAvailableClasses() {
    auto classes = data::get_class_list();
    vector<string> classNames;
    classNames.reserve(classes.size());
    for (auto c : classes) {
        classNames.push_back(c.name);
    }
    return classNames;
}

string NewGame::GetClass() {
    return character.CharacterClass.name;
}

void NewGame::SetClass(string name) {
    auto classes = data::get_class_list();
    for (auto c : classes) {
        if (c.name == name) {
            character.CharacterClass = c;
            break;
        }
    }
}

void NewGame::ReRoll() {
    array<uint64_t, 6> values = {character.STR, character.CON, character.DEX, character.INT, character.WIS, character.CHA};
    unrollBuffer.push(values);
    RollEm();
}

bool NewGame::CanUnroll() {
    return !unrollBuffer.empty();
}

void NewGame::UnRoll() {
    if (!unrollBuffer.empty()) {
        array<uint64_t, 6> values = unrollBuffer.top();
        character.STR = values[0];
        character.CON = values[1];
        character.DEX = values[2];
        character.INT = values[3];
        character.WIS = values[4];
        character.CHA = values[5];
        unrollBuffer.pop();
    }
}

uint64_t NewGame::GetSTR() {
    return character.STR;
}

uint64_t NewGame::GetCON() {
    return character.CON;
}

uint64_t NewGame::GetDEX() {
    return character.DEX;
}

uint64_t NewGame::GetINT() {
    return character.INT;
}

uint64_t NewGame::GetWIS() {
    return character.WIS;
}

uint64_t NewGame::GetCHA() {
    return character.CHA;
}

uint64_t NewGame::GetTotal() {
    return character.STR + character.CON + character.DEX + character.INT + character.WIS + character.CHA;
}

Color NewGame::GetTotalColor() {
    uint64_t total = GetTotal();
    Color color;
    if (total >= 81) {
        color = ColorRed;
    }
    else if (total >= 73) {
        color = ColorYellow;
    }
    else if (total <= 45) {
        color = ColorGray;
    }
    else if (total <= 53) {
        color = ColorSilver;
    }
    else {
        color = ColorWhite;
    }
    return color;
}

void NewGame::ConfirmCharacter() {
    callback(character);
}
