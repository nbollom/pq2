//
// Created by nbollom on 21/06/16.
//

#include "mainmenu.hpp"
#include <ncurses.h>
#include "ncursesview.hpp"
#include <iostream>
#include <ranges>

typedef std::pair<std::string, std::function<void()>> MenuItem;
typedef std::vector<MenuItem>::iterator MenuItemIterator;

MainMenu::MainMenu(const std::shared_ptr<Game>& game, const MessageHandler& message_handler) : NCursesView(game, message_handler) {
    selected_index = 0;
    menu_options.emplace_back("Start New Game", [message_handler] {
        message_handler("new");
    });
    menu_options.emplace_back("Load Game", [] {

    });
    menu_options.emplace_back("Quit", [message_handler] {
        message_handler("quit");
    });
}


void MainMenu::Render() {
    constexpr int horizontal_middle = 40;
    CenterAlign(win, "Progress Quest 2", horizontal_middle, 8);
    int index = 0;
    for (const auto& label : std::views::keys(menu_options)) {
        if (index == selected_index) {
            wattron(win, A_STANDOUT);
        }
        CenterAlign(win, label, horizontal_middle, 10 + index);
        if (index == selected_index) {
            wattroff(win, A_STANDOUT);
        }
        index++;
    }
}

void MainMenu::HandleKey(const int key) {
    if (key == 27) {
        message_handler("quit");
    }
    else if (key == KEY_DOWN) {
        selected_index = std::min(selected_index + 1, static_cast<int>(menu_options.size()) - 1);
    }
    else if (key == KEY_UP) {
        selected_index = std::max(selected_index - 1, 0);
    }
    else if (key == '\n' || key == ' ') {
        const auto [_, func] = menu_options[selected_index];
        func();
    }
}

