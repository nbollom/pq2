//
// Created by nbollom on 9/10/18.
//

#ifndef PQ2_COCOAMAINMENU_H
#define PQ2_COCOAMAINMENU_H

#include <view.hpp>
#import <Cocoa/Cocoa.h>

class CocoaMainMenu : public View {

private:
	NSWindowController *controller;
	NSWindow *window;
	NSView *content;
	NSImage *image;
	NSImageView *logo;
	NSButton *new_game;
	NSButton *load_game;
	NSButton *exit;

public:
    CocoaMainMenu(std::shared_ptr<Game> game, const MessageHandler& message_handler);
    virtual ~CocoaMainMenu();

    void Show() override;
    void Hide() override;
    void NewGame();
    void LoadGame();
    void Close() override;
	void Resize();

};

#endif //PQ2_COCOAMAINMENU_H
