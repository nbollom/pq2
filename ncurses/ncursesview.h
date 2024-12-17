//
// Created by nbollom on 13/01/19.
//

#ifndef PQ2_NCURSESTOOLS_H
#define PQ2_NCURSESTOOLS_H

#include <string>
#include "view.h"

class NCursesView : public View {

protected:
    int screen_width{};
    int screen_height{};

public:
    NCursesView(const std::shared_ptr<Game>& game, const std::function<bool(std::string message, void *value)>& message_handler);

    static void LeftAlign(const std::string& value, int x, int y);
    static void RightAlign(const std::string& value, int x, int y);
    static void CenterAlign(const std::string& value, int x, int y);

    void Resize(int new_screen_width, int new_screen_height);
    virtual void HandleKeyPress(int key) = 0;
    virtual void Render() = 0;

};

#endif //PQ2_NCURSESTOOLS_H
