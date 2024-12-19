//
// Created by nbollom on 9/10/18.
//

#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>
#include <iostream>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include "qtmainmenu.h"

#define MARGIN 20
#define MARGINS MARGIN, MARGIN, MARGIN, MARGIN

QTMainMenu::QTMainMenu(const std::shared_ptr<Game>& game, const std::function<void(std::string, void*)> &message_handler) : View(game, message_handler) {
    setGeometry(0, 0, 800, 600);
    setWindowTitle("Progress Quest 2");
    main_widget = new QWidget;
    main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(20, 20, 20, 20);
    main_layout->setSpacing(10);
    logo = new QLabel;
    logo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    logo->setAlignment(Qt::AlignCenter);
    logo->setMinimumSize(200, 200);
    const QImage newImage(":/resources/pq.png");
    logo_image = QPixmap::fromImage(newImage);
    new_game = new QPushButton("New Game");
    new_game->setMinimumSize(200, 60);
    load_game = new QPushButton("Load Game");
    load_game->setMinimumSize(200, 60);
    exit_game = new QPushButton("Exit");
    exit_game->setMinimumSize(200, 60);
    main_layout->addWidget(logo);
    main_layout->addWidget(new_game);
    main_layout->addWidget(load_game);
    main_layout->addWidget(exit_game);
    main_widget->setLayout(main_layout);
    setCentralWidget(main_widget);
    connect(new_game, SIGNAL(clicked()), this, SLOT(NewGame()));
    connect(load_game, SIGNAL(clicked()), this, SLOT(LoadGame()));
    connect(exit_game, SIGNAL(clicked()), this, SLOT(Close()));
    ResizeLogo();
}

QTMainMenu::~QTMainMenu() = default;

void QTMainMenu::Show() {
    show();
    move(QApplication::primaryScreen()->geometry().center() - rect().center());
    ResizeLogo();
}

void QTMainMenu::Hide() {
    hide();
}

void QTMainMenu::Close() {
    if (isVisible()) {
        close();
    }
}

void QTMainMenu::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    ResizeLogo();
}

void QTMainMenu::ResizeLogo() const {
    const int height = logo->height();
    const int width = logo->width();
    logo->setPixmap(logo_image.scaled(width, height, Qt::KeepAspectRatio));
}


void QTMainMenu::NewGame() const {
    message_handler("new", nullptr);
}

void QTMainMenu::LoadGame() const {
    QFileDialog dialog(nullptr, "Please select a pq2 save file", "", "PQ2 saves (*.pq2)");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    if (dialog.exec()) {
        const QString filename = dialog.selectedFiles()[0];
        if (const file::LoadError error = game->LoadGame(filename.toStdString()); error == file::LoadErrorNone) {
            message_handler("load", nullptr);
        }
        else {
            QMessageBox error_message;
            error_message.setText("Error loading game");
            error_message.setIcon(QMessageBox::Critical);
            error_message.exec();
        }
    }
}

void QTMainMenu::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    message_handler("quit", nullptr);
}
