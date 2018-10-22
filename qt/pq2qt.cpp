//
// Created by nbollom on 5/10/18.
//

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <zconf.h>
#include "pq2qt.h"
#include "qtmainmenu.h"
#include "signals.h"
#include "qtcharatercreator.h"
#include "qtgamescreen.h"

QTGUI::QTGUI(std::shared_ptr<Game> game) : GUI(game) {
    message_handler = std::bind(&QTGUI::HandleMessage, this, std::placeholders::_1, std::placeholders::_2);
}

QTGUI::~QTGUI() {
    QApplication::exit();
}

void QTGUI::Run() {
    int argc = 1;
    char *argv = const_cast<char *>("pq2");
    auto *app = new QApplication(argc, &argv);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setQuitOnLastWindowClosed(false);
    GUI::Run();
    QApplication::exec();
    delete(app);
}

void QTGUI::ShowMainMenu() {
    std::shared_ptr<View> main_menu = std::make_shared<QTMainMenu>(game, message_handler);
    main_menu->Show();
    PushView(main_menu);
}

void QTGUI::ShowCharacterCreator() {
    std::shared_ptr<View> character_creator = std::make_shared<QTCharacterCreator>(game, message_handler);
    character_creator->Show();
    PushView(character_creator);
}

void QTGUI::ShowGameScreen() {
    std::shared_ptr<View> game_screen = std::make_shared<QTGameScreen>(game, message_handler);
    game_screen->Show();
    PushView(game_screen);
}

void QTGUI::Close() {
    PopAllViews();
    game->Close();
    QApplication::exit();
}

void QTGUI::HandleMessage(std::string message, void *data) {
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
        PopAllViews();
        ShowGameScreen();
    }
}
