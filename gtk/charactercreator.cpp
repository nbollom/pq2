//
// Created by nbollom on 5/01/25.
//

#include "charactercreator.hpp"

CharacterCreator::CharacterCreator(const std::shared_ptr<Game> &game, const MessageHandler &message_handler) : GTKView(game, message_handler) {
    set_title("Progress Quest 2 - Create New Character");
    set_default_size(800, 600);
    signal_close_request().connect([&]() {
        Close();
        return true;
    }, true);

    new_game = game->StartNewGame();

    vbox.set_orientation(Gtk::Orientation::VERTICAL);
    vbox.set_spacing(10);
    vbox.set_margin(20);
    vbox.set_homogeneous(false);

    name_box.set_orientation(Gtk::Orientation::HORIZONTAL);
    name_box.set_spacing(10);
    name_box.set_homogeneous(false);

    name_label.set_text("Name");
    name_label.set_size_request(40, 10);
    name_text.set_text(new_game->GetName());
    name_text.set_name("name_text");
    name_text.set_size_request(200, 10);
    name_text.set_hexpand(true);
    name_random_button.set_label("?");
    name_random_button.set_size_request(100, 10);
    name_random_button.signal_clicked().connect([&]() {
        new_game->GenerateName();
        name_text.set_text(new_game->GetName());
    });

    name_box.append(name_label);
    name_box.append(name_text);
    name_box.append(name_random_button);

    hbox.set_orientation(Gtk::Orientation::HORIZONTAL);
    hbox.set_spacing(10);
    hbox.set_homogeneous(true);

    race_box.set_orientation(Gtk::Orientation::VERTICAL);
    race_box.set_spacing(10);

    const std::string selected_race = new_game->GetRace();
    Gtk::CheckButton *first_race = nullptr;
    for (auto &race_name: NewGame::GetAvailableRaces()) {
        auto race_option = new Gtk::CheckButton(race_name);
        if (first_race == nullptr) {
            first_race = race_option;
        }
        else {
            race_option->set_group(*first_race);
        }
        if (selected_race == race_name) {
            race_option->set_active(true);
        }
        race_options.push_back(race_option);
        race_box.append(*race_option);
    }

    race_frame.set_label("Race");
    race_frame.set_child(race_box);

    class_box.set_orientation(Gtk::Orientation::VERTICAL);
    class_box.set_spacing(10);

    const std::string selected_class = new_game->GetClass();
    Gtk::CheckButton *first_class = nullptr;
    for (auto &class_name: NewGame::GetAvailableClasses()) {
        auto class_option = new Gtk::CheckButton(class_name);
        if (first_class == nullptr) {
            first_class = class_option;
        }
        else {
            class_option->set_group(*first_class);
        }
        if (selected_class == class_name) {
            class_option->set_active(true);
        }
        class_options.push_back(class_option);
        class_box.append(*class_option);
    }

    class_frame.set_label("Class");
    class_frame.set_child(class_box);

    stats_frame.set_label("Stats");

    stats_grid.set_column_spacing(10);
    stats_grid.set_row_spacing(10);
    stats_grid.set_column_homogeneous(false);
    stats_grid.set_row_homogeneous(false);

    str_label.set_label("STR");
    str_label.set_size_request(30, 10);
    str_text.set_editable(false);
    str_text.set_size_request(100, 10);
    con_label.set_label("CON");
    con_label.set_size_request(30, 10);
    con_text.set_editable(false);
    con_text.set_size_request(100, 10);
    dex_label.set_label("DEX");
    dex_label.set_size_request(30, 10);
    dex_text.set_editable(false);
    dex_text.set_size_request(100, 10);
    int_label.set_label("INT");
    int_label.set_size_request(30, 10);
    int_text.set_editable(false);
    int_text.set_size_request(100, 10);
    wis_label.set_label("WIS");
    wis_label.set_size_request(30, 10);
    wis_text.set_editable(false);
    wis_text.set_size_request(100, 10);
    cha_label.set_label("CHA");
    cha_label.set_size_request(30, 10);
    cha_text.set_editable(false);
    cha_text.set_size_request(100, 10);
    total_label.set_label("Total");
    total_label.set_size_request(30, 10);
    total_text.set_editable(false);
    total_text.set_size_request(100, 10);

    roll_button.set_label("Roll");
    roll_button.set_size_request(100, 10);
    roll_button.set_hexpand(true);
    roll_button.signal_clicked().connect([&]() {
        new_game->ReRoll();
        UpdateStats();
    });

    unroll_button.set_label("Unroll");
    unroll_button.set_size_request(100, 10);
    unroll_button.set_hexpand(true);
    unroll_button.signal_clicked().connect([&]() {
        if (new_game->CanUnroll()) {
            new_game->UnRoll();
            UpdateStats();
        }
    });

    stats_grid.attach(str_label, 0, 0);
    stats_grid.attach(str_text, 1, 0);
    stats_grid.attach(con_label, 0, 1);
    stats_grid.attach(con_text, 1, 1);
    stats_grid.attach(dex_label, 0, 2);
    stats_grid.attach(dex_text, 1, 2);
    stats_grid.attach(int_label, 0, 3);
    stats_grid.attach(int_text, 1, 3);
    stats_grid.attach(wis_label, 0, 4);
    stats_grid.attach(wis_text, 1, 4);
    stats_grid.attach(cha_label, 0, 5);
    stats_grid.attach(cha_text, 1, 5);
    stats_grid.attach(total_label, 0, 7);
    stats_grid.attach(total_text, 1, 7);
    stats_grid.attach(roll_button, 0, 8, 2);
    stats_grid.attach(unroll_button, 0, 9, 2);

    stats_frame.set_child(stats_grid);

    hbox.append(race_frame);
    hbox.append(class_frame);
    hbox.append(stats_frame);

    sold_button.set_label("Sold!");
    sold_button.set_size_request(100, 10);
    sold_button.set_halign(Gtk::Align::END);
    sold_button.set_valign(Gtk::Align::END);
    sold_button.signal_clicked().connect([&]() {
        new_game->SetName(name_text.get_text());
        for (const auto &race_option : race_options) {
            if (race_option->get_active()) {
                new_game->SetRace(race_option->get_label());
                break;
            }
        }
        for (const auto &class_option : class_options) {
            if (class_option->get_active()) {
                new_game->SetClass(class_option->get_label());
                break;
            }
        }
        new_game->ConfirmCharacter();
        message_handler("start");
    });

    vbox.append(name_box);
    vbox.append(hbox);
    vbox.append(sold_button);

    scrolled_window.set_child(vbox);

    set_child(scrolled_window);

    UpdateStats();

    Show();
}

