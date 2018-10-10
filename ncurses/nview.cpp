//
// Created by nbollom on 27/06/16.
//

#include "nview.h"
#include <ncurses.h>

NView::NView(std::shared_ptr<Game> game_ptr, std::function<bool(std::string message, void *value)> message_handler_callback) {
    game = game_ptr;
    message_handler = message_handler_callback;
}

void NView::Resize(int new_screen_width, int new_screen_height) {
    screen_width = new_screen_width;
    screen_height = new_screen_height;
}

void NView::LeftAlign(std::string value, int x, int y) {
    mvprintw(y, x, value.c_str());
}

void NView::RightAlign(std::string value, int x, int y) {
    mvprintw(y, x - (int)value.length(), value.c_str());
}

void NView::CenterAlign(std::string value, int x, int y) {
    mvprintw(y, x - (int)((float)value.length() / 2), value.c_str());
}
