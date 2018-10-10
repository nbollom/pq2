//
// Created by nbollom on 9/10/18.
//

#ifndef PQ2_VIEW_H
#define PQ2_VIEW_H

#include <memory>
#include <functional>
#include "game.h"

class View {

protected:
    std::shared_ptr<Game> game;
    std::function<void(std::string, void*)> message_handler;

public:
    View(std::shared_ptr<Game> game, std::function<void(std::string, void*)> message_handler);
    ~View();

    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Close() = 0;
};

#endif //PQ2_VIEW_H
