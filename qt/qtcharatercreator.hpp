//
// Created by nbollom on 12/10/18.
//

#pragma once

#include <QButtonGroup>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollArea>
#include <QWidget>
#include "newgame.hpp"
#include <pq2gui.hpp>

class QTCharacterCreator final : public QMainWindow, public View {
Q_OBJECT

private:
    QScrollArea *scroll_area;
    QWidget *main_widget;
    QVBoxLayout *vlayout;
    QHBoxLayout *name_layout;
    QLabel *name_label;
    QLineEdit *name_text;
    QPushButton *name_randomiser;
    QHBoxLayout *hlayout;
    QGroupBox *race_group;
    QVBoxLayout *race_layout;
    QButtonGroup *race_options;
    QGroupBox *class_group;
    QVBoxLayout *class_layout;
    QButtonGroup *class_options;
    QGroupBox *stats_group;
    QGridLayout *stats_layout;
    QLabel *str_label;
    QLineEdit *str_text;
    QLabel *con_label;
    QLineEdit *con_text;
    QLabel *dex_label;
    QLineEdit *dex_text;
    QLabel *int_label;
    QLineEdit *int_text;
    QLabel *wis_label;
    QLineEdit *wis_text;
    QLabel *cha_label;
    QLineEdit *cha_text;
    QLabel *total_label;
    QLineEdit *total_text;
    QPushButton *roll_button;
    QPushButton *unroll_button;
    QHBoxLayout *button_layout;
    QPushButton *start_button;

    std::shared_ptr<NewGame> new_game;

    void UpdateStats() const;

public:
    QTCharacterCreator(const std::shared_ptr<Game>& game, const MessageHandler& message_handler);
    ~QTCharacterCreator() override;

    void closeEvent(QCloseEvent *event) override;
    QSize sizeHint() const override;

    void Show() override;
    void Hide() override;

public slots:
    void GenRandomName() const;
    void RaceButtonClicked(const QAbstractButton *button) const;
    void ClassButtonClicked(const QAbstractButton *button) const;
    void RollStats() const;
    void UnrollStats() const;
    void Start() const;
    void Close() override;

};
