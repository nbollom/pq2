//
// Created by nbollom on 13/01/19.
//

#include <ncurses.h>

#include "ncursesview.h"

NCursesView::NCursesView(const std::shared_ptr<Game>& game, const std::function<bool(std::string message, void *value)>& message_handler) : View(game, message_handler) {

}

void NCursesView::LeftAlign(const std::string& value, const int x, const int y) {
    mvprintw(y, x, "%s", value.c_str());
}

void NCursesView::RightAlign(const std::string& value, const int x, const int y) {
    mvprintw(y, x - static_cast<int>(value.length()), "%s", value.c_str());
}

void NCursesView::CenterAlign(const std::string& value, const int x, const int y) {
    mvprintw(y, x - static_cast<int>(static_cast<float>(value.length()) / 2), "%s", value.c_str());
}

void NCursesView::Resize(const int new_screen_width, const int new_screen_height) {
    screen_width = new_screen_width;
    screen_height = new_screen_height;
}