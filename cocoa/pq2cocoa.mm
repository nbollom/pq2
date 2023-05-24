//
// Created by nbollom on 12/12/18.
//

#include "pq2cocoa.h"
#include "cocoamainmenu.h"
#include "cocoacharatercreator.h"

#import <Cocoa/Cocoa.h>

bool running = true;

@interface AppDelegate : NSObject<NSApplicationDelegate> {
	CocoaGUI *gui;
}

- (id) initWithGui:(CocoaGUI*)gui;
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender;

@end

@implementation AppDelegate

- (id)initWithGui:(CocoaGUI *)gui {
	self = [super init];
	self->gui = gui;
	return self;
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender {
	if (running) {
		return NSTerminateCancel;
	}
	else {
		return NSTerminateNow;
	}
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
	return NO;
}

@end

NSAutoreleasePool *pool;
AppDelegate *delegate;

CocoaGUI::CocoaGUI(std::shared_ptr<Game> game) : GUI(game) {
	message_handler = std::bind(&CocoaGUI::HandleMessage, this, std::placeholders::_1, std::placeholders::_2);
	pool = [[NSAutoreleasePool alloc] init];
	[NSApplication sharedApplication];
	delegate = [[AppDelegate alloc] init];
	[NSApp setDelegate:delegate];
}

CocoaGUI::~CocoaGUI() {
	[delegate release];
	[pool drain];
}

void CocoaGUI::Run() {
	GUI::Run();
	[NSApp run];
}

void CocoaGUI::ShowMainMenu() {
	std::shared_ptr<View> main_menu = std::make_shared<CocoaMainMenu>(game, message_handler);
	main_menu->Show();
	PushView(main_menu);
}

void CocoaGUI::ShowCharacterCreator() {
	std::shared_ptr<View> character_creator = std::make_shared<CocoaCharacterCreator>(game, message_handler);
	character_creator->Show();
	PushView(character_creator);
}

void CocoaGUI::ShowGameScreen() {

}

void CocoaGUI::Close() {
	[NSApp terminate:[NSNull null]];
	PopAllViews();
	game->Close();
}

void CocoaGUI::HandleMessage(std::string message, void *data) {
	if (message == "quit") {
		// Don't close if there is nothing on the stack like when we pop all views to replace them with the game screen
		if (!view_stack.empty()) {
			running = false;
			Close();
		}
	}
	else if (message == "new") {
		ShowCharacterCreator();
	}
	else if (message == "cancel") {
		PopView();
	}
	else if (message == "start") {
		PopAllViews();
		ShowGameScreen();
	}
}

