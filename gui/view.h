//
// Created by nbollom on 9/10/18.
//

#ifndef PQ2_VIEW_H
#define PQ2_VIEW_H

#include <memory>
#include <functional>
#include "game.h"

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

#endif //PQ2_VIEW_H
