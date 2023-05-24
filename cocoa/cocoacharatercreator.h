//
// Created by nbollom on 17/12/18.
//

#ifndef PQ2_CHARATERCREATOR_H
#define PQ2_CHARATERCREATOR_H

#include "view.h"
#include "newgame.h"
#import <Cocoa/Cocoa.h>

class CocoaCharacterCreator : public View {

private:
	NSWindowController *controller;
	NSWindow *window;
	NSImage *image;
	NSView *content;
	NSView *name_section;
	NSTextView *name_label;
	NSTextView *name_text;
	NSButton *name_randomiser;
	NSView *middle_section;
	NSView *left_column;
	NSView *centre_column;
	NSView *right_column;
	
//    QVBoxLayout *vlayout;
//    QHBoxLayout *name_layout;
//    QLabel *name_label;
//    QLineEdit *name_text;
//    QPushButton *name_randomiser;
//    QHBoxLayout *hlayout;
//    QGroupBox *race_group;
//    QVBoxLayout *race_layout;
//    QButtonGroup *race_options;
//    QGroupBox *class_group;
//    QVBoxLayout *class_layout;
//    QButtonGroup *class_options;
//    QGroupBox *stats_group;
//    QGridLayout *stats_layout;
//    QLabel *str_label;
//    QLineEdit *str_text;
//    QLabel *con_label;
//    QLineEdit *con_text;
//    QLabel *dex_label;
//    QLineEdit *dex_text;
//    QLabel *int_label;
//    QLineEdit *int_text;
//    QLabel *wis_label;
//    QLineEdit *wis_text;
//    QLabel *cha_label;
//    QLineEdit *cha_text;
//    QLabel *total_label;
//    QLineEdit *total_text;
//    QPushButton *roll_button;
//    QPushButton *unroll_button;
//    QHBoxLayout *button_layout;
//    QPushButton *start_button;
	bool closing;

    std::shared_ptr<NewGame> new_game;

    void UpdateStats();

public:
    CocoaCharacterCreator(std::shared_ptr<Game> game, std::function<void(std::string, void*)> message_handler);
    virtual ~CocoaCharacterCreator();

    void Show() override;
    void Hide() override;

    void GenRandomName();
    void RaceButtonClicked();
    void ClassButtonClicked();
    void RollStats();
    void UnrollStats();
    void Start();
    void Close() override;
	void Resize();

};

#endif //PQ2_CHARATERCREATOR_H
