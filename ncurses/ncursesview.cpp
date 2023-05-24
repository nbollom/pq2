//
// Created by nbollom on 13/01/19.
//

#include <ncurses.h>

#include "ncursesview.h"

NCursesView::NCursesView(std::shared_ptr<Game> game, std::function<bool(std::string message, void *value)> message_handler) : View(game, message_handler) {

}

void NCursesView::LeftAlign(std::string value, int x, int y) {
    mvprintw(y, x, value.c_str());
}

void NCursesView::RightAlign(std::string value, int x, int y) {
    mvprintw(y, x - (int)value.length(), value.c_str());
}

void NCursesView::CenterAlign(std::string value, int x, int y) {
    mvprintw(y, x - (int)((float)value.length() / 2), value.c_str());
}

void NCursesView::Resize(int new_screen_width, int new_screen_height) {
    screen_width = new_screen_width;
    screen_height = new_screen_height;
}