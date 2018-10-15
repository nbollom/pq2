//
// Created by nbollom on 5/10/18.
//

#ifndef PQ2_PQ2QT_H
#define PQ2_PQ2QT_H

#include <pq2gui.h>
#include <memory>
#include <functional>

class QTGUI : public GUI {

private:
    std::function<void(std::string, void*)> message_handler;

public:
    explicit QTGUI(std::shared_ptr<Game> game);
    ~QTGUI() override;
    void Run() override;

    void ShowMainMenu() override;
    void ShowCharacterCreator() override;
    void ShowGameScreen() override;
    void Close() override;
    void HandleMessage(std::string message, void *data);
};

#endif //PQ2_PQ2QT_H
