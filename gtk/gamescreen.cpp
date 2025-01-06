//
// Created by nbollom on 6/01/25.
//

#include <format>
#include <utils.hpp>
#include <gtkmm.h>
#include "gamescreen.hpp"

#define TIMER_MS 100
#define TEN_SECONDS 10000

GameScreen::GameScreen(const std::shared_ptr<Game> &game, const MessageHandler &message_handler) : GTKView(game, message_handler) {
    set_title(std::format("Progress Quest 2 - {}", game->GetCharacter().Name));
    set_default_size(800, 600);
    signal_close_request().connect([&]() {
        Close();
        return true;
    }, true);

    const auto &character = game->GetCharacter();

    vbox.set_orientation(Gtk::Orientation::VERTICAL);
    vbox.set_spacing(10);
    vbox.set_margin(10);

    hbox.set_orientation(Gtk::Orientation::HORIZONTAL);
    hbox.set_spacing(10);
    hbox.set_homogeneous(true);

    col1_box.set_orientation(Gtk::Orientation::VERTICAL);
    col1_box.set_spacing(10);
    col1_box.set_homogeneous(false);

    character_frame.set_label("Character Sheet");

    character_box.set_orientation(Gtk::Orientation::VERTICAL);
    character_box.set_spacing(10);

    character_grid.set_column_homogeneous(true);
    character_grid.set_row_homogeneous(false);
    character_grid.add_css_class("table");

    SetLabelProperties(character_trait_header_label, "Trait", {"header", "top"});
    character_grid.attach(character_trait_header_label, 0, 0);

    SetLabelProperties(character_value_header_label, "Value", {"header", "top", "last"});
    character_grid.attach(character_value_header_label, 1, 0);

    SetLabelProperties(character_name_label, "Name", {"body"});
    character_grid.attach(character_name_label, 0, 1);

    SetLabelProperties(character_name_value_label, character.Name, {"body", "last"});
    character_grid.attach(character_name_value_label, 1, 1);

    SetLabelProperties(character_race_label, "Race", {"body"});
    character_grid.attach(character_race_label, 0, 2);

    SetLabelProperties(character_race_value_label, character.CharacterRace.name, {"body", "last"});
    character_grid.attach(character_race_value_label, 1, 2);

    SetLabelProperties(character_class_label, "Class", {"body"});
    character_grid.attach(character_class_label, 0, 3);

    SetLabelProperties(character_class_value_label, character.CharacterClass.name, {"body", "last"});
    character_grid.attach(character_class_value_label, 1, 3);

    SetLabelProperties(character_level_label, "Level", {"body"});
    character_grid.attach(character_level_label, 0, 4);

    SetLabelProperties(character_level_value_label, "", {"body", "last"});
    character_grid.attach(character_level_value_label, 1, 4);

    character_box.append(character_grid);

    stats_grid.set_column_homogeneous(true);
    stats_grid.set_row_homogeneous(false);
    stats_grid.add_css_class("table");

    SetLabelProperties(stats_stat_header_label, "Stat", {"header", "top"});
    stats_grid.attach(stats_stat_header_label, 0, 0);

    SetLabelProperties(stats_value_header_label, "Value", {"header", "top", "last"});
    stats_grid.attach(stats_value_header_label, 1, 0);

    SetLabelProperties(stats_str_label, "STR", {"body"});
    stats_grid.attach(stats_str_label, 0, 1);

    SetLabelProperties(stats_str_value_label, "", {"body", "last"});
    stats_grid.attach(stats_str_value_label, 1, 1);

    SetLabelProperties(stats_con_label, "CON", {"body"});
    stats_grid.attach(stats_con_label, 0, 2);

    SetLabelProperties(stats_con_value_label, "", {"body", "last"});
    stats_grid.attach(stats_con_value_label, 1, 2);

    SetLabelProperties(stats_dex_label, "DEX", {"body"});
    stats_grid.attach(stats_dex_label, 0, 3);

    SetLabelProperties(stats_dex_value_label, "", {"body", "last"});
    stats_grid.attach(stats_dex_value_label, 1, 3);

    SetLabelProperties(stats_int_label, "INT", {"body"});
    stats_grid.attach(stats_int_label, 0, 4);

    SetLabelProperties(stats_int_value_label, "", {"body", "last"});
    stats_grid.attach(stats_int_value_label, 1, 4);

    SetLabelProperties(stats_wis_label, "WIS", {"body"});
    stats_grid.attach(stats_wis_label, 0, 5);

    SetLabelProperties(stats_wis_value_label, "", {"body", "last"});
    stats_grid.attach(stats_wis_value_label, 1, 5);

    SetLabelProperties(stats_cha_label, "CHA", {"body"});
    stats_grid.attach(stats_cha_label, 0, 6);

    SetLabelProperties(stats_cha_value_label, "", {"body", "last"});
    stats_grid.attach(stats_cha_value_label, 1, 6);

    SetLabelProperties(stats_hp_label, "HP Max", {"body"});
    stats_grid.attach(stats_hp_label, 0, 7);

    SetLabelProperties(stats_hp_value_label, "", {"body", "last"});
    stats_grid.attach(stats_hp_value_label, 1, 7);

    SetLabelProperties(stats_mp_label, "MP Max", {"Body"});
    stats_grid.attach(stats_mp_label, 0, 8);

    SetLabelProperties(stats_mp_value_label, "", {"body", "last"});
    stats_grid.attach(stats_mp_value_label, 1, 8);

    character_box.append(stats_grid);

    experience_label.set_label("Experience");
    experience_label.set_halign(Gtk::Align::START);
    character_box.append(experience_label);

    character_box.append(experience_progressbar);

    character_frame.set_child(character_box);

    col1_box.append(character_frame);

    spells_frame.set_label("Spells");

    spells_scrolled_window.set_expand(true);

    spells_grid.set_column_homogeneous(true);
    spells_grid.set_row_homogeneous(false);
    spells_grid.add_css_class("table");

    SetLabelProperties(spells_spell_header_label, "Spell", {"header", "top"});
    spells_grid.attach(spells_spell_header_label, 0, 0);

    SetLabelProperties(spells_spell_level_label, "Level", {"header", "top", "last"});
    spells_grid.attach(spells_spell_level_label, 1, 0);

    spells_frame.set_child(spells_scrolled_window);

    spells_scrolled_window.set_child(spells_grid);

    col1_box.append(spells_frame);

    hbox.append(col1_box);

    col2_box.set_orientation(Gtk::Orientation::VERTICAL);
    col2_box.set_spacing(10);
    col2_box.set_homogeneous(false);

    equipment_frame.set_label("Equipment");

    equipment_grid.set_column_homogeneous(true);
    equipment_grid.set_row_homogeneous(false);
    equipment_grid.add_css_class("table");

    equipment_types.resize(11);
    equipment_values.resize(11);

    equipment_types[0].add_css_class("top");
    equipment_values[0].add_css_class("top");

    for (size_t i = 0; i < 11; i++) {
        SetLabelProperties(equipment_types[i], data::EquipmentLabels[i], {"body"});
        equipment_grid.attach(equipment_types[i], 0, static_cast<int>(i));
        SetLabelProperties(equipment_values[i], "", {"body", "last"});
        equipment_grid.attach(equipment_values[i], 1, static_cast<int>(i));
    }

    equipment_frame.set_child(equipment_grid);

    col2_box.append(equipment_frame);

    inventory_frame.set_label("Inventory");

    inventory_box.set_orientation(Gtk::Orientation::VERTICAL);
    inventory_box.set_spacing(10);

    inventory_scrolled_window.set_expand(true);

    inventory_grid.set_column_homogeneous(true);
    inventory_grid.set_row_homogeneous(false);
    inventory_grid.add_css_class("table");

    SetLabelProperties(inventory_item_header_label, "Item", {"header", "top"});
    inventory_grid.attach(inventory_item_header_label, 0, 0);

    SetLabelProperties(inventory_qty_header_label, "Qty", {"header", "top", "last"});
    inventory_grid.attach(inventory_qty_header_label, 1, 0);

    SetLabelProperties(inventory_gold_label, "Gold", {"body"});
    inventory_grid.attach(inventory_gold_label, 0, 1);

    SetLabelProperties(inventory_gold_value_label, "", {"body", "last"});
    inventory_grid.attach(inventory_gold_value_label, 1, 1);

    inventory_scrolled_window.set_child(inventory_grid);

    inventory_box.append(inventory_scrolled_window);

    encumbrance_label.set_label("Encumbrance");
    encumbrance_label.set_halign(Gtk::Align::START);

    inventory_box.append(encumbrance_label);

    inventory_box.append(encumbrance_progressbar);

    inventory_frame.set_child(inventory_box);

    col2_box.append(inventory_frame);

    hbox.append(col2_box);

    col3_box.set_orientation(Gtk::Orientation::VERTICAL);
    col3_box.set_spacing(10);
    col3_box.set_homogeneous(true);

    plot_frame.set_label("Plot Development");

    plot_box.set_orientation(Gtk::Orientation::VERTICAL);

    plot_table.set_orientation(Gtk::Orientation::VERTICAL);
    plot_table.add_css_class("table");
    plot_table.set_vexpand(true);

    plot_scrolled_window.set_child(plot_table);

    plot_box.append(plot_scrolled_window);
    plot_box.append(plot_progress);

    plot_frame.set_child(plot_box);

    col3_box.append(plot_frame);

    quest_frame.set_label("Quests");

    quest_box.set_orientation(Gtk::Orientation::VERTICAL);

    quest_table.set_orientation(Gtk::Orientation::VERTICAL);
    quest_table.add_css_class("table");
    quest_table.set_vexpand(true);

    quest_scrolled_window.set_child(quest_table);

    quest_box.append(quest_scrolled_window);
    quest_box.append(quest_progress);

    quest_frame.set_child(quest_box);

    col3_box.append(quest_frame);

    hbox.append(col3_box);

    vbox.append(hbox);

    status_label.set_halign(Gtk::Align::START);

    vbox.append(status_label);
    vbox.append(status_progressbar);

    scrolled_window.set_child(vbox);

    set_child(scrolled_window);

    UpdateStats();
    UpdateSpells();
    UpdateEquipment();
    UpdateInventory();
    UpdatePlot();
    UpdateQuests();
    UpdateStatus();

    last_update = std::chrono::system_clock::now();
    Glib::signal_timeout().connect([&]() {
        UpdateAll();
        return true;
    }, TIMER_MS);
}

