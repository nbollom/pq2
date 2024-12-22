//
// Created by nbollom on 5/10/18.
//

#pragma once

#include <pq2gui.hpp>
#include <memory>
#include <functional>

class QTGUI final : public GUI {

private:
    MessageHandler message_handler;

public:
    explicit QTGUI(const std::shared_ptr<Game> &game);
    ~QTGUI() override;
    void Run() override;

    void ShowMainMenu() override;
    void ShowCharacterCreator() override;
    void ShowGameScreen() override;
    void Close() override;
    void HandleMessage(const std::string& message);
};
