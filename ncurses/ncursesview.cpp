//
// Created by nbollom on 13/01/19.
//

#include <ncurses.h>
#include <ranges>

#include "ncursesview.hpp"

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

void NCursesView::ShowPopup(const std::string &label, const std::vector<std::string> &items, const int current_index) {
    const int desired_rows = static_cast<int>(items.size());
    const int rows = std::min(24 - 4, desired_rows);
    int skip = 0;
    const auto max_text_width = std::accumulate(items.begin(), items.end(), 26, [](const int max, const std::string &item) {
        return std::max(max, static_cast<int>(item.length()));
    });
    const int height = rows + 2;
    const int width = max_text_width + 6;
    if (height != last_popup_height || width != last_popup_width || !popup) {
        if (popup) {
            delwin(popup);
        }
        popup = subwin(win, height, width, 1, 4);
        last_popup_height = height;
        last_popup_width = width;
    }
    wclear(popup);
    box(popup, 0, 0);
    LeftAlign(popup, label, 2, 0);
    if (rows < desired_rows) {
        skip = std::clamp(current_index - rows / 2, 0, desired_rows - rows);
        wattron(popup, A_REVERSE);
        if (skip == 0) {
            mvwaddch(popup, 1, max_text_width + 4, ' ');
        }
        else if (skip + rows == desired_rows) {
            mvwaddch(popup, rows, max_text_width + 4, ' ');
        }
        else {
            const auto scroll_pos = static_cast<int>(static_cast<float>(skip) * static_cast<float>(rows) / static_cast<float>(desired_rows - rows)) + 1;
            mvwaddch(popup, scroll_pos, max_text_width + 4, ' ');
        }
        wattroff(popup, A_REVERSE);
    }
    int index = skip;
    for (const auto &item: items | std::ranges::views::drop(skip) | std::ranges::views::take(rows)) {
        if (current_index == index) {
            wattron(popup, A_STANDOUT);
        }
        LeftAlign(popup, item, 2, 1 + index - skip);
        wattroff(popup, A_STANDOUT);
        index++;
    }
    wnoutrefresh(popup);
}

void NCursesView::ClearPopup() {
    if (popup) {
        delwin(popup);
        popup = nullptr;
    }
}


void NCursesView::Resize(const int new_screen_width, const int new_screen_height) {
    screen_width = new_screen_width;
    screen_height = new_screen_height;
    delwin(win);
    win = newwin(std::min(required_height, screen_height), std::min(required_width, screen_width), 0, 0);
    keypad(win, true);
    nodelay(win, true);
    wtimeout(win, 100);
}

void NCursesView::Update() {
    wclear(win);
    if (screen_width < required_width || screen_height < required_height) {
        wprintw(win, "Progress Quest 2 requires a terminal of at least 80x24");
    }
    else {
        box(win, 0, 0);
        Render();
    }
    wnoutrefresh(win);
    doupdate();
    const int ch = wgetch(win);
    if (ch != ERR) {
        HandleKey(ch);
    }
}


void NCursesView::Show() {
    visible = true;
}

void NCursesView::Hide() {
    visible = false;
}

void NCursesView::Close() {

}

