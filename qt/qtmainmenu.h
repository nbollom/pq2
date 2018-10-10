//
// Created by nbollom on 9/10/18.
//

#ifndef PQ2_QTMAINMENU_H
#define PQ2_QTMAINMENU_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include "view.h"

class QTMainMenu : public QMainWindow, public View {
Q_OBJECT

private:
    QWidget *main_widget;
    QVBoxLayout *main_layout;
    QPushButton *new_game;
    QPushButton *load_game;
    QPushButton *exit_game;

public:
    QTMainMenu(std::shared_ptr<Game> game, std::function<void(std::string, void*)> message_handler);
    ~QTMainMenu() override;

    void closeEvent(QCloseEvent *event) override;

public slots:
    void Show() override;
    void Hide() override;
    void Close() override;


};

#endif //PQ2_QTMAINMENU_H