constexpr void GameScreen::SetLabelProperties(Gtk::Label &label, const std::string &text, const std::vector<std::string>& css_classes) {
    if (!text.empty()) {
        label.set_label(text);
    }
    for (const auto &css_class : css_classes) {
        label.add_css_class(css_class);
    }
    label.set_size_request(100, 10);
    label.set_overflow(Gtk::Overflow::HIDDEN);
    label.set_xalign(0);
}


void GameScreen::UpdateStats() {
    const auto &character = game->GetCharacter();
    character_level_value_label.set_label(std::to_string(character.Level));
    stats_str_value_label.set_label(std::to_string(character.STR));
    stats_con_value_label.set_label(std::to_string(character.CON));
    stats_dex_value_label.set_label(std::to_string(character.DEX));
    stats_int_value_label.set_label(std::to_string(character.INT));
    stats_wis_value_label.set_label(std::to_string(character.WIS));
    stats_cha_value_label.set_label(std::to_string(character.CHA));
    stats_hp_value_label.set_label(std::to_string(character.MAX_HP));
    stats_mp_value_label.set_label(std::to_string(character.MAX_MP));

    const uint64_t max = game->GetLevelUpMaxValue();
    experience_progressbar.set_fraction(static_cast<double>(character.Experience) / static_cast<double>(max));
    const uint64_t needed = max - character.Experience;
    const std::string needed_exp = std::to_string(needed) + " XP needed for next level";
    experience_progressbar.set_tooltip_text(needed_exp);
}

