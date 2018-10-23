//
// Created by nbollom on 19/10/18.
//

#include <QHeaderView>
#include <QApplication>
#include <QDesktopWidget>
#include <QCheckBox>
#include "qtgamescreen.h"

#define MARGIN_AMOUNT 0

QTGameScreen::QTGameScreen(std::shared_ptr<Game> game, std::function<void(std::string, void *)> message_handler) : View(game, message_handler) {
    std::string title = "ProgressQuest 2 - ";
    QMargins margins(MARGIN_AMOUNT, MARGIN_AMOUNT, MARGIN_AMOUNT, MARGIN_AMOUNT);
    auto character = game->GetCharacter();
    title += character->Name;
    setWindowTitle(title.c_str());
    main_widget = new QWidget;
    main_vlayout = new QVBoxLayout;
    columns_hlayout = new QHBoxLayout;
    col1_layout = new QVBoxLayout;
    col1_layout->setContentsMargins(margins);
    col1_layout->setSpacing(MARGIN_AMOUNT);
    character_group = new QGroupBox("Character Sheet");
    character_group->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    character_layout = new QVBoxLayout;
    character_layout->setContentsMargins(margins);
    character_layout->setSpacing(MARGIN_AMOUNT);
    character_table = new QTableWidget(4, 2);
    character_table->setHorizontalHeaderLabels(QStringList{"Trait", "Value"});
    character_table->verticalHeader()->setVisible(false);
    character_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    character_table->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    character_table->setItem(0, 0, new QTableWidgetItem("Name"));
    character_table->setItem(1, 0, new QTableWidgetItem("Race"));
    character_table->setItem(2, 0, new QTableWidgetItem("Class"));
    character_table->setItem(3, 0, new QTableWidgetItem("Level"));
    character_table->setItem(0, 1, new QTableWidgetItem(character->Name.c_str()));
    character_table->setItem(1, 1, new QTableWidgetItem(character->CharacterRace.name.c_str()));
    character_table->setItem(2, 1, new QTableWidgetItem(character->CharacterClass.name.c_str()));
    auto table_height = character_table->rowCount() * character_table->rowHeight(0) + character_table->horizontalHeader()->height() + 2;
    character_table->setMinimumHeight(table_height);
    character_table->setMaximumHeight(table_height);
    stats_table = new QTableWidget(8, 2);
    stats_table->setHorizontalHeaderLabels(QStringList{"Stat", "Value"});
    stats_table->verticalHeader()->setVisible(false);
    stats_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    stats_table->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    stats_table->setItem(0, 0, new QTableWidgetItem("STR"));
    stats_table->setItem(1, 0, new QTableWidgetItem("CON"));
    stats_table->setItem(2, 0, new QTableWidgetItem("DEX"));
    stats_table->setItem(3, 0, new QTableWidgetItem("INT"));
    stats_table->setItem(4, 0, new QTableWidgetItem("WIS"));
    stats_table->setItem(5, 0, new QTableWidgetItem("CHA"));
    stats_table->setItem(6, 0, new QTableWidgetItem("HP Max"));
    stats_table->setItem(7, 0, new QTableWidgetItem("MP Max"));
    table_height = stats_table->rowCount() * stats_table->rowHeight(0) + stats_table->horizontalHeader()->height() + 2;
    stats_table->setMinimumHeight(table_height);
    stats_table->setMaximumHeight(table_height);
    experience_label = new QLabel("Experience");
    experience_progress = new QProgressBar;
    experience_progress->setRange(0, 100);
    UpdateStats();
    spells_group = new QGroupBox("Spells");
    spells_group->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spells_layout = new QVBoxLayout;
    spells_layout->setContentsMargins(margins);
    spells_layout->setSpacing(MARGIN_AMOUNT);
    spells_table = new QTableWidget(0, 2);
    spells_table->setHorizontalHeaderLabels(QStringList{"Spell", "Level"});
    spells_table->verticalHeader()->setVisible(false);
    spells_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    spells_table->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    UpdateSpells();
    col2_layout = new QVBoxLayout;
    col2_layout->setContentsMargins(margins);
    col2_layout->setSpacing(MARGIN_AMOUNT);
    equipment_group = new QGroupBox("Equipment");
    equipment_layout = new QVBoxLayout;
    equipment_layout->setContentsMargins(margins);
    equipment_layout->setSpacing(MARGIN_AMOUNT);
    equipment_group->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    equipment_table = new QTableWidget(11, 2);
    equipment_table->verticalHeader()->setVisible(false);
    equipment_table->horizontalHeader()->setVisible(false);
    equipment_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    equipment_table->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    auto equipment_index = 0;
    for (const auto& label: data::EquipmentLabels) {
        equipment_table->setItem(equipment_index++, 0, new QTableWidgetItem(label.c_str()));
    }
    table_height = equipment_table->rowCount() * equipment_table->rowHeight(0) + 2;
    equipment_table->setMinimumHeight(table_height);
    equipment_table->setMaximumHeight(table_height);
    UpdateEquipment();
    inventory_group = new QGroupBox("Inventory");
    inventory_group->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    inventory_layout = new QVBoxLayout;
    inventory_layout->setContentsMargins(margins);
    inventory_layout->setSpacing(MARGIN_AMOUNT);
    inventory_table = new QTableWidget(0, 2);
    inventory_table->setHorizontalHeaderLabels(QStringList{"Item", "Qty"});
    inventory_table->verticalHeader()->setVisible(false);
    inventory_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    inventory_table->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    encumbrance_label = new QLabel("Encumbrance");
    encumbrance_progress = new QProgressBar;
    encumbrance_progress->setRange(0, 100);
    UpdateInventory();
    col3_layout = new QVBoxLayout;
    col3_layout->setContentsMargins(margins);
    col3_layout->setSpacing(MARGIN_AMOUNT);
    plot_group = new QGroupBox("Plot Development");
    plot_layout = new QVBoxLayout;
    plot_layout->setContentsMargins(margins);
    plot_layout->setSpacing(MARGIN_AMOUNT);
    plot_table = new QTableWidget(0, 1);
    plot_table->verticalHeader()->setVisible(false);
    plot_table->horizontalHeader()->setVisible(false);
    plot_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    plot_table->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    plot_progress = new QProgressBar;
    plot_progress->setRange(0, 100);
    UpdatePlot();
    quest_group = new QGroupBox("Quests");
    quest_layout = new QVBoxLayout;
    quest_layout->setContentsMargins(margins);
    quest_layout->setSpacing(MARGIN_AMOUNT);
    quest_table = new QTableWidget(0, 1);
    quest_table->verticalHeader()->setVisible(false);
    quest_table->horizontalHeader()->setVisible(false);
    quest_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    quest_table->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    quest_progress = new QProgressBar;
    quest_progress->setRange(0, 100);
    UpdateQuests();
    status_label = new QLabel();
    status_progress = new QProgressBar;
    status_progress->setRange(0, 100);
    UpdateStatus();
    character_layout->addWidget(character_table);
    character_layout->addWidget(stats_table);
    character_layout->addWidget(experience_label);
    character_layout->addWidget(experience_progress);
    character_group->setLayout(character_layout);
    col1_layout->addWidget(character_group);
    spells_layout->addWidget(spells_table);
    spells_group->setLayout(spells_layout);
    col1_layout->addWidget(spells_group);
    columns_hlayout->addLayout(col1_layout);
    equipment_layout->addWidget(equipment_table);
    equipment_group->setLayout(equipment_layout);
    col2_layout->addWidget(equipment_group);
    inventory_layout->addWidget(inventory_table);
    inventory_layout->addWidget(encumbrance_label);
    inventory_layout->addWidget(encumbrance_progress);
    inventory_group->setLayout(inventory_layout);
    col2_layout->addWidget(inventory_group);
    columns_hlayout->addLayout(col2_layout);
    plot_layout->addWidget(plot_table);
    plot_layout->addWidget(plot_progress);
    plot_group->setLayout(plot_layout);
    col3_layout->addWidget(plot_group);
    quest_layout->addWidget(quest_table);
    quest_layout->addWidget(quest_progress);
    quest_group->setLayout(quest_layout);
    col3_layout->addWidget(quest_group);
    columns_hlayout->addLayout(col3_layout);
    main_vlayout->addLayout(columns_hlayout);
    main_vlayout->addWidget(status_label);
    main_vlayout->addWidget(status_progress);
    main_widget->setLayout(main_vlayout);
    setCentralWidget(main_widget);
}

