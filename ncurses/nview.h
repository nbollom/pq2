//
// Created by nbollom on 17/06/16.
//

#ifndef PQ2_NVIEW_H
#define PQ2_NVIEW_H

#include <memory>
#include <functional>
#include <string>
#include "game.h"

class NView {

protected:
    std::shared_ptr<Game> game;
    std::function<bool(std::string message, void *value)> message_handler;
    int screen_width;
    int screen_height;

    void LeftAlign(std::string value, int x, int y);
    void RightAlign(std::string value, int x, int y);
    void CenterAlign(std::string value, int x, int y);

public:
    NView(std::shared_ptr<Game> game_ptr, std::function<bool(std::string message, void *value)> message_handler_callback);
    virtual void Resize(int new_screen_width, int new_screen_height);
    virtual void HandleKeyPress(int key) = 0;
    virtual void Render() = 0;
    virtual void ViewDidAppear() {};
    virtual void ViewWillDissapear() {};
};

#endif //PQ2_NVIEW_H
