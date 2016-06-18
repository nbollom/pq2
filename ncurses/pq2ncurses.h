//
// Created by nbollom on 26/05/16.
//

#ifndef PQ2_PQ2NCURSES_H
#define PQ2_PQ2NCURSES_H

#include <memory>
#include <stack>
#include "pq2gui.h"
#include "game.h"
#include "view.h"

class NCursesGUI : public GUI {

private:
    std::stack<View> _viewStack;

    void StartGameLoop();

public:
    NCursesGUI(std::shared_ptr<Game> game);
    void Run() override;

};

#endif //PQ2_PQ2NCURSES_H
