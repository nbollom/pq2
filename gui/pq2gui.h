//
// Created by nbollom on 30/05/16.
//

#ifndef PQ2_PQ2GUI_H
#define PQ2_PQ2GUI_H

class GUI {

private:

protected:
    GUI(); //cannot directly instantiate base class

public:
    virtual void ShowMainWindow() = 0; //called if there is no game in progress (no filename passed to command-line)
    virtual void ShowGameWindow() = 0; //called if there is a game in progress

};

#endif //PQ2_PQ2GUI_H
