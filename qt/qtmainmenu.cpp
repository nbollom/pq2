//
// Created by nbollom on 9/10/18.
//

#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>
#include <iostream>
#include "qtmainmenu.h"

#define MARGIN 20
#define MARGINS MARGIN, MARGIN, MARGIN, MARGIN

QTMainMenu::QTMainMenu(std::shared_ptr<Game> game, std::function<void(std::string, void*)> message_handler) : View(game, message_handler) {
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
    QImage newImage(":/resources/pq.png");
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

QTMainMenu::~QTMainMenu() {

}

void QTMainMenu::Show() {
    QMainWindow::show();
    ResizeLogo();
}

void QTMainMenu::Hide() {
    QMainWindow::hide();
}

void QTMainMenu::Close() {
    if (isVisible()) {
        QMainWindow::close();
    }
}

void QTMainMenu::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    ResizeLogo();
}

void QTMainMenu::ResizeLogo() {
    int height = logo->height();
    int width = logo->width();
    logo->setPixmap(logo_image.scaled(width, height, Qt::KeepAspectRatio));
}


void QTMainMenu::NewGame() {
    message_handler("new", nullptr);
}

void QTMainMenu::LoadGame() {
    QFileDialog dialog(nullptr, "Please select a pq2 save file", "", "PQ2 saves (*.pq2)");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    if (dialog.exec()) {
        QString filename = dialog.selectedFiles()[0];
        file::LoadError error = game->LoadGame(filename.toStdString());
        if (error == file::LoadErrorNone) {
            // TODO: show game screen
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
