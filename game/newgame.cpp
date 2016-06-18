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

NewGame::NewGame(shared_ptr<mt19937_64> engine, std::function<void(std::shared_ptr<Character> character)>callback) {
    _engine = engine;
    _callback = callback;
    _character = make_shared<Character>();
    GenerateName();
    _character->CharacterRace = data::get_random_race(_engine.get());
    _character->CharacterClass = data::get_random_class(_engine.get());
    RollEm();
}

void NewGame::RollEm() {
    RollStat(&_character->STR);
    RollStat(&_character->CON);
    RollStat(&_character->DEX);
    RollStat(&_character->INT);
    RollStat(&_character->WIS);
    RollStat(&_character->CHA);
}

void NewGame::RollStat(uint64_t *stat) {
    static uniform_int_distribution<uint64_t> distribution(0, 5);
    *stat = 3 + distribution(*_engine) + distribution(*_engine) + distribution(*_engine);
}

void NewGame::GenerateName() {
    static vector<string> parts1 = {"br", "cr", "dr", "fr", "gr", "j", "kr", "l", "m", "n", "pr", "r", "sh", "tr", "v", "wh", "x", "y", "z"};
    static vector<string> parts2 = {"a", "a", "e", "e", "i", "i", "o", "o", "u", "u", "ae", "ie", "oo", "ou"};
    static vector<string> parts3 = {"b", "ck", "d", "g", "k", "m", "n", "p", "t", "v", "x", "z"};
    static uniform_int_distribution<unsigned long> distribution1(0, parts1.size() - 1);
    static uniform_int_distribution<unsigned long> distribution2(0, parts2.size() - 1);
    static uniform_int_distribution<unsigned long> distribution3(0, parts3.size() - 1);
    string result = "";
    for (int i = 0; i < 6; ++i) {
        string part;
        switch (i % 3) {
            case 0:
                part = parts1[distribution1(*_engine)];
                break;
            case 1:
                part = parts2[distribution2(*_engine)];
                break;
            case 2:
                part = parts3[distribution3(*_engine)];
                break;
        }
        result.append(part);
    }
    result[0] = result[0] - (char)32;
    _character->Name = result;
}

string NewGame::GetName() {
    return _character->Name;
}

void NewGame::SetName(string name) {
    _character->Name = name;
}

typedef vector<Race>::iterator RI;

vector<string> NewGame::GetAvailableRaces() {
    auto races = data::get_race_list();
    vector<string> raceNames;
    for (RI i = races.begin(); i != races.end(); i++) {
        Race r = *i;
        raceNames.push_back(r.name);
    }
    return raceNames;
}

string NewGame::GetRace() {
    return _character->CharacterRace.name;
}

void NewGame::SetRace(string name) {
    auto races = data::get_race_list();
    for (RI i = races.begin(); i != races.end(); i++) {
        Race r = *i;
        if (r.name == name) {
            _character->CharacterRace = r;
        }
    }
}

typedef vector<Class>::iterator CI;

vector<string> NewGame::GetAvailableClasses() {
    auto classes = data::get_class_list();
    vector<string> classNames;
    for (CI i = classes.begin(); i != classes.end(); i++) {
        Class c = *i;
        classNames.push_back(c.name);
    }
    return classNames;
}

string NewGame::GetClass() {
    return _character->CharacterClass.name;
}

void NewGame::SetClass(string name) {
    auto classes = data::get_class_list();
    for (CI i = classes.begin(); i != classes.end(); i++) {
        Class c = *i;
        if (c.name == name) {
            _character->CharacterClass = c;
        }
    }
}

void NewGame::ReRoll() {
    array<uint64_t, 6> values = {_character->STR, _character->CON, _character->DEX, _character->INT, _character->WIS, _character->CHA};
    _unrollBuffer.push(values);
    RollEm();
}

bool NewGame::CanUnroll() {
    return _unrollBuffer.size() > 0;
}

void NewGame::UnRoll() {
    if (!_unrollBuffer.empty()) {
        array<uint64_t, 6> values = _unrollBuffer.top();
        _character->STR = values[0];
        _character->CON = values[1];
        _character->DEX = values[2];
        _character->INT = values[3];
        _character->WIS = values[4];
        _character->CHA = values[5];
        _unrollBuffer.pop();
    }
}

uint64_t NewGame::GetSTR() {
    return _character->STR;
}

uint64_t NewGame::GetCON() {
    return _character->CON;
}

uint64_t NewGame::GetDEX() {
    return _character->DEX;
}

uint64_t NewGame::GetINT() {
    return _character->INT;
}

uint64_t NewGame::GetWIS() {
    return _character->WIS;
}

uint64_t NewGame::GetCHA() {
    return _character->CHA;
}

uint64_t NewGame::GetTotal() {
    return _character->STR + _character->CON + _character->DEX + _character->INT + _character->WIS + _character->CHA;
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
    _callback(_character);
}
