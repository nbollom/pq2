//
// Created by nbollom on 2/01/25.
//

#include "loadscreen.hpp"
#include <ranges>
#include <format>

#define LEFT 2

LoadScreen::LoadScreen(const std::shared_ptr<Game> &game, const MessageHandler &message_handler) : NCursesView(game, message_handler) {
    ChangeDir(std::filesystem::current_path());
}

void LoadScreen::ChangeDir(const std::filesystem::path &new_path) {
    current_index = 0;
    if (new_path == "..") {
        path = path.parent_path();
    }
    else {
        path = absolute(new_path);
    }
    files.clear();
    if (path.has_parent_path()) {
        files.emplace_back("..");
    }
    for (auto &entry: std::filesystem::directory_iterator(path)) {
        if (entry.is_directory() || entry.path().extension() == ".pq2") {
            files.push_back(entry.path());
        }
    }
    std::sort(files.begin(), files.end(), [](const std::filesystem::path &a, const std::filesystem::path &b) {
        if (a == "..") {
            return true;
        }
        if (b == "..") {
            return false;
        }
        if (is_directory(a) && !is_directory(b)) {
            return true;
        }
        if (is_directory(a) && is_directory(b)) {
            return a < b;
        }
        if (!is_directory(a) && is_directory(b)) {
            return false;
        }
        return a < b;
    });
}


void LoadScreen::Render() {
    LeftAlign(win, "Progress Quest 2", LEFT, 0);
    const int desired_rows = static_cast<int>(files.size());
    const int rows = std::min(22, desired_rows);
    int skip = 0;
    if (rows < desired_rows) {
        skip = std::clamp(current_index - rows / 2, 0, desired_rows - rows);
        wattron(win, A_REVERSE);
        if (skip == 0) {
            mvwaddch(win, 1, 78, ' ');
        }
        else if (skip + rows == desired_rows) {
            mvwaddch(win, rows, 78, ' ');
        }
        else {
            const auto scroll_pos = static_cast<int>(static_cast<float>(skip) * static_cast<float>(rows) / static_cast<float>(desired_rows - rows)) + 1;
            mvwaddch(win, scroll_pos, 78, ' ');
        }
        wattroff(win, A_REVERSE);
    }
    int index = skip;
    for (const auto &file: files | std::ranges::views::drop(skip) | std::ranges::views::take(rows)) {
        if (current_index == index) {
            wattron(win, A_STANDOUT);
        }
        if (is_directory(file)) {
            LeftAlign(win, std::format("[{}]", file.filename().string()), LEFT, 1 + index - skip);
        }
        else {
            LeftAlign(win, file.filename().string(), LEFT, 1 + index - skip);
        }
        wattroff(win, A_STANDOUT);
        index++;
    }
    if (has_error) {
        if (!popup) {
            popup = subwin(win, 4, 46, 10, 17);
        }
        wclear(popup);
        box(popup, 0, 0);
        LeftAlign(popup, "Error:", LEFT, 0);
        LeftAlign(popup, "There was an error loading the save file.", LEFT, 1);
        wattron(popup, A_STANDOUT);
        CenterAlign(popup, "OK", 22, 2);
        wattroff(popup, A_STANDOUT);
        wnoutrefresh(popup);
    }
}

void LoadScreen::HandleKey(const int key) {
    if (key == 27) {
        if (has_error) {
            has_error = false;
            ClearPopup();
        }
        else {
            message_handler("cancel");
        }
    }
    else if (key == '\n') {
        if (has_error) {
            has_error = false;
            ClearPopup();
        }
        else {
            const auto &file = files[current_index];
            if (is_directory(file)) {
                ChangeDir(file);
            }
            else {
                if (game->LoadGame(absolute(file).string()) == file::LoadErrorNone) {
                    message_handler("load");
                }
                else {
                    has_error = true;
                }
            }
        }
    }
    else if (key == KEY_UP) {
        current_index = std::max(0, current_index - 1);
    }
    else if (key == KEY_DOWN) {
        current_index = std::min(static_cast<int>(files.size()) - 1, current_index + 1);
    }
}


