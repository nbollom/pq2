//
// Created by nbollom on 20/12/24.
//

#pragma once

#include <vector>
#include <string>
#include "ncursesview.hpp"

class CharacterCreator final : public NCursesView {
    WINDOW *win = nullptr;
    int selected_control = 0;
    bool show_race_popup = false;
    std::vector<std::string> races;
    int race_index = 0;
    bool show_class_popup = false;
    int class_index = 0;
    std::vector<std::string> classes;

    std::shared_ptr<NewGame> new_game;

    void ShowPopup(const std::string &label, const std::vector<std::string> &items, int current_index) const;

public:
    CharacterCreator(const std::shared_ptr<Game>& game, const MessageHandler& message_handler);
    void Resize(int new_screen_width, int new_screen_height) override;
    void Render() override;

};