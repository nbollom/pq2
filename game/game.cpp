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
using namespace game;
using namespace data;
using namespace file;

Game::Game() {
    random_device random;
    _engine = make_shared<mt19937_64>(random());
    _state = GameStateNone;
}

LoadError Game::LoadGame(string filename) {
    _filename = filename;

    _state = GameStateReady; //if loaded successfully
    return LoadErrorNone;
}

shared_ptr<NewGame> Game::StartNewGame() {
    return make_shared<NewGame>(_engine, [this](shared_ptr<Character> character){
        _character = character;
        _state = GameStateReady;
    });
}

void Game::Tick(uint64_t ms) {
    if (_state == GameStateReady) {

    }
}

GameState Game::GetState() {
    return _state;
}
