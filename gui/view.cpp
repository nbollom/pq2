//
// Created by nbollom on 9/10/18.
//

#include "view.h"

View::View(std::shared_ptr<Game> game, std::function<void(std::string, void*)> message_handler) {
    this->game = game;
    this->message_handler = message_handler;
}

View::~View() {

}
