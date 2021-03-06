//
// Created by nbollom on 12/10/18.
//

#ifndef PQ2_CHARATERCREATOR_H
#define PQ2_CHARATERCREATOR_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QGridLayout>
#include "view.h"
#include "newgame.h"

class QTCharacterCreator : public QMainWindow, public View {
Q_OBJECT

private:
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

    void UpdateStats();

public:
    QTCharacterCreator(std::shared_ptr<Game> game, std::function<void(std::string, void*)> message_handler);
    ~QTCharacterCreator() override;

    void closeEvent(QCloseEvent *event) override;
    QSize sizeHint() const override;

    void Show() override;
    void Hide() override;

public slots:
    void GenRandomName();
    void RaceButtonClicked(QAbstractButton *button);
    void ClassButtonClicked(QAbstractButton *button);
    void RollStats();
    void UnrollStats();
    void Start();
    void Close() override;

};

#endif //PQ2_CHARATERCREATOR_H
