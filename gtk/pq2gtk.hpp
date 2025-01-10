//
// Created by nbollom on 4/01/25.
//

#pragma once

#include <memory>
#include <string>
#include "pq2gui.hpp"
#include "game.hpp"

class GTKGUI final : public GUI {

private:
    MessageHandler message_handler;

    void HandleMessage(const std::string& message);

public:
    explicit GTKGUI(const std::shared_ptr<Game> &game);
    ~GTKGUI() override;
    void Run() override;

    void ShowMainMenu() override;
    void ShowCharacterCreator() override;
    void ShowGameScreen() override;
    void Close() override;

};
