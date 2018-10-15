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

QTGUI::QTGUI(std::shared_ptr<Game> game) : GUI(game) {
    message_handler = std::bind(&QTGUI::HandleMessage, this, std::placeholders::_1, std::placeholders::_2);
}

QTGUI::~QTGUI() {
    QApplication::exit();
}

void QTGUI::Run() {
    int argc = 0;
    auto *app = new QApplication(argc, nullptr);
    app->setQuitOnLastWindowClosed(false);
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

}

void QTGUI::Close() {
    PopAllViews();
    game->Close();
    QApplication::exit();
}

void QTGUI::HandleMessage(std::string message, void *data) {
    if (message == "quit") {
        Close();
    }
    else if (message == "new") {
        ShowCharacterCreator();
    }
    else if (message == "cancel") {
        PopView();
    }
}
