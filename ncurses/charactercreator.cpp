//
// Created by nbollom on 20/12/24.
//

#include "charactercreator.hpp"
#include <ranges>

#define CONTROLS 6
#define LEFT 2
#define COLUMN_2 16
#define COLUMN_3 48

using namespace ui;

CharacterCreator::CharacterCreator(const std::shared_ptr<Game> &game, const MessageHandler& message_handler)  : NCursesView(game, message_handler) {
    new_game = game->StartNewGame();
    races = NewGame::GetAvailableRaces();
    classes = NewGame::GetAvailableClasses();
}

void CharacterCreator::ShowPopup(const std::string &label, const std::vector<std::string> &items, const int current_index) const {
    const int desired_rows = static_cast<int>(items.size());
    const int rows = std::min(24 - 4, desired_rows);
    int skip = 0;
    WINDOW *w = subwin(win, rows + 2, 30, 1, 4);
    wclear(w);
    box(w, 0, 0);
    LeftAlign(w, label, 2, 0);
    if (rows < desired_rows) {
        skip = std::clamp(current_index - rows / 2, 0, desired_rows - rows);
        wattron(w, A_REVERSE);
        if (skip == 0) {
            mvwaddch(w, 1, 28, ' ');
        }
        else if (skip + rows == desired_rows) {
            mvwaddch(w, rows, 28, ' ');
        }
        else {
            const auto scroll_pos = static_cast<int>(static_cast<float>(skip) * static_cast<float>(rows) / static_cast<float>(desired_rows - rows)) + 1;
            mvwaddch(w, scroll_pos, 28, ' ');
        }
        wattroff(w, A_REVERSE);
    }
    int index = skip;
    for (const auto &item: items | std::ranges::views::drop(skip) | std::ranges::views::take(rows)) {
        if (current_index == index) {
            wattron(w, A_STANDOUT);
        }
        LeftAlign(w, item, 2, 1 + index - skip);
        wattroff(w, A_STANDOUT);
        index++;
    }
    wrefresh(w);
}


void CharacterCreator::Resize(const int new_screen_width, const int new_screen_height) {
    NCursesView::Resize(new_screen_width, new_screen_height);
    delwin(win);
    constexpr int required_width = 80;
    constexpr int required_height = 24;
    win = newwin(required_height, required_width, 0, 0);
    keypad(win, true);
    nodelay(win, true);
    wtimeout(win, 100);
}

