//
// Created by nbollom on 5/01/25.
//

#pragma once

//
// Created by nbollom on 4/01/25.
//

#pragma once
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/text.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/grid.h>
#include "gtkview.hpp"

class CharacterCreator final : public GTKView {

    bool closed = false;

    std::shared_ptr<NewGame> new_game;

    Gtk::ScrolledWindow scrolled_window;

    Gtk::Box vbox;
    Gtk::Box hbox;
    Gtk::Box name_box;
    Gtk::Label name_label;
    Gtk::Text name_text;
    Gtk::Button name_random_button;
    Gtk::Frame race_frame;
    Gtk::Box race_box;
    std::vector<Gtk::CheckButton*> race_options;
    Gtk::Frame class_frame;
    Gtk::Box class_box;
    std::vector<Gtk::CheckButton*> class_options;
    Gtk::Frame stats_frame;
    Gtk::Grid stats_grid;
    Gtk::Label str_label;
    Gtk::Text str_text;
    Gtk::Label con_label;
    Gtk::Text con_text;
    Gtk::Label dex_label;
    Gtk::Text dex_text;
    Gtk::Label int_label;
    Gtk::Text int_text;
    Gtk::Label wis_label;
    Gtk::Text wis_text;
    Gtk::Label cha_label;
    Gtk::Text cha_text;
    Gtk::Label total_label;
    Gtk::Text total_text;
    Gtk::Button roll_button;
    Gtk::Button unroll_button;
    Gtk::Button sold_button;

public:
    CharacterCreator(const std::shared_ptr<Game> &game, const MessageHandler &message_handler);
    ~CharacterCreator() override;

    void Show() override;
    void Hide() override;
    void Close() override;

    void UpdateStats();

};
