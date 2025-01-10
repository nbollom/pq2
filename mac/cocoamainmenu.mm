//
// Created by nbollom on 9/10/18.
//

#include "cocoamainmenu.hpp"

@interface MainMenuController : NSWindowController<NSWindowDelegate> {
	CocoaMainMenu *main_menu;
	BOOL closing;
}

- (id) initWithWindow:(NSWindow *)window andView:(CocoaMainMenu*)view;
- (void)windowWillClose:(NSNotification *)notification;
- (void)windowDidResize:(NSNotification *)notification;
- (void)newGame;
- (void)loadGame;
- (void)exitGame;

@end

@implementation MainMenuController

- (id)initWithWindow:(NSWindow *)window andView:(CocoaMainMenu*)view {
	self = [super initWithWindow:window];
	self->main_menu = view;
	self->closing = NO;
	return self;
}

- (void)windowWillClose:(NSNotification *)notification {
	if (!closing) {
		main_menu->Close();
		closing = YES;
	}
}

- (void)windowDidResize:(NSNotification *)notification {
	main_menu->Resize();
}

- (void)newGame {
	main_menu->NewGame();
}

- (void)loadGame {
	main_menu->LoadGame();
}

- (void)exitGame {
	[self close];
}

@end

CocoaMainMenu::CocoaMainMenu(std::shared_ptr<Game> game, const MessageHandler& message_handler) : View(game, message_handler) {
	window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 600, 600) styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable) backing:NSBackingStoreBuffered defer:NO] autorelease];
	[window setMinSize:NSMakeSize(300, 300)];
	[window setShowsResizeIndicator:YES];
	[window setReleasedWhenClosed:NO];
	[window setTitle:@"ProgressQuest 2"];
	controller = [[MainMenuController alloc] initWithWindow:window andView:this];
	[window setDelegate:(MainMenuController*)controller];
	image = [[[NSImage alloc] initWithContentsOfFile:@"../pq.png"] autorelease];
	[window setMiniwindowImage:image];
	content = [[[NSView alloc] init] autorelease];
	logo = [NSImageView imageViewWithImage:image];
	[logo setTranslatesAutoresizingMaskIntoConstraints:YES];
	[logo setImageScaling:NSImageScaleProportionallyUpOrDown];
	[content addSubview:logo];
	new_game = [[NSButton buttonWithTitle:@"New Game" target:controller action:@selector(newGame)] autorelease];
	[new_game setBezelStyle:NSBezelStyleRegularSquare];
	[content addSubview:new_game];
	load_game = [[NSButton buttonWithTitle:@"Load Game" target:controller action:@selector(loadGame)] autorelease];
	[load_game setBezelStyle:NSBezelStyleRegularSquare];
	[content addSubview:load_game];
	exit = [[NSButton buttonWithTitle:@"Exit" target:controller action:@selector(exitGame)] autorelease];
	[exit setBezelStyle:NSBezelStyleRegularSquare];
	[content addSubview:exit];
	[window setContentView:content];
	[window center];
	Resize();
}

CocoaMainMenu::~CocoaMainMenu() = default;

void CocoaMainMenu::Show() {
	[controller showWindow:window];
	[window setIsVisible:YES];
	[window makeKeyWindow];
	[window orderFront:controller];
}

void CocoaMainMenu::Hide() {
	[window setIsVisible:NO];
}

void CocoaMainMenu::Close() {
	if ([window isVisible]) {
		message_handler("quit");
	}
}

void CocoaMainMenu::NewGame() {
    message_handler("new");
}

void CocoaMainMenu::LoadGame() {
	NSOpenPanel* openDlg = [NSOpenPanel openPanel];
	[openDlg setCanChooseFiles:YES];
	[openDlg setAllowsMultipleSelection:NO];
	[openDlg setCanChooseDirectories:NO];
	if ([openDlg runModal] == NSModalResponseOK) {
		NSArray* urls = [openDlg URLs];
		for (NSUInteger i = 0; i < [urls count]; i++)
		{
			NSURL* url = [urls objectAtIndex:i];
			NSLog(@"Url: %@", url);
			dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0), dispatch_get_main_queue(), ^{
				if (game->LoadGame(url.fileSystemRepresentation) == file::LoadErrorNone) {
					message_handler("start");
				}
				else {
					NSAlert *alert = [[[NSAlert alloc] init] autorelease];
					[alert setMessageText:@"Failed to load game"];
					[alert setAlertStyle:NSAlertStyleCritical];
					[alert setIcon:image];
					[alert addButtonWithTitle:@"OK"];
					[alert runModal];
				}
			});
			break;
		}
	}
}

void CocoaMainMenu::Resize() {
	NSSize content_size = content.frame.size;
	CGFloat image_size = content_size.height / 2;
	CGFloat button_size = image_size / 4;
	CGFloat gap = (content_size.height - image_size - button_size * 3) / 4;
	
	[logo setFrame:NSMakeRect(0, content_size.height - image_size, content_size.width, image_size)];
	[new_game setFrame:NSMakeRect(20, content_size.height - image_size - button_size - gap, content_size.width - 40, button_size)];
	[load_game setFrame:NSMakeRect(20, content_size.height - image_size - button_size * 2 - gap * 2, content_size.width - 40, button_size)];
	[exit setFrame:NSMakeRect(20, content_size.height - image_size - button_size * 3 - gap * 3, content_size.width - 40, button_size)];
}
