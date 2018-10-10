//
// Created by nbollom on 21/06/16.
//

#include "mainmenu.h"
#include <ncurses.h>

using namespace std;

typedef pair<string, function<void()>> MenuItem;
typedef std::vector<MenuItem>::iterator MenuItemIterator;

MainMenu::MainMenu(std::shared_ptr<Game> game, std::function<bool(std::string message, void *value)> messageHandler) : NView(game, messageHandler) {
    selected_index = 0;
    menu_options.emplace_back(MenuItem("New Game", [this, game](){
        game->StartNewGame();
    }));
    menu_options.emplace_back(MenuItem("Load Game", [this, game](){

    }));
    menu_options.emplace_back(MenuItem("Quit", [this, game, messageHandler](){
        messageHandler("Quit", nullptr);
    }));
}

void MainMenu::HandleKeyPress(int key) {
    if (key == KEY_DOWN) {
        selected_index = min(selected_index + 1, (int)menu_options.size() - 1);
    }
    else if (key == KEY_UP) {
        selected_index = max(selected_index - 1, 0);
    }
    else if (key == KEY_ENTER) {
        MenuItem item = menu_options[selected_index];
        item.second();
    }
}

void MainMenu::Render() {
    int horizontal_middle = screen_width / 2;
    int menu_top = max((screen_height / 3) - (((int)menu_options.size() + 3) / 2), 0);
    CenterAlign("Progress Quest 2", horizontal_middle, menu_top);
    int index = 0;
    for (auto item : menu_options) {
        if (index == selected_index) {
            attron(A_UNDERLINE);
        }
        CenterAlign(item.first, horizontal_middle, menu_top + 2 + index);
        if (index == selected_index) {
            attroff(A_UNDERLINE);
        }
        index++;
    }
    move(0, 0); //reset cursor to top left
}
