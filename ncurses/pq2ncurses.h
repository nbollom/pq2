//
// Created by nbollom on 26/05/16.
//

#ifndef PQ2_PQ2NCURSES_H
#define PQ2_PQ2NCURSES_H

#include <memory>
#include <string>
#include "pq2gui.h"
#include "game.h"

class NCursesGUI final : public GUI {

private:
    MessageHandler message_handler;
    int screen_width;
    int screen_height;

    void HandleMessage(const std::string& message);

public:
    explicit NCursesGUI(const std::shared_ptr<Game> &game);
    ~NCursesGUI() override;
    void Run() override;

    void ShowMainMenu() override;
    void ShowCharacterCreator() override;
    void ShowGameScreen() override;
    void Close() override;

};

#endif //PQ2_PQ2NCURSES_H