CharacterCreator::~CharacterCreator() {
    for (const auto &race_option: race_options) {
        delete race_option;
    }
    for (const auto &class_option: class_options) {
        delete class_option;
    }
}


void CharacterCreator::Show() {
    set_visible(true);
}

void CharacterCreator::Hide() {
    set_visible(false);
}

void CharacterCreator::Close() {
    if (!closed) {
        closed = true;
        message_handler("cancel");
    }
}

void CharacterCreator::UpdateStats() {
    str_text.set_text(std::to_string(new_game->GetSTR()));
    con_text.set_text(std::to_string(new_game->GetCON()));
    dex_text.set_text(std::to_string(new_game->GetDEX()));
    int_text.set_text(std::to_string(new_game->GetINT()));
    wis_text.set_text(std::to_string(new_game->GetWIS()));
    cha_text.set_text(std::to_string(new_game->GetCHA()));
    total_text.set_text(std::to_string(new_game->GetTotal()));
    for (const auto& css_class: total_text.get_css_classes()) {
        total_text.remove_css_class(css_class);
    }
    switch (new_game->GetTotalColor()) {
        case ui::ColorRed:
            total_text.add_css_class("red");
        break;
        case ui::ColorYellow:
            total_text.add_css_class("yellow");
        break;
        case ui::ColorGray:
            total_text.add_css_class("gray");
        break;
        case ui::ColorSilver:
            total_text.add_css_class("silver");
        break;
        default:
            total_text.add_css_class("default");;
    }
}