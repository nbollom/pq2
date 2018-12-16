//
// Created by nbollom on 12/12/18.
//

#include "pq2cocoa.h"
#include "cocoamainmenu.h"

#import <Cocoa/Cocoa.h>

NSAutoreleasePool *pool;

CocoaGUI::CocoaGUI(std::shared_ptr<Game> game) : GUI(game) {
	message_handler = std::bind(&CocoaGUI::HandleMessage, this, std::placeholders::_1, std::placeholders::_2);
	pool = [[NSAutoreleasePool alloc] init];
	[NSApplication sharedApplication];
}

CocoaGUI::~CocoaGUI() {
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

