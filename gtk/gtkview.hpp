//
// Created by nbollom on 5/01/25.
//

#pragma once

#include <gtkmm/window.h>
#include "view.hpp"

class GTKView : public View, public Gtk::Window {

public:
    GTKView(const std::shared_ptr<Game> &game, const MessageHandler &message_handler);

    void Show() override;
    void Hide() override;
    void Close() override;

};