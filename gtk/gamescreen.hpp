//
// Created by nbollom on 6/01/25.
//

#pragma once


//
// Created by nbollom on 5/01/25.
//

#pragma once

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/label.h>
#include <gtkmm/checkbutton.h>
#include <vector>
#include <chrono>
#include "gtkview.hpp"

class GameScreen final : public GTKView {

    bool closed = false;

    Gtk::ScrolledWindow scrolled_window;
    Gtk::Box vbox;
    Gtk::Box hbox;
    Gtk::Box col1_box;
    Gtk::Frame character_frame;
    Gtk::Box character_box;
    Gtk::Grid character_grid;
    Gtk::Label character_trait_header_label;
    Gtk::Label character_value_header_label;
    Gtk::Label character_name_label;
    Gtk::Label character_name_value_label;
    Gtk::Label character_race_label;
    Gtk::Label character_race_value_label;
    Gtk::Label character_class_label;
    Gtk::Label character_class_value_label;
    Gtk::Label character_level_label;
    Gtk::Label character_level_value_label;
    Gtk::Grid stats_grid;
    Gtk::Label stats_stat_header_label;
    Gtk::Label stats_value_header_label;
    Gtk::Label stats_str_label;
    Gtk::Label stats_str_value_label;
    Gtk::Label stats_con_label;
    Gtk::Label stats_con_value_label;
    Gtk::Label stats_dex_label;
    Gtk::Label stats_dex_value_label;
    Gtk::Label stats_int_label;
    Gtk::Label stats_int_value_label;
    Gtk::Label stats_wis_label;
    Gtk::Label stats_wis_value_label;
    Gtk::Label stats_cha_label;
    Gtk::Label stats_cha_value_label;
    Gtk::Label stats_hp_label;
    Gtk::Label stats_hp_value_label;
    Gtk::Label stats_mp_label;
    Gtk::Label stats_mp_value_label;
    Gtk::Label experience_label;
    Gtk::ProgressBar experience_progressbar;
    Gtk::Frame spells_frame;
    Gtk::ScrolledWindow spells_scrolled_window;
    Gtk::Grid spells_grid;
    Gtk::Label spells_spell_header_label;
    Gtk::Label spells_spell_level_label;
    std::vector<Gtk::Label> spells_names;
    std::vector<Gtk::Label> spells_levels;
    Gtk::Box col2_box;
    Gtk::Frame equipment_frame;
    Gtk::Grid equipment_grid;
    std::vector<Gtk::Label> equipment_types;
    std::vector<Gtk::Label> equipment_values;
    Gtk::Frame inventory_frame;
    Gtk::Box inventory_box;
    Gtk::ScrolledWindow inventory_scrolled_window;
    Gtk::Grid inventory_grid;
    Gtk::Label inventory_item_header_label;
    Gtk::Label inventory_qty_header_label;
    Gtk::Label inventory_gold_label;
    Gtk::Label inventory_gold_value_label;
    std::vector<Gtk::Label> inventory_item_names;
    std::vector<Gtk::Label> inventory_item_qty;
    Gtk::Label encumbrance_label;
    Gtk::ProgressBar encumbrance_progressbar;
    Gtk::Box col3_box;
    Gtk::Frame plot_frame;
    Gtk::Box plot_box;
    Gtk::ScrolledWindow plot_scrolled_window;
    Gtk::Box plot_table;
    std::vector<Gtk::CheckButton> plot_items;
    Gtk::ProgressBar plot_progress;
    Gtk::Frame quest_frame;
    Gtk::Box quest_box;
    Gtk::ScrolledWindow quest_scrolled_window;
    Gtk::Box quest_table;
    std::vector<Gtk::CheckButton> quest_items;
    Gtk::ProgressBar quest_progress;
    Gtk::Label status_label;
    Gtk::ProgressBar status_progressbar;

    std::chrono::time_point<std::chrono::system_clock> last_update;

    static constexpr void SetLabelProperties(Gtk::Label &label, const std::string &text, const std::vector<std::string>& css_classes);

public:
    GameScreen(const std::shared_ptr<Game> &game, const MessageHandler &message_handler);

    void UpdateStats();
    void UpdateSpells();
    void UpdateEquipment();
    void UpdateInventory();
    void UpdatePlot();
    void UpdateQuests();
    void UpdateStatus();
    void UpdateAll();

    void Show() override;
    void Hide() override;
    void Close() override;

};
