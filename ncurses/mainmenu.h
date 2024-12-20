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
    int selected_index = 0;
    std::vector<std::pair<std::string, std::function<void()>>> menu_options;
    WINDOW *win = nullptr;

public:
    MainMenu(const std::shared_ptr<Game>& game, const MessageHandler& message_handler);
    void Resize(int new_screen_width, int new_screen_height) override;
    void Render() override;

};

#endif //PQ2_MAINMENU_H
