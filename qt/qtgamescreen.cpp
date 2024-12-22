//
// Created by nbollom on 19/10/18.
//

#include <QHeaderView>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QCheckBox>
#include <QPropertyAnimation>
#include <utils.hpp>
#include <string>
#include "qtgamescreen.hpp"

#define MARGIN_AMOUNT 0
#define TIMER_MS 100
#define TEN_SECONDS 10000

inline void smooth_update_progress_bar(const uint64_t value, const uint64_t max, QProgressBar *bar) {
    // Increase the value range of progress bars for smoother animation
    const auto max_float = static_cast<float>(max);
    // Due to floating point inaccuracies we might end up overflowing int so make sure limit is safely below the max
    constexpr auto safe_float_max = static_cast<float>(std::numeric_limits<int>::max() - 500);
    const float progress_multiplier = safe_float_max / max_float;
    bar->setMaximum(max_float * progress_multiplier);
    const auto value_float = std::ceil(static_cast<float>(value) * progress_multiplier);
    // ReSharper disable once CppDFAMemoryLeak
    const auto animation = new QPropertyAnimation(bar, "value");
    animation->setDuration(TIMER_MS - 10);
    animation->setStartValue(bar->value());
    animation->setEndValue(static_cast<int>(value_float));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

QTGameScreen::QTGameScreen(const std::shared_ptr<Game>& game, const MessageHandler& message_handler) : View(game, message_handler) {
    std::string title = "ProgressQuest 2 - ";
    QMargins margins(MARGIN_AMOUNT, MARGIN_AMOUNT, MARGIN_AMOUNT, MARGIN_AMOUNT);
    auto character = game->GetCharacter();
    title += character.Name;
    setWindowTitle(title.c_str());
    scroll_area = new QScrollArea();
    scroll_area->setWidgetResizable(true);
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
    character_table->setItem(0, 1, new QTableWidgetItem(character.Name.c_str()));
    character_table->setItem(1, 1, new QTableWidgetItem(character.CharacterRace.name.c_str()));
    character_table->setItem(2, 1, new QTableWidgetItem(character.CharacterClass.name.c_str()));
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
    scroll_area->setWidget(main_widget);
    setCentralWidget(scroll_area);

    timer = new QTimer();
    timer->setTimerType(Qt::PreciseTimer);
    timer->setInterval(TIMER_MS);
    last_update = std::chrono::system_clock::now();
    connect(timer, &QTimer::timeout, this, &QTGameScreen::UpdateAll);
    timer->start();
}

void QTGameScreen::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    message_handler("quit");
}

void QTGameScreen::Show() {
    show();
    move(QApplication::primaryScreen()->geometry().center() - rect().center());
}

void QTGameScreen::Hide() {
    hide();
}

void QTGameScreen::Close() {
    if (isVisible()) {
        close();
    }
}

void QTGameScreen::UpdateStats() const {
    const auto character = game->GetCharacter();
    character_table->setItem(3, 1, new QTableWidgetItem(QString::number(character.Level)));
    stats_table->setItem(0, 1, new QTableWidgetItem(QString::number(character.STR)));
    stats_table->setItem(1, 1, new QTableWidgetItem(QString::number(character.CON)));
    stats_table->setItem(2, 1, new QTableWidgetItem(QString::number(character.DEX)));
    stats_table->setItem(3, 1, new QTableWidgetItem(QString::number(character.INT)));
    stats_table->setItem(4, 1, new QTableWidgetItem(QString::number(character.WIS)));
    stats_table->setItem(5, 1, new QTableWidgetItem(QString::number(character.CHA)));
    stats_table->setItem(6, 1, new QTableWidgetItem(QString::number(character.MAX_HP)));
    stats_table->setItem(7, 1, new QTableWidgetItem(QString::number(character.MAX_MP)));
    const uint64_t max = game->GetLevelUpMaxValue();
    smooth_update_progress_bar(character.Experience, max, experience_progress);
    const uint64_t needed = max - character.Experience;
    const std::string needed_exp = std::to_string(needed) + " XP needed for next level";
    experience_progress->setToolTip(needed_exp.c_str());
}

void QTGameScreen::UpdateSpells() {
    const auto character = game->GetCharacter();
    auto row = 0;
    const auto new_spells_count = static_cast<int>(character.Spells.size());
    spells_table->setRowCount(new_spells_count);
    for (const auto&[name, level]: character.Spells) {
        spells_table->setItem(row, 0, new QTableWidgetItem(name.c_str()));
        std::string level_string = GetRomanNumerals(level);
        spells_table->setItem(row, 1, new QTableWidgetItem(level_string.c_str()));
        row++;
    }
    if (new_spells_count > spell_count) {
        spells_table->scrollToBottom();
    }
    spell_count = new_spells_count;
}

