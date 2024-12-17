//
// Created by nbollom on 9/10/18.
//

#ifndef PQ2_QTMAINMENU_H
#define PQ2_QTMAINMENU_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "view.h"

class QTMainMenu final : public QMainWindow, public View {
Q_OBJECT

private:
    QWidget *main_widget;
    QVBoxLayout *main_layout;
    QPixmap logo_image;
    QLabel *logo;
    QPushButton *new_game;
    QPushButton *load_game;
    QPushButton *exit_game;

public:
    QTMainMenu(const std::shared_ptr<Game>& game, const std::function<void(std::string, void*)> &message_handler);
    ~QTMainMenu() override;

    void closeEvent(QCloseEvent *event) override;

    void Show() override;
    void Hide() override;
    void resizeEvent(QResizeEvent *event) override;
    void ResizeLogo() const;
public slots:
    void NewGame() const;
    void LoadGame() const;
    void Close() override;

};

#endif //PQ2_QTMAINMENU_H
