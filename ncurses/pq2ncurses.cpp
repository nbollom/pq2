#include "pq2ncurses.hpp"
#include <ncurses.h>
#include <iostream>
#include "mainmenu.hpp"
#include "charactercreator.hpp"
#include "gamescreen.hpp"
#include <utils.hpp>

#include "loadscreen.hpp"


using namespace std;
using namespace game;

bool running = false;

NCursesGUI::NCursesGUI(const std::shared_ptr<Game> &game) : GUI(game), screen_width(0), screen_height(0) {
    message_handler = [this](const std::string &message) {
        HandleMessage(message);
    };
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    ESCDELAY = 1;
}

NCursesGUI::~NCursesGUI() {
    endwin();
    cout << "cleaning up" << endl;
}

void NCursesGUI::Run() {
    GUI::Run();
    running = true;
    while (running) {
        const shared_ptr<NCursesView> current_view = static_pointer_cast<NCursesView>(view_stack.top());
        int new_width;
        int new_height;
        getmaxyx(stdscr, new_height, new_width);
        if (new_width != screen_width || new_height != screen_height) {
            screen_width = new_width;
            screen_height = new_height;
            current_view->Resize(screen_width, screen_height);
        }
        current_view->Update();
    }
}

void NCursesGUI::HandleMessage(const std::string& message) {
    if (message == "quit") {
        // Don't close if there is nothing on the stack like when we pop all views to replace them with the game screen
        if (!view_stack.empty()) {
            Close();
        }
    }
    else if (message == "new") {
        ShowCharacterCreator();
    }
    else if (message == "load_screen") {
        ShowLoadScreen();
    }
    else if (message == "cancel") {
        PopView();
        if (!view_stack.empty()) {
            const shared_ptr<NCursesView> current_view = static_pointer_cast<NCursesView>(view_stack.top());
            current_view->Resize(screen_width, screen_height);
        }
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

void NCursesGUI::ShowMainMenu() {
    const auto menu = make_shared<MainMenu>(game, message_handler);
    menu->Resize(screen_width, screen_height);
    menu->Show();
    PushView(menu);
}

void NCursesGUI::ShowCharacterCreator() {
    const auto character_creator = std::make_shared<CharacterCreator>(game, message_handler);
    character_creator->Resize(screen_width, screen_height);
    character_creator->Show();
    PushView(character_creator);
}

void NCursesGUI::ShowGameScreen() {
    const auto game_screen = std::make_shared<GameScreen>(game, message_handler);
    game_screen->Resize(screen_width, screen_height);
    game_screen->Show();
    PushView(game_screen);
}

void NCursesGUI::ShowLoadScreen() {
    const auto load_screen = std::make_shared<LoadScreen>(game, message_handler);
    load_screen->Resize(screen_width, screen_height);
    load_screen->Show();
    PushView(load_screen);
}


void NCursesGUI::Close() {
    running = false;
    game->Close();
}
