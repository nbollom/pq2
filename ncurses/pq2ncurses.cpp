#include "pq2ncurses.h"
#include <ncurses.h>
#include <iostream>
#include "mainmenu.h"
#include "signals.h"

using namespace std;
using namespace game;

bool running = false;

NCursesGUI::NCursesGUI(std::shared_ptr<Game> game) : GUI(game) {
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();
    timeout(100);
    screen_changed = false;
    AddSignalCallback(SIGWINCH, [this](int sig){
        screen_change_lock.lock();
        screen_changed = true;
        screen_change_lock.unlock();
    });
    RaiseSignal(SIGWINCH);
}

NCursesGUI::~NCursesGUI() {
    endwin();
    cout << "cleaning up" << endl;
}

void NCursesGUI::Run() {
    GUI::Run();
    running = true;
    int ch = 0;
    while (running) {
        screen_change_lock.lock();
        shared_ptr<NCursesView> current_view = static_pointer_cast<NCursesView>(view_stack.top());
        if (screen_changed) {
            endwin();
            initscr();
            getmaxyx(stdscr, screen_height, screen_width);
            current_view->Resize(screen_width, screen_height);
            screen_changed = false;
        }
        screen_change_lock.unlock();
        clear();
        current_view->Render();
        refresh();
        ch = getch();
        if (ch != ERR) { //wasn't a timeout but a real keypress`
            current_view->HandleKeyPress(ch);
            if (ch == 'q') { //global quit key
                running = false;
            }
        }
    }
}

bool NCursesGUI::ProcessMessage(std::string message, void *value) {
    if(message == "Quit") {
        Close();
    }
    return true;
}

void NCursesGUI::ShowMainMenu() {
    shared_ptr<View> menu = make_shared<MainMenu>(game, std::bind(&NCursesGUI::ProcessMessage, this, std::placeholders::_1, std::placeholders::_2));
    view_stack.push(menu);
}

void NCursesGUI::ShowCharacterCreator() {

}

void NCursesGUI::ShowGameScreen() {

}

void NCursesGUI::Close() {
    running = false;
}
