#include "pq2ncurses.h"
#include <ncurses.h>
#include <iostream>
#include "mainmenu.h"
#include <utils.h>

using namespace std;
using namespace game;

bool running = false;

NCursesGUI::NCursesGUI(const std::shared_ptr<Game> &game) : GUI(game), screen_width(0), screen_height(0) {
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();
    timeout(100);
    screen_changed = false;
    AddSignalCallback(
        SIGWINCH, [this](int sig) {
            screen_change_lock.lock();
            screen_changed = true;
            screen_change_lock.unlock();
        }
    );
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
        const shared_ptr<NCursesView> current_view = static_pointer_cast<NCursesView>(view_stack.top());
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

bool NCursesGUI::ProcessMessage(const std::string& message, void *value) {
    if(message == "Quit") {
        Close();
    }
    return true;
}

void NCursesGUI::ShowMainMenu() {
    const shared_ptr<View> menu = make_shared<MainMenu>(game, [this](auto && PH1, auto && PH2) {
        return ProcessMessage(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    });
    view_stack.push(menu);
}

void NCursesGUI::ShowCharacterCreator() {

}

void NCursesGUI::ShowGameScreen() {

}

void NCursesGUI::Close() {
    running = false;
}
