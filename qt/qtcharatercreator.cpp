//
// Created by nbollom on 12/10/18.
//

#include "qtcharatercreator.h"

QTCharacterCreator::QTCharacterCreator(std::shared_ptr<Game> game, std::function<void(std::string, void *)> message_handler) : View(game, message_handler) {
    main_widget = new QWidget;
    vlayout = new QVBoxLayout;
    name_label = new QLabel("Name");
    name_text = new QLineEdit;
    name_randomiser = new QPushButton("?");
    hlayout = new QHBoxLayout;
}

QTCharacterCreator::~QTCharacterCreator() {

}

void QTCharacterCreator::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
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

