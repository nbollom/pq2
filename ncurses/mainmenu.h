//
// Created by nbollom on 21/06/16.
//

#ifndef PQ2_MAINMENU_H
#define PQ2_MAINMENU_H

#include <functional>
#include <vector>
#include <string>
#include "ncursesview.h"

class MainMenu : public NCursesView {
    int selected_index;
    std::vector<std::pair<std::string, std::function<void()>>> menu_options;

public:
    MainMenu(std::shared_ptr<Game> game, std::function<bool(std::string message, void *value)> message_handler);
    void HandleKeyPress(int key) override;
    void Render() override;
    virtual void Show() override;
    virtual void Hide() override;
    virtual void Close() override;

};

#endif //PQ2_MAINMENU_H
