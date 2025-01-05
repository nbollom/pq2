//
// Created by nbollom on 5/01/25.
//

#include "gtkview.hpp"


GTKView::GTKView(const std::shared_ptr<Game> &game, const MessageHandler &message_handler) : View(game, message_handler) {

}

void GTKView::Show() {
    set_visible(true);
}

void GTKView::Hide() {
    set_visible(false);
}

void GTKView::Close() {

}
