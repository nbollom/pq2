//
// Created by nbollom on 12/10/18.
//

#include "qtcharatercreator.h"

inline QString StringValue(uint64_t value) {
    char buffer[10];
    sprintf(buffer, "%llu", value);
    return QString(buffer);
}

QTCharacterCreator::QTCharacterCreator(std::shared_ptr<Game> game, std::function<void(std::string, void *)> message_handler) : View(game, message_handler) {
    new_game = game->StartNewGame();
    setWindowTitle("Progress Quest 2 - Create New Character");
    main_widget = new QWidget;
    vlayout = new QVBoxLayout;
    name_layout = new QHBoxLayout;
    name_label = new QLabel("Name");
    std::string name = new_game->GetName();
    name_text = new QLineEdit(name.c_str());
    name_randomiser = new QPushButton("?");
    hlayout = new QHBoxLayout;
    race_group = new QGroupBox("Race");
    race_layout = new QVBoxLayout;
    std::string selected_race = new_game->GetRace();
    for (auto &race_name: new_game->GetAvailableRaces()) {
        QRadioButton *race_option = new QRadioButton(race_name.c_str());
        race_options.addButton(race_option);
        race_layout->addWidget(race_option);
        if (selected_race == race_name) {
            race_option->setChecked(true);
        }
    }
    class_group = new QGroupBox("Class");
    class_layout = new QVBoxLayout;
    std::string selected_class = new_game->GetClass();
    for (auto &class_name: new_game->GetAvailableClasses()) {
        QRadioButton *class_option = new QRadioButton(class_name.c_str());
        class_options.addButton(class_option);
        class_layout->addWidget(class_option);
        if (selected_class == class_name) {
            class_option->setChecked(true);
        }
    }
    stats_group = new QGroupBox("Stats");
    stats_layout = new QGridLayout;
    str_label = new QLabel("STR");
    str_text = new QLineEdit(StringValue(new_game->GetSTR()));
    str_text->setReadOnly(true);
    con_label = new QLabel("CON");
    con_text = new QLineEdit(StringValue(new_game->GetCON()));
    con_text->setReadOnly(true);
    dex_label = new QLabel("DEX");
    dex_text = new QLineEdit(StringValue(new_game->GetDEX()));
    dex_text->setReadOnly(true);
    int_label = new QLabel("INT");
    int_text = new QLineEdit(StringValue(new_game->GetINT()));
    int_text->setReadOnly(true);
    wis_label = new QLabel("WIS");
    wis_text = new QLineEdit(StringValue(new_game->GetWIS()));
    wis_text->setReadOnly(true);
    cha_label = new QLabel("CHA");
    cha_text = new QLineEdit(StringValue(new_game->GetCHA()));
    cha_text->setReadOnly(true);



    name_layout->addWidget(name_label);
    name_layout->addWidget(name_text);
    name_layout->addWidget(name_randomiser);
    name_layout->addStretch();
    vlayout->addLayout(name_layout);
    race_group->setLayout(race_layout);
    hlayout->addWidget(race_group);
    class_group->setLayout((class_layout));
    hlayout->addWidget(class_group);
    stats_layout->addWidget(str_label, 0, 0);
    stats_layout->addWidget(str_text, 0, 1);
    stats_layout->addWidget(con_label, 1, 0);
    stats_layout->addWidget(con_text, 1, 1);
    stats_layout->addWidget(dex_label, 2, 0);
    stats_layout->addWidget(dex_text, 2, 1);
    stats_layout->addWidget(int_label, 3, 0);
    stats_layout->addWidget(int_text, 3, 1);
    stats_layout->addWidget(wis_label, 4, 0);
    stats_layout->addWidget(wis_text, 4, 1);
    stats_layout->addWidget(cha_label, 5, 0);
    stats_layout->addWidget(cha_text, 5, 1);



    stats_layout->setColumnStretch(2, 1);
    stats_layout->setRowStretch(8, 1);
    stats_group->setLayout(stats_layout);
    hlayout->addWidget(stats_group);
    vlayout->addLayout(hlayout);
    vlayout->addStretch();
    main_widget->setLayout(vlayout);
    setCentralWidget(main_widget);
}

QTCharacterCreator::~QTCharacterCreator() {

}

void QTCharacterCreator::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    message_handler("cancel", nullptr);
}

void QTCharacterCreator::Show() {
    show();
}

void QTCharacterCreator::Hide() {
    hide();
}

void QTCharacterCreator::GenRandomName() {

}

void QTCharacterCreator::RaceButtonClicked(int id) {

}

void QTCharacterCreator::ClassButtonClicked(int id) {

}

void QTCharacterCreator::RollStats() {

}

void QTCharacterCreator::UnrollStats() {

}

void QTCharacterCreator::Close() {

}