QTGameScreen::~QTGameScreen() {

}

void QTGameScreen::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    message_handler("quit", nullptr);
}

void QTGameScreen::Show() {
    show();
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

void QTGameScreen::Hide() {
    hide();
}

void QTGameScreen::Close() {
    if (isVisible()) {
        QMainWindow::close();
    }
}

void QTGameScreen::UpdateStats() {
    auto character = game->GetCharacter();
    character_table->setItem(3, 1, new QTableWidgetItem(QString::number(character->Level)));
    stats_table->setItem(0, 1, new QTableWidgetItem(QString::number(character->STR)));
    stats_table->setItem(1, 1, new QTableWidgetItem(QString::number(character->CON)));
    stats_table->setItem(2, 1, new QTableWidgetItem(QString::number(character->DEX)));
    stats_table->setItem(3, 1, new QTableWidgetItem(QString::number(character->INT)));
    stats_table->setItem(4, 1, new QTableWidgetItem(QString::number(character->WIS)));
    stats_table->setItem(5, 1, new QTableWidgetItem(QString::number(character->CHA)));
    stats_table->setItem(6, 1, new QTableWidgetItem(QString::number(character->MAXHP)));
    stats_table->setItem(7, 1, new QTableWidgetItem(QString::number(character->MAXMP)));
    // TODO: real experience level
    experience_progress->setValue(10);
}

void QTGameScreen::UpdateSpells() {
    spells_table->clearContents();
    auto character = game->GetCharacter();
    auto row = 0;
    spells_table->setRowCount(static_cast<int>(character->Spells.size()));
    for (const auto& spell: character->Spells) {
        spells_table->setItem(row, 0, new QTableWidgetItem(spell.name.c_str()));
        // TODO: Get count as roman numerals
        spells_table->setItem(row, 1, new QTableWidgetItem(QString::number(spell.count)));
        row++;
    }
}

void QTGameScreen::UpdateEquipment() {
    auto character = game->GetCharacter();
    auto equipment_index = 0;
    for (const auto& item: character->Equipment) {
        // TODO: proper item name logic
        equipment_table->setItem(equipment_index++, 1, new QTableWidgetItem(item.label.c_str()));
    }
}

void QTGameScreen::UpdateInventory() {
    inventory_table->clearContents();
    auto character = game->GetCharacter();
    auto row = 1;
    inventory_table->setRowCount(static_cast<int>(character->Inventory.size() + 1));
    inventory_table->setItem(0, 0, new QTableWidgetItem("Gold"));
    inventory_table->setItem(0, 1, new QTableWidgetItem(QString::number(character->Gold)));
    for (const auto& item: character->Inventory) {
        inventory_table->setItem(row, 0, new QTableWidgetItem(item.name.c_str()));
        inventory_table->setItem(row, 1, new QTableWidgetItem(QString::number(item.count)));
        row++;
    }
    // TODO: real encumbrance
    encumbrance_progress->setValue(10);
}

void QTGameScreen::UpdatePlot() {
    plot_table->clearContents();
    auto character = game->GetCharacter();
    auto row = 0;
    plot_table->setRowCount(static_cast<int>(character->Plot.size()));
    for (const auto& plot: character->Plot) {
        QCheckBox *check = new QCheckBox(plot.c_str());
        bool checked = row != character->Plot.size() - 1;
        check->setChecked(checked);
        check->setAttribute(Qt::WA_TransparentForMouseEvents);
        check->setFocusPolicy(Qt::NoFocus);
        plot_table->setCellWidget(row, 0, check);
        row++;
    }
    // TODO: real plot progress
    plot_progress->setValue(10);
}

void QTGameScreen::UpdateQuests() {
    quest_table->clearContents();
    auto character = game->GetCharacter();
    auto row = 0;
    quest_table->setRowCount(static_cast<int>(character->Quests.size()));
    for (const auto& quest: character->Quests) {
        QCheckBox *check = new QCheckBox(quest.c_str());
        bool checked = row != character->Quests.size() - 1;
        check->setChecked(checked);
        check->setAttribute(Qt::WA_TransparentForMouseEvents);
        check->setFocusPolicy(Qt::NoFocus);
        quest_table->setCellWidget(row, 0, check);
        row++;
    }
    // TODO: real quest progress
    quest_progress->setValue(10);
}

void QTGameScreen::UpdateStatus() {
    auto character = game->GetCharacter();
    status_label->setText(character->CurrentAction.c_str());
    status_progress->setValue(static_cast<int>(character->CurrentProgress));
}

