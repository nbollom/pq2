//
// Created by nbollom on 20/12/24.
//

#include "charactercreator.h"

#define CONTROLS 3

CharacterCreator::CharacterCreator(const std::shared_ptr<Game> &game, const MessageHandler& message_handler)  : NCursesView(game, message_handler) {
    new_game = game->StartNewGame();
    races = new_game->GetAvailableRaces();
    classes = new_game->GetAvailableClasses();
}

void CharacterCreator::Resize(const int new_screen_width, const int new_screen_height) {
    NCursesView::Resize(new_screen_width, new_screen_height);
    delwin(win);
    win = newwin(0, 0, 0, 0);
    keypad(win, true);
    nodelay(win, true);
    wtimeout(win, 100);
}

void CharacterCreator::Render() {
    wclear(win);
    box(win, 0, 0);
    LeftAlign(win, "Progress Quest 2", 2, 0);
    LeftAlign(win, "Name:", 2, 2);
    if (selected_control == 0) {
        wattron(win, A_UNDERLINE);
    }
    LeftAlign(win, new_game->GetName(), 9, 2);
    wattroff(win, A_UNDERLINE);
    if (selected_control == 1) {
        wattron(win, A_UNDERLINE);
    }
    LeftAlign(win, "?", 40, 2);
    wattroff(win, A_UNDERLINE);
    LeftAlign(win, "Race:", 2, 3);
    if (selected_control == 2) {
        wattron(win, A_UNDERLINE);
    }
    LeftAlign(win, new_game->GetRace(), 9, 3);
    wattroff(win, A_UNDERLINE);
    LeftAlign(win, "Class:", 2, 4);
    if (selected_control == 3) {
        wattron(win, A_UNDERLINE);
    }
    LeftAlign(win, new_game->GetClass(), 9, 4);
    wattroff(win, A_UNDERLINE);
    if (show_race_popup) {
        const int desired_rows = static_cast<int>(races.size());
        const int rows = std::min(screen_height - 4, desired_rows);
        int skip = 0;
        int skip_tail = 0;
        WINDOW *w = subwin(win, rows + 2, 30, 1, 4);
        wclear(w);
        box(w, 0, 0);
        LeftAlign(w, "Race:", 2, 0);
        int index = 0;
        if (rows < desired_rows) {
            skip = std::min(std::max(race_index - rows / 2, 0), desired_rows - rows);
            skip_tail = skip + rows;
            wattron(w, A_REVERSE);
            if (skip == 0) {
                mvwaddch(w, 1, 28, ' ');
            }
            else if (skip_tail == desired_rows) {
                mvwaddch(w, rows, 28, ' ');
            }
            else {
                const auto scroll_pos = static_cast<int>(skip * static_cast<float>(rows) / static_cast<float>(desired_rows - rows)) + 1;
                mvwaddch(w, scroll_pos, 28, ' ');
            }
            wattroff(w, A_REVERSE);
        }
        for (const auto &race: races) {
            if (index >= skip_tail) {
                break;;
            }
            if (index >= skip) {
                if (race_index == index) {
                    wattron(w, A_UNDERLINE);
                }
                LeftAlign(w, race, 2, 1 + index - skip);
                wattroff(w, A_UNDERLINE);
            }
            index++;
        }
        wrefresh(w);
    }
    if (show_class_popup) {
        const int desired_rows = static_cast<int>(classes.size());
        const int rows = std::min(screen_height - 4, desired_rows);
        int skip = 0;
        int skip_tail = 0;
        WINDOW *w = subwin(win, rows + 2, 30, 1, 4);
        wclear(w);
        box(w, 0, 0);
        LeftAlign(w, "Class:", 2, 0);
        int index = 0;
        if (rows < desired_rows) {
            skip = std::min(std::max(class_index - rows / 2, 0), desired_rows - rows);
            skip_tail = skip + rows;
            wattron(w, A_REVERSE);
            if (skip == 0) {
                mvwaddch(w, 1, 28, ' ');
            }
            else if (skip_tail == desired_rows) {
                mvwaddch(w, rows, 28, ' ');
            }
            else {
                const auto scroll_pos = static_cast<int>(skip * static_cast<float>(rows) / static_cast<float>(desired_rows - rows)) + 1;
                mvwaddch(w, scroll_pos, 28, ' ');
            }
            wattroff(w, A_REVERSE);
        }
        for (const auto &cls: classes) {
            if (index >= skip_tail) {
                break;;
            }
            if (index >= skip) {
                if (class_index == index) {
                    wattron(w, A_UNDERLINE);
                }
                LeftAlign(w, cls, 2, 1 + index - skip);
                wattroff(w, A_UNDERLINE);
            }
            index++;
        }
        wrefresh(w);
    }
    wrefresh(win);
    const int ch = wgetch(win);
    if (ch != ERR) {
        if (ch == 27) {
            if (show_race_popup) {
                show_race_popup = false;
            }
            else if (show_class_popup) {
                show_class_popup = false;
            }
            else {
                message_handler("cancel");
            }
        }
        else if (ch == '\t') {
            if (show_race_popup) {
                race_index++;
                if (race_index == static_cast<int>(races.size())) {
                    race_index = 0;
                }
            }
            else if (show_class_popup) {
                class_index++;
                if (class_index == static_cast<int>(classes.size())) {
                    class_index = 0;
                }
            }
            else {
                selected_control++;
                if (selected_control > CONTROLS) {
                    selected_control = 0;
                }
            }
        }
        else if (ch == KEY_DOWN) {
            if (show_race_popup) {
                race_index = std::min(race_index + 1, static_cast<int>(races.size()) - 1);
            }
            else if (show_class_popup) {
                class_index = std::min(class_index + 1, static_cast<int>(classes.size()) - 1);
            }
            else {
                selected_control = std::min(selected_control + 1, CONTROLS);
                if (selected_control == 1) { // 2nd column controls go down to next row
                    selected_control++;
                }
            }
        }
        else if (ch == KEY_UP) {
            if (show_race_popup) {
                race_index = std::max(race_index - 1, 0);
            }
            else if (show_class_popup) {
                class_index = std::max(class_index - 1, 0);
            }
            else {
                selected_control = std::max(selected_control - 1, 0);
                if (selected_control == 1) { // skip 2nd column controls
                    selected_control--;
                }
            }
        }
        else if (ch == KEY_LEFT) {
            if (!show_race_popup && !show_class_popup && selected_control == 1) {
                selected_control--;
            }
        }
        else if (ch == KEY_RIGHT) {
            if (!show_race_popup && !show_class_popup && selected_control == 0) {
                selected_control++;
            }
        }
        else if (ch == '\n' || ch == ' ') {
            if (selected_control == 1) {
                new_game->GenerateName();
            }
            else if (selected_control == 2) {
                if (show_race_popup) {
                    const auto race = races[race_index];
                    new_game->SetRace(race);
                    show_race_popup = false;
                }
                else {
                    show_race_popup = true;
                    race_index = std::ranges::find(races, new_game->GetRace()) - races.begin();
                }
            }
            else if (selected_control == 3) {
                if (show_class_popup) {
                    const auto cls = classes[class_index];
                    new_game->SetClass(cls);
                    show_class_popup = false;
                }
                else {
                    show_class_popup = true;
                    class_index = std::ranges::find(classes, new_game->GetClass()) - classes.begin();
                }
            }
        }
        else if (ch == KEY_BACKSPACE) {
            if (selected_control == 0) {
                std::string name = new_game->GetName();
                if (name.length() > 0) {
                    name.pop_back();
                    new_game->SetName(name);
                }
            }
        }
        else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57)) {
            if (selected_control == 0) {
                std::string name = new_game->GetName();
                if (name.length() < 30) {
                    name += ch;
                }
                new_game->SetName(name);
            }
        }
    }
}

