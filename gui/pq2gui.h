//
// Created by nbollom on 30/05/16.
//

#ifndef PQ2_PQ2GUI_H
#define PQ2_PQ2GUI_H

#include <memory>
#include <stack>
#include "game.h"
#include "view.h"

class GUI {

private:

protected:
    std::shared_ptr<Game> game;
    std::stack<std::shared_ptr<View>> view_stack;

    GUI(std::shared_ptr<Game> game_ptr); //cannot directly instantiate base class

public:
    virtual void Run();
    virtual ~GUI();

    void PushView(std::shared_ptr<View> view);
    void PopView();
    void PopAllViews();

    virtual void ShowMainMenu() = 0;
    virtual void ShowCharacterCreator() = 0;
    virtual void ShowGameScreen() = 0;
    virtual void Close() = 0;

};

#endif //PQ2_PQ2GUI_H
