//
// Created by nbollom on 4/01/25.
//

#pragma once
#include <pq2gui.hpp>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/filedialog.h>
#include "gtkview.hpp"

class MainMenu final : public GTKView {

    bool closed = false;
    Gtk::Box box;
    Gtk::Image logo;
    Gtk::Button new_game;
    Gtk::Button load_game;
    Gtk::Button exit;
    Glib::RefPtr<Gtk::FileDialog> file_dialog;

public:
    MainMenu(const std::shared_ptr<Game> &game, const MessageHandler &message_handler);

    void Show() override;
    void Hide() override;
    void Close() override;

    void NewGame() const;
    void LoadGame() const;

};
