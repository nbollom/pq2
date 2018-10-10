//
// Created by nbollom on 9/10/18.
//

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
    new_game = new QPushButton("New Game");
    new_game->setMinimumSize(300, 100);
    load_game = new QPushButton("Load Game");
    load_game->setMinimumSize(300, 100);
    exit_game = new QPushButton("Exit");
    exit_game->setMinimumSize(300, 100);
    main_layout->addStretch();
    main_layout->addWidget(new_game);
    main_layout->addWidget(load_game);
    main_layout->addWidget(exit_game);
    main_layout->addStretch();
    main_widget->setLayout(main_layout);
    setCentralWidget(main_widget);
    connect(exit_game, SIGNAL(clicked()), this, SLOT(Close()));
}

QTMainMenu::~QTMainMenu() {

}

void QTMainMenu::Show() {
    this->show();
}

void QTMainMenu::Hide() {
    this->hide();
}

void QTMainMenu::Close() {
    if (isVisible()) {
        this->close();
    }
}

void QTMainMenu::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    message_handler("quit", nullptr);
}
