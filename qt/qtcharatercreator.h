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

class QTCharacterCreator : public QMainWindow, public View {

private:
    QWidget *main_widget;
    QVBoxLayout *vlayout;
    QLabel *name_label;
    QLineEdit *name_text;
    QPushButton *name_randomiser;
    QHBoxLayout *hlayout;
    QGroupBox *race_group;
    QButtonGroup race_options;
    QGroupBox *class_group;
    QButtonGroup class_options;
    QGroupBox *stats_group;
    QGridLayout *slats_layout;
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
    QLabel *total_text;
    QPushButton *roll_button;
    QPushButton *unroll_button;
    QPushButton *start_button;

public:
    QTCharacterCreator(std::shared_ptr<Game> game, std::function<void(std::string, void*)> message_handler);
    ~QTCharacterCreator();

    void closeEvent(QCloseEvent *event) override;

    void Show() override;
    void Hide() override;

public slots:
    void GenRandomName();
    void RaceButtonClicked(int id);
    void ClassButtonClicked(int id);
    void RollStats();
    void UnrollStats();
    void Close() override;

};

#endif //PQ2_CHARATERCREATOR_H