void GameScreen::UpdateSpells() {
    const auto &character = game->GetCharacter();
    if (spells_names.size() != character.Spells.size()) {
        const auto start = spells_names.size();
        spells_names.resize(character.Spells.size());
        spells_levels.resize(character.Spells.size());
        for (auto i = start; i < character.Spells.size(); i++) {
            SetLabelProperties(spells_names[i], "", {"body"});
            spells_grid.attach(spells_names[i], 0, static_cast<int>(i) + 1);
            SetLabelProperties(spells_levels[i], "", {"body", "last"});
            spells_grid.attach(spells_levels[i], 1, static_cast<int>(i) + 1);
        }
    }
    for (size_t i = 0; i < character.Spells.size(); i++) {
        const auto &[name, level] = character.Spells[i];
        spells_names[i].set_label(name);
        spells_levels[i].set_label(GetRomanNumerals(level));
    }
}

void GameScreen::UpdateEquipment() {
    const auto &character = game->GetCharacter();
    for (size_t i = 0; i < 11; i++) {
        equipment_values[i].set_label(character.Equipment[i]);
    }
}

void GameScreen::UpdateInventory() {
    const auto &character = game->GetCharacter();
    while (inventory_item_names.size() > character.Inventory.size()) {
        // need to remove extra items from the grid
        auto &name_label = inventory_item_names.back();
        inventory_grid.remove(name_label);
        inventory_item_names.pop_back();
        auto &qty_label = inventory_item_qty.back();
        inventory_grid.remove(qty_label);
        inventory_item_qty.pop_back();
    }
    while (inventory_item_names.size() < character.Inventory.size()) {
        // need to add more items
        const int pos = static_cast<int>(inventory_item_names.size());
        auto &name_label = inventory_item_names.emplace_back();
        SetLabelProperties(name_label, "", {"body"});
        inventory_grid.attach(name_label, 0, pos + 2);

        auto &qty_label = inventory_item_qty.emplace_back();
        SetLabelProperties(qty_label, "", {"body", "last"});
        inventory_grid.attach(qty_label, 1, pos + 2);
    }

    inventory_gold_value_label.set_label(std::to_string(character.Gold));

    for (size_t i = 0; i < character.Inventory.size(); i++) {
        const auto &[name, qty] = character.Inventory[i];
        inventory_item_names[i].set_label(name);
        inventory_item_qty[i].set_label(std::to_string(qty));
    }

    const uint64_t max = game->GetEncumbranceMaxValue();
    const uint64_t value = game->GetEncumbrance();
    encumbrance_progressbar.set_fraction(static_cast<double>(value) / static_cast<double>(max));
    encumbrance_progressbar.set_tooltip_text(std::to_string(max - value) + " cubits");
}

