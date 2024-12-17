//
// Created by nbollom on 21/06/16.
//

#include "mainmenu.h"
#include <ncurses.h>
#include "ncursesview.h"
#include <iostream>

using namespace std;

typedef pair<string, function<void()>> MenuItem;
typedef std::vector<MenuItem>::iterator MenuItemIterator;

MainMenu::MainMenu(const std::shared_ptr<Game>& game, const std::function<bool(std::string message, void *value)>& message_handler) : NCursesView(game, message_handler) {
    selected_index = 0;
    menu_options.emplace_back("New Game", [this, game] {
        game->StartNewGame();
    });
    menu_options.emplace_back("Load Game", [this, game] {

    });
    menu_options.emplace_back("Quit", [message_handler] {
        message_handler("Quit", nullptr);
    });
}

void MainMenu::HandleKeyPress(const int key) {
    if (key == KEY_DOWN) {
        selected_index = min(selected_index + 1, static_cast<int>(menu_options.size()) - 1);
    }
    else if (key == KEY_UP) {
        selected_index = max(selected_index - 1, 0);
    }
    else if (key == KEY_ENTER || key == 10) {
        const MenuItem item = menu_options[selected_index];
        item.second();
    }
    else {
        cout << "Unhandled key " << key << endl;
    }
}

void MainMenu::Render() {
    const int horizontal_middle = screen_width / 2;
    const int menu_top = max((screen_height / 3) - (static_cast<int>(menu_options.size()) + 3) / 2, 0);
    CenterAlign("Progress Quest 2", horizontal_middle, menu_top);
    int index = 0;
    for (const auto& item : menu_options) {
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

void MainMenu::Show() {

}

void MainMenu::Hide() {

}

void MainMenu::Close() {

}
