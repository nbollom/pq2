//
// Created by nbollom on 9/10/18.
//

#pragma once

#include <memory>
#include <functional>
#include "game.hpp"

typedef std::function<void(std::string)> MessageHandler;

class View {

protected:
    std::shared_ptr<Game> game;
    MessageHandler message_handler;

public:
    View(const std::shared_ptr<Game> &game, const MessageHandler &message_handler);
    virtual ~View() = default;

    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Close() = 0;
};
