#include "pq2ncurses.h"

using namespace std;
using namespace game;

NCursesGUI::NCursesGUI(std::shared_ptr<Game> game) : GUI(game) {

}

void NCursesGUI::StartGameLoop() {

}

void NCursesGUI::Run() {
    if (_game->GetState() == GameStateReady) { //already have loaded a game, run loop
        StartGameLoop();
    }
    else {
#warning TODO: show game menu
    }
}
