//
// Created by nbollom on 12/12/18.
//

#include "pq2mac.hpp"
#include "cocoamainmenu.hpp"
#include "cocoacharatercreator.hpp"

#import <Cocoa/Cocoa.h>

bool running = true;

@interface AppDelegate : NSObject<NSApplicationDelegate> {
	MacGUI *mac_gui;
}

- (id) initWithGui:(MacGUI*)gui;
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender;

@end

@implementation AppDelegate

- (id)initWithGui:(MacGUI *)gui {
	self = [super init];
	self->mac_gui = gui;
	return self;
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender {
	if (running) {
        mac_gui->HandleMessage("quit");
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

MacGUI::MacGUI(std::shared_ptr<Game> game) : GUI(game) {
	message_handler = std::bind(&MacGUI::HandleMessage, this, std::placeholders::_1);
	pool = [[NSAutoreleasePool alloc] init];
	[NSApplication sharedApplication];
    delegate = [[AppDelegate alloc] initWithGui:this];
	[NSApp setDelegate:delegate];
    id menu_bar = [[[NSMenu alloc] init] autorelease];
    id appMenuItem = [[NSMenuItem new] autorelease];
    [menu_bar addItem:appMenuItem];
    [NSApp setMainMenu:menu_bar];
    id appMenu = [[NSMenu new] autorelease];
    id quit_item = [[[NSMenuItem alloc] initWithTitle:@"Quit PQ2" action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
    [appMenu addItem:quit_item];
    [appMenuItem setSubmenu:appMenu];
}

MacGUI::~MacGUI() {
	[delegate release];
	[pool drain];
}

void MacGUI::Run() {
	GUI::Run();
	[NSApp run];
}

void MacGUI::ShowMainMenu() {
	std::shared_ptr<View> main_menu = std::make_shared<CocoaMainMenu>(game, message_handler);
	main_menu->Show();
	PushView(main_menu);
}

void MacGUI::ShowCharacterCreator() {
	std::shared_ptr<View> character_creator = std::make_shared<CocoaCharacterCreator>(game, message_handler);
	character_creator->Show();
	PushView(character_creator);
}

void MacGUI::ShowGameScreen() {

}

void MacGUI::Close() {
	[NSApp terminate:[NSNull null]];
	PopAllViews();
	game->Close();
}

void MacGUI::HandleMessage(std::string message) {
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

