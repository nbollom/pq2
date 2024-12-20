//
// Created by nbollom on 21/06/16.
//

#include "mainmenu.h"
#include <ncurses.h>
#include "ncursesview.h"
#include <iostream>
#include <ranges>

using namespace std;

typedef pair<string, function<void()>> MenuItem;
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

void MainMenu::Resize(const int new_screen_width, const int new_screen_height) {
    NCursesView::Resize(new_screen_width, new_screen_height);
    delwin(win);
    constexpr int required_width = 26;
    const int required_height = static_cast<int>(menu_options.size()) + 6;
    const int menu_top = max((screen_height / 3) - required_height / 2, 0);
    const int menu_left = max(0, (screen_width / 2) - required_width / 2);
    win = newwin(required_height, required_width, menu_top, menu_left);
    keypad(win, true);
    nodelay(win, true);
    wtimeout(win, 100);
}


void MainMenu::Render() {
    constexpr int horizontal_middle = 13;
    wclear(win);
    box(win, 0, 0);
    CenterAlign(win, "Progress Quest 2", horizontal_middle, 2);
    int index = 0;
    for (const auto& label : std::views::keys(menu_options)) {
        if (index == selected_index) {
            wattron(win, A_STANDOUT);
        }
        CenterAlign(win, label, horizontal_middle, 4 + index);
        if (index == selected_index) {
            wattroff(win, A_STANDOUT);
        }
        index++;
    }
    wrefresh(win);
    const int ch = wgetch(win);
    if (ch != ERR) {
        if (ch == 27) {
            message_handler("quit");
        }
        else if (ch == KEY_DOWN) {
            selected_index = min(selected_index + 1, static_cast<int>(menu_options.size()) - 1);
        }
        else if (ch == KEY_UP) {
            selected_index = max(selected_index - 1, 0);
        }
        else if (ch == '\n' || ch == ' ') {
            const auto [_, func] = menu_options[selected_index];
            func();
        }
    }
}
