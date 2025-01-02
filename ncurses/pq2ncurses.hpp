//
// Created by nbollom on 26/05/16.
//

#pragma once

#include <memory>
#include <string>
#include "pq2gui.hpp"
#include "game.hpp"

class NCursesGUI final : public GUI {

private:
    MessageHandler message_handler;
    int screen_width;
    int screen_height;

    void HandleMessage(const std::string& message);

public:
    explicit NCursesGUI(const std::shared_ptr<Game> &game);
    ~NCursesGUI() override;
    void Run() override;

    void ShowMainMenu() override;
    void ShowCharacterCreator() override;
    void ShowGameScreen() override;
    void ShowLoadScreen();
    void Close() override;

};
