//
// Created by nbollom on 27/06/16.
//

#include "view.h"
#include <ncurses.h>

View::View(std::shared_ptr<Game> game_ptr, std::function<bool(std::string message, void *value)> message_handler_callback) {
    game = game_ptr;
    message_handler = message_handler_callback;
}

void View::Resize(int new_screen_width, int new_screen_height) {
    screen_width = new_screen_width;
    screen_height = new_screen_height;
}

void View::LeftAlign(std::string value, int x, int y) {
    mvprintw(y, x, value.c_str());
}

void View::RightAlign(std::string value, int x, int y) {
    mvprintw(y, x - (int)value.length(), value.c_str());
}

void View::CenterAlign(std::string value, int x, int y) {
    mvprintw(y, x - (int)((float)value.length() / 2), value.c_str());
}
