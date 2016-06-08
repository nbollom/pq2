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

using namespace std;

Game::Game() {
    random_device random;
    engine = make_shared<mt19937_64>(random());
}

shared_ptr<NewGame> Game::StartNewGame() {
    return make_shared<NewGame>(engine);
}

void Game::tick(uint64_t ms) {
    cout << data::get_random_spell(engine.get()) << endl;
    Attribute offAttribute = data::get_random_good_offensive_attribute(engine.get());
    cout << offAttribute.label << ", " << offAttribute.value << endl;
    Attribute defAttribute = data::get_random_bad_defensive_attribute(engine.get());
    cout << defAttribute.label << ", " << defAttribute.value << endl;
}