void GameScreen::UpdatePlot() {
    const auto &character = game->GetCharacter();
    while (plot_items.size() < character.Plot.size()) {
        auto &checkbox = plot_items.emplace_back();
        if (&checkbox == &plot_items.front()) {
            checkbox.add_css_class("top");
        }
        checkbox.add_css_class("body");
        checkbox.add_css_class("last");
        checkbox.set_sensitive(false);
        plot_table.append(checkbox);
    }
    for (size_t i = 0; i < character.Plot.size(); i++) {
        auto &checkbox = plot_items[i];
        checkbox.set_label(character.Plot[i]);
        if (character.Plot[i] != character.Plot.back()) {
            checkbox.set_active(true);
        }
    }
    plot_progress.set_fraction(static_cast<double>(character.CurrentPlotProgress) / static_cast<double>(game->GetPlotMaxValue()));
}

void GameScreen::UpdateQuests() {
    const auto &character = game->GetCharacter();
    while (quest_items.size() < character.Quests.size()) {
        auto &checkbox = quest_items.emplace_back();
        if (&checkbox == &quest_items.front()) {
            checkbox.add_css_class("top");
        }
        checkbox.add_css_class("body");
        checkbox.add_css_class("last");
        checkbox.set_sensitive(false);
        quest_table.append(checkbox);
    }
    for (size_t i = 0; i < character.Quests.size(); i++) {
        auto &checkbox = quest_items[i];
        checkbox.set_label(character.Quests[i].label);
        if (&character.Quests[i] != &character.Quests.back()) {
            checkbox.set_active(true);
        }
    }
    quest_progress.set_fraction(static_cast<double>(character.CurrentQuestProgress) / static_cast<double>(character.MaxQuestProgress));
}

void GameScreen::UpdateStatus() {
    const auto character = game->GetCharacter();
    status_label.set_label(character.CurrentActionLabel);
    status_progressbar.set_fraction(static_cast<double>(character.CurrentProgress) / static_cast<double>(character.MaxProgress));
}

void GameScreen::UpdateAll() {
    const std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time - last_update).count();
    if (elapsed > TEN_SECONDS) {
        // if 10 seconds have passed since last update, the system was either sleeping or badly locked up
        // regardless we should consider that time as dead to avoid cheating by "sleep progressing"
        elapsed = TIMER_MS;
    }
    last_update = time;
    game->Tick(elapsed);
    UpdateStats();
    UpdateSpells();
    UpdateEquipment();
    UpdateInventory();
    UpdatePlot();
    UpdateQuests();
    UpdateStatus();
}

void GameScreen::Show() {
    set_visible(true);
}

void GameScreen::Hide() {
    set_visible(false);
}

void GameScreen::Close() {
    if (!closed) {
        message_handler("quit");
        closed = true;
    }
}
