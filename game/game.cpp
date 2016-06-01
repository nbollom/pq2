//
// Created by nbollom on 25/05/16.
//

#include "game.h"
#include "spells.h"
#include "offensiveattributes.h"
#include "defensiveattributes.h"
#include <iostream>

using namespace std;

Game::Game() {

}

void Game::tick(uint64_t ms) {
    cout << data::get_random_spell(&random) << endl;
    Attribute offAttribute = data::get_random_good_offensive_attribute(&random);
    cout << offAttribute.label << ", " << offAttribute.value << endl;
    Attribute defAttribute = data::get_random_bad_defensive_attribute(&random);
    cout << defAttribute.label << ", " << defAttribute.value << endl;
}