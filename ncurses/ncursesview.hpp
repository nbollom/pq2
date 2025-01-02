//
// Created by nbollom on 13/01/19.
//

#pragma once

#include <string>
#include <ncurses.h>
#include "view.hpp"

class NCursesView : public View {

protected:
    int screen_width{};
    int screen_height{};
    bool visible = true;
    WINDOW *win = nullptr;
    const int required_width = 80;
    const int required_height = 24;
    WINDOW *popup = nullptr;
    int last_popup_width = 0;
    int last_popup_height = 0;

public:
    NCursesView(const std::shared_ptr<Game>& game, const MessageHandler& message_handler);

    static void LeftAlign(WINDOW *win, const std::string& value, int x, int y);
    static void RightAlign(WINDOW *win, const std::string& value, int x, int y);
    static void CenterAlign(WINDOW *win, const std::string& value, int x, int y);

    void ShowPopup(const std::string &label, const std::vector<std::string> &items, int current_index);
    void ClearPopup();

    void Resize(int new_screen_width, int new_screen_height);
    void Update();
    virtual void Render() = 0;
    virtual void HandleKey(int key) = 0;

    void Show() override;
    void Hide() override;
    void Close() override;

};
