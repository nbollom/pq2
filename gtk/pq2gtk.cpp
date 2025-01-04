//
// Created by nbollom on 4/01/25.
//

#include <gtkmm/application.h>
#include "pq2gtk.hpp"
#include "mainmenu.hpp"

GTKGUI::GTKGUI(const std::shared_ptr<Game> &game) : GUI(game) {
    message_handler = [this](const std::string &message) {
        HandleMessage(message);
    };
    app = Gtk::Application::create("com.github.nbollom.pq2", Gio::Application::Flags::DEFAULT_FLAGS);
    app->signal_startup().connect([this]() {
        GUI::Run();
    });
}

GTKGUI::~GTKGUI() {
}

void GTKGUI::Run() {
    app->run();
}

void GTKGUI::HandleMessage(const std::string& message) {
    if (message == "quit") {
        // Don't close if there is nothing on the stack like when we pop all views to replace them with the game screen
        if (!view_stack.empty()) {
            Close();
        }
    }
    else if (message == "new") {
        ShowCharacterCreator();
    }
    else if (message == "cancel") {
        PopView();
    }
    else if (message == "start") {
        game->SaveGame(game->GetCharacter().Name + ".pq2");
        PopAllViews();
        ShowGameScreen();
    }
    else if (message == "load") {
        PopAllViews();
        ShowGameScreen();
    }
}

void GTKGUI::ShowMainMenu() {
    const auto menu = make_shared<MainMenu>(game, message_handler);
    app->add_window(*menu.get());
    menu->Show();
    PushView(menu);
}

void GTKGUI::ShowCharacterCreator() {
    // const auto character_creator = std::make_shared<CharacterCreator>(game, message_handler);
    // character_creator->Show();
    // PushView(character_creator);
}

void GTKGUI::ShowGameScreen() {
    // const auto game_screen = std::make_shared<GameScreen>(game, message_handler);
    // game_screen->Show();
    // PushView(game_screen);
}

void GTKGUI::Close() {
    app->quit();
    game->Close();
}
