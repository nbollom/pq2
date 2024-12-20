//
// Created by nbollom on 13/01/19.
//

#include <ncurses.h>

#include "ncursesview.h"

NCursesView::NCursesView(const std::shared_ptr<Game>& game, const MessageHandler& message_handler) : View(game, message_handler) {

}

void NCursesView::LeftAlign(WINDOW *win, const std::string& value, const int x, const int y) {
    mvwprintw(win, y, x, "%s", value.c_str());
}

void NCursesView::RightAlign(WINDOW *win, const std::string& value, const int x, const int y) {
    mvwprintw(win, y, x - static_cast<int>(value.length()), "%s", value.c_str());
}

void NCursesView::CenterAlign(WINDOW *win, const std::string& value, const int x, const int y) {
    mvwprintw(win, y, x - static_cast<int>(static_cast<float>(value.length()) / 2), "%s", value.c_str());
}

void NCursesView::Resize(const int new_screen_width, const int new_screen_height) {
    screen_width = new_screen_width;
    screen_height = new_screen_height;
}

void NCursesView::Show() {
    visible = true;
}

void NCursesView::Hide() {
    visible = false;
}

void NCursesView::Close() {

}

