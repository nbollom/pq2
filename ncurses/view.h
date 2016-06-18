//
// Created by nbollom on 17/06/16.
//

#ifndef PQ2_VIEW_H
#define PQ2_VIEW_H

class View {

public:
    virtual void HandleKeyPress(int key) = 0;
    virtual void Render() = 0;
};

#endif //PQ2_VIEW_H
