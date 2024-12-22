//
// Created by nbollom on 12/10/18.
//

#include <algorithm>
#include <QApplication>
#include <QScreen>
#include "qtcharatercreator.hpp"

inline QString StringValue(const uint64_t value) {
    char buffer[10];
    sprintf(buffer, "%lu", value);
    return {buffer};
}

inline std::string StripShortcuts(const QString &value) {
    std::string v = value.toStdString();
    std::erase(v, '&');
    return v;
}

QTCharacterCreator::QTCharacterCreator(const std::shared_ptr<Game>& game, const MessageHandler& message_handler) : View(game, message_handler) {
    new_game = game->StartNewGame();
    setWindowTitle("ProgressQuest 2 - Create New Character");
    scroll_area = new QScrollArea();
    scroll_area->setWidgetResizable(true);
    main_widget = new QWidget;
    vlayout = new QVBoxLayout;
    name_layout = new QHBoxLayout;
    name_label = new QLabel("Name");
    std::string name = new_game->GetName();
    name_text = new QLineEdit(name.c_str());
    name_randomiser = new QPushButton("?");
    hlayout = new QHBoxLayout;
    race_group = new QGroupBox("Race");
    race_group->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    race_layout = new QVBoxLayout;
    race_options = new QButtonGroup;
    std::string selected_race = new_game->GetRace();
    for (auto &race_name: NewGame::GetAvailableRaces()) {
        // ReSharper disable once CppDFAMemoryLeak
        auto *race_option = new QRadioButton(race_name.c_str());
        race_options->addButton(race_option);
        race_layout->addWidget(race_option);
        if (selected_race == race_name) {
            race_option->setChecked(true);
        }
    }
    class_group = new QGroupBox("Class");
    class_group->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    class_layout = new QVBoxLayout;
    class_options = new QButtonGroup;
    std::string selected_class = new_game->GetClass();
    for (auto &class_name: NewGame::GetAvailableClasses()) {
        // ReSharper disable once CppDFAMemoryLeak
        auto *class_option = new QRadioButton(class_name.c_str());
        class_options->addButton(class_option);
        class_layout->addWidget(class_option);
        if (selected_class == class_name) {
            class_option->setChecked(true);
        }
    }
    stats_group = new QGroupBox("Stats");
    stats_group->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    stats_layout = new QGridLayout;
    str_label = new QLabel("STR");
    str_text = new QLineEdit;
    str_text->setReadOnly(true);
    con_label = new QLabel("CON");
    con_text = new QLineEdit;
    con_text->setReadOnly(true);
    dex_label = new QLabel("DEX");
    dex_text = new QLineEdit;
    dex_text->setReadOnly(true);
    int_label = new QLabel("INT");
    int_text = new QLineEdit;
    int_text->setReadOnly(true);
    wis_label = new QLabel("WIS");
    wis_text = new QLineEdit;
    wis_text->setReadOnly(true);
    cha_label = new QLabel("CHA");
    cha_text = new QLineEdit;
    cha_text->setReadOnly(true);
    total_label = new QLabel("Total");
    total_text = new QLineEdit;
    total_text->setReadOnly(true);
    roll_button = new QPushButton("Roll");
    unroll_button = new QPushButton("Unroll");
    button_layout = new QHBoxLayout;
    start_button = new QPushButton("Sold!");
    name_layout->addWidget(name_label);
    name_layout->addWidget(name_text);
    name_layout->addWidget(name_randomiser);
    name_layout->addStretch();
    vlayout->addLayout(name_layout);
    race_layout->addStretch();
    race_group->setLayout(race_layout);
    hlayout->addWidget(race_group);
    class_layout->addStretch();
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
    stats_layout->setRowStretch(6, 1);
    stats_layout->addWidget(total_label, 7, 0);
    stats_layout->addWidget(total_text, 7, 1);
    stats_layout->addWidget(roll_button, 8, 0, 1, 2);
    stats_layout->addWidget(unroll_button, 9, 0, 1, 2);
    stats_layout->setRowStretch(10, 10);
    stats_group->setLayout(stats_layout);
    hlayout->addWidget(stats_group);
    vlayout->addLayout(hlayout);
    button_layout->addStretch();
    button_layout->addWidget(start_button);
    vlayout->addLayout(button_layout);
    main_widget->setLayout(vlayout);
    scroll_area->setWidget(main_widget);
    setCentralWidget(scroll_area);
    connect(name_randomiser, &QPushButton::clicked, this, &QTCharacterCreator::GenRandomName);
    connect(race_options, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &QTCharacterCreator::RaceButtonClicked);
    connect(class_options, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &QTCharacterCreator::ClassButtonClicked);
    connect(roll_button, &QPushButton::clicked, this, &QTCharacterCreator::RollStats);
    connect(unroll_button, &QPushButton::clicked, this, &QTCharacterCreator::UnrollStats);
    connect(start_button, &QPushButton::clicked, this, &QTCharacterCreator::Start);
    UpdateStats();
}

QTCharacterCreator::~QTCharacterCreator() = default;

void QTCharacterCreator::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    message_handler("cancel");
}

QSize QTCharacterCreator::sizeHint() const {
    return {1024, 768};
}

void QTCharacterCreator::Show() {
    show();
    move(QApplication::primaryScreen()->geometry().center() - rect().center());
}

void QTCharacterCreator::Hide() {
    hide();
}

void QTCharacterCreator::GenRandomName() const {
    new_game->GenerateName();
    const std::string name = new_game->GetName();
    name_text->setText(name.c_str());
}

void QTCharacterCreator::RaceButtonClicked(const QAbstractButton *button) const {
    new_game->SetRace(StripShortcuts(button->text()));
}

void QTCharacterCreator::ClassButtonClicked(const QAbstractButton *button) const {
    new_game->SetClass(StripShortcuts(button->text()));
}

void QTCharacterCreator::RollStats() const {
    new_game->ReRoll();
    UpdateStats();
}

void QTCharacterCreator::UnrollStats() const {
    new_game->UnRoll();
    UpdateStats();
}

void QTCharacterCreator::Start() const {
    new_game->SetName(name_text->text().toStdString());
    new_game->ConfirmCharacter();
    message_handler("start");
}

void QTCharacterCreator::Close() {

}

void QTCharacterCreator::UpdateStats() const {
    str_text->setText(StringValue(new_game->GetSTR()));
    con_text->setText(StringValue(new_game->GetCON()));
    dex_text->setText(StringValue(new_game->GetDEX()));
    int_text->setText(StringValue(new_game->GetINT()));
    wis_text->setText(StringValue(new_game->GetWIS()));
    cha_text->setText(StringValue(new_game->GetCHA()));
    total_text->setText(StringValue(new_game->GetTotal()));
    switch (new_game->GetTotalColor()) {
        case ui::ColorRed:
            total_text->setStyleSheet("background:#FF0000;");
            break;
        case ui::ColorYellow:
            total_text->setStyleSheet("background:#FFFF00;");
            break;
        case ui::ColorGray:
            total_text->setStyleSheet("background:#808080;");
            break;
        case ui::ColorSilver:
            total_text->setStyleSheet("background:#C0C0C0;");
            break;
        default:
            total_text->setStyleSheet("background:#FFFFFF;");
    }
}

