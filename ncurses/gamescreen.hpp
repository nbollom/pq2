//
// Created by nbollom on 29/12/24.
//

#pragma once

#include <chrono>
#include "ncursesview.hpp"

class GameScreen final : public NCursesView {

    std::chrono::time_point<std::chrono::system_clock> last_update;

    template<typename T>
    void ShowProgress(int line, T progress_current, T progress_max, const std::string& custom_label="") const;

public:
    GameScreen(const std::shared_ptr<Game>& game, const MessageHandler& message_handler);
    void Render() override;
    void HandleKey(int key) override;

};