//
// Created by nbollom on 13/01/19.
//

#ifndef PQ2_NCURSESTOOLS_H
#define PQ2_NCURSESTOOLS_H

#include <string>
#include <ncurses.h>
#include "view.h"

class NCursesView : public View {

protected:
    int screen_width{};
    int screen_height{};
    bool visible = true;

public:
    NCursesView(const std::shared_ptr<Game>& game, const MessageHandler& message_handler);

    static void LeftAlign(WINDOW *win, const std::string& value, int x, int y);
    static void RightAlign(WINDOW *win, const std::string& value, int x, int y);
    static void CenterAlign(WINDOW *win, const std::string& value, int x, int y);

    virtual void Resize(int new_screen_width, int new_screen_height);
    virtual void Render() = 0;

    void Show() override;
    void Hide() override;
    void Close() override;

};

#endif //PQ2_NCURSESTOOLS_H
