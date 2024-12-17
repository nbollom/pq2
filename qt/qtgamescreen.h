//
// Created by nbollom on 19/10/18.
//

#ifndef PQ2_QTGAMESCREEN_H
#define PQ2_QTGAMESCREEN_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QTableWidget>
#include <QProgressBar>
#include <QTimer>
#include "view.h"

class QTGameScreen : public QMainWindow, public View {
Q_OBJECT

private:
    QWidget *main_widget;
    QVBoxLayout *main_vlayout;
    QHBoxLayout *columns_hlayout;
    QVBoxLayout *col1_layout;
    QGroupBox *character_group;
    QVBoxLayout *character_layout;
    QTableWidget *character_table;
    QTableWidget *stats_table;
    QLabel *experience_label;
    QProgressBar *experience_progress;
    QGroupBox *spells_group;
    QVBoxLayout *spells_layout;
    QTableWidget *spells_table;
    QVBoxLayout *col2_layout;
    QGroupBox *equipment_group;
    QVBoxLayout *equipment_layout;
    QTableWidget *equipment_table;
    QGroupBox *inventory_group;
    QVBoxLayout *inventory_layout;
    QTableWidget *inventory_table;
    QLabel *encumbrance_label;
    QProgressBar *encumbrance_progress;
    QVBoxLayout *col3_layout;
    QGroupBox *plot_group;
    QVBoxLayout *plot_layout;
    QTableWidget *plot_table;
    QProgressBar *plot_progress;
    QGroupBox *quest_group;
    QVBoxLayout *quest_layout;
    QTableWidget *quest_table;
    QProgressBar *quest_progress;
    QLabel *status_label;
    QProgressBar *status_progress;

    QTimer *timer;

public:
    QTGameScreen(const std::shared_ptr<Game>& game, const std::function<void(std::string, void*)>& message_handler);
    ~QTGameScreen() override = default;

    void closeEvent(QCloseEvent *event) override;

    void Show() override;
    void Hide() override;

public slots:
    void Close() override;

    void UpdateStats() const;
    void UpdateSpells() const;
    void UpdateEquipment() const;
    void UpdateInventory() const;
    void UpdatePlot() const;
    void UpdateQuests() const;
    void UpdateStatus() const;
    void UpdateAll() const;
};

#endif //PQ2_QTGAMESCREEN_H