void QTGameScreen::UpdateEquipment() const {
    const auto character = game->GetCharacter();
    auto equipment_index = 0;
    for (const auto& item: character.Equipment) {
        // TODO: proper item name logic
        equipment_table->setItem(equipment_index++, 1, new QTableWidgetItem(item.c_str()));
    }
}

void QTGameScreen::UpdateInventory() {
    auto character = game->GetCharacter();
    auto row = 1;
    const auto new_inventory_count = static_cast<int>(character.Inventory.size() + 1);
    inventory_table->setRowCount(new_inventory_count);
    inventory_table->setItem(0, 0, new QTableWidgetItem("Gold"));
    inventory_table->setItem(0, 1, new QTableWidgetItem(QString::number(character.Gold)));
    for (const auto&[name, count]: character.Inventory) {
        inventory_table->setItem(row, 0, new QTableWidgetItem(name.c_str()));
        inventory_table->setItem(row, 1, new QTableWidgetItem(QString::number(count)));
        row++;
    }
    if (new_inventory_count > inventory_count) {
        inventory_table->scrollToBottom();
    }
    else if (new_inventory_count < inventory_count) {
        inventory_table->scrollToTop();
    }
    inventory_count = new_inventory_count;
    const uint64_t max = game->GetEncumbranceMaxValue();
    const uint64_t value = game->GetEncumbrance();
    smooth_update_progress_bar(value, max, encumbrance_progress);
    const std::string hint = std::to_string(max - value) + " cubits";
    encumbrance_progress->setToolTip(hint.c_str());
}

void QTGameScreen::UpdatePlot() {
    const auto character = game->GetCharacter();
    const auto new_plot_count = static_cast<int>(character.Plot.size());
    // No need to update plot table if count of items hasn't changed since the old one is checked only when new one added
    if (new_plot_count != plot_count) {
        size_t row = 0;
        plot_table->setRowCount(new_plot_count);
        for (const auto& plot: character.Plot) {
            // ReSharper disable once CppDFAMemoryLeak
            auto *check = new QCheckBox(plot.c_str());
            const bool checked = row != character.Plot.size() - 1;
            check->setChecked(checked);
            check->setAttribute(Qt::WA_TransparentForMouseEvents);
            check->setFocusPolicy(Qt::NoFocus);
            plot_table->setCellWidget(static_cast<int>(row), 0, check);
            row++;
        }
        if (new_plot_count > plot_count) {
            plot_table->scrollToBottom();
        }
        plot_count = new_plot_count;
    }
    smooth_update_progress_bar(character.CurrentPlotProgress, game->GetPlotMaxValue(), plot_progress);
}

void QTGameScreen::UpdateQuests() {
    const auto character = game->GetCharacter();
    const auto new_quest_count = static_cast<int>(character.Quests.size());
    bool force_refresh = false;
    if (new_quest_count == quest_count && quest_count != 0) {
        const auto first_item = static_cast<QCheckBox*>(quest_table->cellWidget(0, 0));
        if (character.Quests[0].label != first_item->text().toStdString()) {
            force_refresh = true;
        }
    }
    if (new_quest_count != quest_count || force_refresh) {
        size_t row = 0;
        quest_table->setRowCount(new_quest_count);
        for (const auto&[label, monster]: character.Quests) {
            // ReSharper disable once CppDFAMemoryLeak
            auto *check = new QCheckBox(label.c_str());
            const bool checked = row != character.Quests.size() - 1;
            check->setChecked(checked);
            check->setAttribute(Qt::WA_TransparentForMouseEvents);
            check->setFocusPolicy(Qt::NoFocus);
            quest_table->setCellWidget(static_cast<int>(row), 0, check);
            row++;
        }
        if (new_quest_count > quest_count) {
            quest_table->scrollToBottom();
        }
        quest_count = new_quest_count;
    }
    smooth_update_progress_bar(character.CurrentQuestProgress, character.MaxQuestProgress, quest_progress);
}

void QTGameScreen::UpdateStatus() const {
    const auto character = game->GetCharacter();
    status_label->setText(character.CurrentActionLabel.c_str());
    smooth_update_progress_bar(character.CurrentProgress, character.MaxProgress, status_progress);
}

void QTGameScreen::UpdateAll() {
    const std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time - last_update).count();
    if (elapsed > TEN_SECONDS) {
        // if 10 seconds have passed since last update, the system was either sleeping or badly locked up
        // regardless we should consider that time as dead to avoid cheating by "sleep progressing"
        elapsed = TIMER_MS;
    }
    last_update = time;
    game->Tick(elapsed);
    UpdateStats();
    UpdateSpells();
    UpdateEquipment();
    UpdateInventory();
    UpdatePlot();
    UpdateQuests();
    UpdateStatus();
}

