//
// Created by nbollom on 30/05/16.
//

#pragma once

#include <memory>
#include <stack>
#include "game.hpp"
#include "view.hpp"

class GUI {

protected:
    std::shared_ptr<Game> game;
    std::stack<std::shared_ptr<View>> view_stack;

    explicit GUI(std::shared_ptr<Game> game_ptr); //cannot directly instantiate base class

public:
    virtual void Run();
    virtual ~GUI();

    void PushView(const std::shared_ptr<View>& view);
    void PopView();
    void PopAllViews();

    virtual void ShowMainMenu() = 0;
    virtual void ShowCharacterCreator() = 0;
    virtual void ShowGameScreen() = 0;
    virtual void Close() = 0;

};
