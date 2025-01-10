//
// Created by nbollom on 30/05/16.
//

#include "pq2gui.hpp"

#include <utility>
#include "game.hpp"

using namespace std;
using namespace game;

GUI::GUI(shared_ptr<Game> game_ptr) {
    game = std::move(game_ptr);
}

GUI::~GUI() {
    PopAllViews();
}

void GUI::Run() {
    if (game->GetState() != GameStateReady) {
        ShowMainMenu();
    }
    else {
        ShowGameScreen();
    }
}

void GUI::PushView(const std::shared_ptr<View>& view) {
    if (!view_stack.empty()) {
        view_stack.top()->Hide();
    }
    view_stack.push(view);
}

void GUI::PopView() {
    const std::shared_ptr<View> view = view_stack.top();
    view_stack.pop();
    if (!view_stack.empty()) {
        view_stack.top()->Show();
    }
    view->Close();
}

void GUI::PopAllViews() {
    while (!view_stack.empty()) {
        PopView();
    }
}
