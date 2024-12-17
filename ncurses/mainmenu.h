//
// Created by nbollom on 21/06/16.
//

#ifndef PQ2_MAINMENU_H
#define PQ2_MAINMENU_H

#include <functional>
#include <vector>
#include <string>
#include "ncursesview.h"

class MainMenu final : public NCursesView {
    int selected_index;
    std::vector<std::pair<std::string, std::function<void()>>> menu_options;

public:
    MainMenu(const std::shared_ptr<Game>& game, const std::function<bool(std::string message, void *value)>& message_handler);
    void HandleKeyPress(int key) override;
    void Render() override;
    void Show() override;
    void Hide() override;
    void Close() override;

};

#endif //PQ2_MAINMENU_H
