//
// Created by nbollom on 5/10/18.
//

#ifndef PQ2_PQ2QT_H
#define PQ2_PQ2QT_H

#include <pq2gui.h>
#include <memory>
#include <functional>

class QTGUI final : public GUI {

private:
    MessageHandler message_handler;

public:
    explicit QTGUI(const std::shared_ptr<Game> &game);
    ~QTGUI() override;
    void Run() override;

    void ShowMainMenu() override;
    void ShowCharacterCreator() override;
    void ShowGameScreen() override;
    void Close() override;
    void HandleMessage(const std::string& message);
};

#endif //PQ2_PQ2QT_H
