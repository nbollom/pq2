//
// Created by nbollom on 4/01/25.
//

#include <giomm/liststore.h>
#include <gtkmm/filter.h>
#include <gtkmm/alertdialog.h>
#include "mainmenu.hpp"

MainMenu::MainMenu(const std::shared_ptr<Game> &game, const MessageHandler &message_handler) : View(game, message_handler) {
    set_title("Progress Quest 2");
    set_default_size(800, 600);
    signal_destroy().connect([this]() {
        Close();
    });

    box.set_orientation(Gtk::Orientation::VERTICAL);
    box.set_spacing(20);
    box.set_homogeneous(false);

    set_child(box);

    logo.set_from_resource("/com/github/nbollom/pq2/pq.png");
    logo.set_size_request(300, 300);
    logo.set_margin_top(100);

    new_game.set_label("New Game");
    new_game.set_size_request(200, 60);
    new_game.set_margin_start(100);
    new_game.set_margin_end(100);
    new_game.signal_clicked().connect([this]() {
        NewGame();
    });

    load_game.set_label("Load Game");
    load_game.set_size_request(200, 60);
    load_game.set_margin_start(100);
    load_game.set_margin_end(100);
    load_game.signal_clicked().connect([&]() {
        file_dialog->open(*this, [&](const Glib::RefPtr<Gio::AsyncResult>& result) {
            const auto file = file_dialog->open_finish(result);
            if (const file::LoadError error = game->LoadGame(file->get_path()); error == file::LoadErrorNone) {
                message_handler("load");
            }
            else {
                const auto error_dialog = Gtk::AlertDialog::create("Error");
                error_dialog->set_detail("Error loading save game");
                error_dialog->set_buttons({"Ok"});
                error_dialog->show();
            }
        }, nullptr);
    });

    quit.set_label("Quit");
    quit.set_size_request(200, 60);
    quit.set_margin_start(100);
    quit.set_margin_end(100);
    quit.signal_clicked().connect([this]() {
        Close();
    });

    box.append(logo);
    box.append(new_game);
    box.append(load_game);
    box.append(quit);

    file_dialog = Gtk::FileDialog::create();
    file_dialog->set_title("Progress Quest 2 - Load Game");
    const auto pq2_files = Gtk::FileFilter::create();
    pq2_files->add_suffix("pq2");
    pq2_files->set_name("PQ2 save game");
    const auto filters = Gio::ListStore<Gtk::FileFilter>::create();
    filters->append(pq2_files);
    file_dialog->set_filters(filters);

    Show();
}

MainMenu::~MainMenu() {

}

void MainMenu::Show() {
    show();
}

void MainMenu::Hide() {
    set_visible(false);
}

void MainMenu::Close() {
    if (!closed) {
        message_handler("quit");
        closed = true;
    }
}

void MainMenu::NewGame() const {
    message_handler("new");
}

void MainMenu::LoadGame() const {
    message_handler("load");
}
