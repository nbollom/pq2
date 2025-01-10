//
// Created by nbollom on 29/12/24.
//

#pragma once

#include <chrono>
#include "ncursesview.hpp"

class GameScreen final : public NCursesView {

    std::chrono::time_point<std::chrono::system_clock> last_update;
    bool show_progress_labels = true;
    bool show_equipment = false;
    bool show_spells = false;
    bool show_inventory = false;
    bool show_plot = false;
    bool show_quests = false;

    int equipment_index = 0;
    int spell_index = 0;
    int inventory_index = 0;
    int plot_index = 0;
    int quest_index = 0;

    template<typename T>
    void ShowProgress(int line, T progress_current, T progress_max) const;

public:
    GameScreen(const std::shared_ptr<Game>& game, const MessageHandler& message_handler);
    void Render() override;
    void HandleKey(int key) override;

};