void CharacterCreator::Render() {
    wclear(win);
    box(win, 0, 0);
    LeftAlign(win, "Progress Quest 2", LEFT, 0);
    LeftAlign(win, "Name:", LEFT, 2);
    if (selected_control == 0) {
        wattron(win, A_UNDERLINE);
    }
    const auto name = new_game->GetName();
    LeftAlign(win, name, COLUMN_2, 2);
    wattroff(win, A_UNDERLINE);
    if (selected_control == 0) {
        wattron(win, A_REVERSE);
        mvwaddch(win, 2, COLUMN_2 + name.size(), ' ');
        wattroff(win, A_REVERSE);
    }
    if (selected_control == 1) {
        wattron(win, A_STANDOUT);
    }
    RightAlign(win, "Random", COLUMN_3, 2);
    wattroff(win, A_STANDOUT);
    LeftAlign(win, "Race:", LEFT, 3);
    if (selected_control == 2) {
        wattron(win, A_STANDOUT);
    }
    LeftAlign(win, new_game->GetRace(), COLUMN_2, 3);
    wattroff(win, A_STANDOUT);
    LeftAlign(win, "Class:", LEFT, 4);
    if (selected_control == 3) {
        wattron(win, A_STANDOUT);
    }
    LeftAlign(win, new_game->GetClass(), COLUMN_2, 4);
    wattroff(win, A_STANDOUT);
    LeftAlign(win, "Stats:", LEFT, 6);
    LeftAlign(win, "STR:", LEFT, 7);
    LeftAlign(win, std::to_string(new_game->GetSTR()), COLUMN_2, 7);
    LeftAlign(win, "CON:", LEFT, 8);
    LeftAlign(win, std::to_string(new_game->GetCON()), COLUMN_2, 8);
    LeftAlign(win, "DEX:", LEFT, 9);
    LeftAlign(win, std::to_string(new_game->GetDEX()), COLUMN_2, 9);
    LeftAlign(win, "INT:", LEFT, 10);
    LeftAlign(win, std::to_string(new_game->GetINT()), COLUMN_2, 10);
    LeftAlign(win, "WIS:", LEFT, 11);
    LeftAlign(win, std::to_string(new_game->GetWIS()), COLUMN_2, 11);
    LeftAlign(win, "CHA:", LEFT, 12);
    LeftAlign(win, std::to_string(new_game->GetCHA()), COLUMN_2, 12);
    LeftAlign(win, std::string(COLUMN_2 + 6, '-'), LEFT, 13);
    LeftAlign(win, "TOTAL:", LEFT, 14);
    LeftAlign(win, std::to_string(new_game->GetTotal()), COLUMN_2, 14);
    const auto colour = new_game->GetTotalColor();
    if (colour == ColorRed) {
        LeftAlign(win, "++", COLUMN_2 + 3, 14);
    }
    else if (colour == ColorYellow) {
        LeftAlign(win, "+", COLUMN_2 + 3, 14);
    }
    else if (colour == ColorSilver) {
        RightAlign(win, "-", COLUMN_2 - 1, 14);
    }
    else if (colour == ColorGray) {
        RightAlign(win, "--", COLUMN_2 - 1, 14);
    }
    if (selected_control == 4) {
        wattron(win, A_STANDOUT);
    }
    LeftAlign(win, "Roll", LEFT, 16);
    wattroff(win, A_STANDOUT);
    if (selected_control == 5) {
        wattron(win, A_STANDOUT);
    }
    LeftAlign(win, "Unroll", COLUMN_2, 16);
    wattroff(win, A_STANDOUT);
    if (selected_control == 6) {
        wattron(win, A_STANDOUT);
    }
    LeftAlign(win, "Sold!", LEFT, 22);
    wattroff(win, A_STANDOUT);
    if (show_race_popup) {
        ShowPopup("Race:", races, race_index);
    }
    if (show_class_popup) {
        ShowPopup("Class:", classes, class_index);
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
                if (selected_control == 1 || selected_control == 5) { // 2nd column controls go down to next row
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
                if (selected_control == 1 || selected_control == 5) { // skip 2nd column controls
                    selected_control--;
                }
            }
        }
        else if (ch == KEY_LEFT) {
            if (!show_race_popup && !show_class_popup && (selected_control == 1 || selected_control == 5)) {
                selected_control--;
            }
        }
        else if (ch == KEY_RIGHT) {
            if (!show_race_popup && !show_class_popup && (selected_control == 0 || selected_control == 4)) {
                selected_control++;
            }
        }
        else if (ch == '\n' || ch == ' ') {
            if (show_race_popup) {
                const auto race = races[race_index];
                new_game->SetRace(race);
                show_race_popup = false;
            }
            else if (show_class_popup) {
                const auto cls = classes[class_index];
                new_game->SetClass(cls);
                show_class_popup = false;
            }
            else if (selected_control == 1) {
                new_game->GenerateName();
            }
            else if (selected_control == 2) {
                show_race_popup = true;
                race_index = static_cast<int>(std::ranges::find(races, new_game->GetRace()) - races.begin());
            }
            else if (selected_control == 3) {
                show_class_popup = true;
                class_index = static_cast<int>(std::ranges::find(classes, new_game->GetClass()) - classes.begin());
            }
            else if (selected_control == 4) {
                new_game->ReRoll();
            }
            else if (selected_control == 5) {
                if (new_game->CanUnroll()) {
                    new_game->UnRoll();
                }
            }
            else if (selected_control == 6) {
                new_game->ConfirmCharacter();
                message_handler("start");
            }
        }
        else if (ch == KEY_BACKSPACE) {
            if (selected_control == 0) {
                std::string name = new_game->GetName();
                if (!name.empty()) {
                    name.pop_back();
                    new_game->SetName(name);
                }
            }
        }
        else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57)) {
            if (selected_control == 0) {
                std::string name = new_game->GetName();
                if (name.length() < 30) {
                    name += static_cast<char>(ch);
                }
                new_game->SetName(name);
            }
        }
    }
}

