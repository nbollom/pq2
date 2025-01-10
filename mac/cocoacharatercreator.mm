//
// Created by nbollom on 17/12/18.
//

#include <algorithm>
#include "cocoacharatercreator.hpp"

@interface CharacterCreatorController : NSWindowController<NSWindowDelegate> {
	CocoaCharacterCreator *character_creator;
	BOOL closing;
}

- (id) initWithWindow:(NSWindow *)window andView:(CocoaCharacterCreator*)view;
- (void)windowWillClose:(NSNotification *)notification;
- (void)windowDidResize:(NSNotification *)notification;
- (void)GenRandomName;

@end

@implementation CharacterCreatorController

- (id)initWithWindow:(NSWindow *)window andView:(CocoaCharacterCreator*)view {
	self = [super initWithWindow:window];
	self->character_creator = view;
	self->closing = NO;
	return self;
}

- (void)windowWillClose:(NSNotification *)notification {
	if (!closing) {
		character_creator->Close();
		closing = YES;
	}
}

- (void)windowDidResize:(NSNotification *)notification {
	character_creator->Resize();
}

- (void)GenRandomName {
    character_creator->GenRandomName();
}

@end

CocoaCharacterCreator::CocoaCharacterCreator(std::shared_ptr<Game> game, const MessageHandler& message_handler) : View(game, message_handler) {
    new_game = game->StartNewGame();
	window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 1200, 800) styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable) backing:NSBackingStoreBuffered defer:NO] autorelease];
	[window setMinSize:NSMakeSize(300, 300)];
	[window setShowsResizeIndicator:YES];
	[window setReleasedWhenClosed:NO];
	[window setTitle:@"ProgressQuest 2 - Create New Character"];
	controller = [[CharacterCreatorController alloc] initWithWindow:window andView:this];
	[window setDelegate:(CharacterCreatorController*)controller];
	image = [[[NSImage alloc] initWithContentsOfFile:@"../pq.png"] autorelease];
	[window setMiniwindowImage:image];
	content = [[[NSView alloc] init] autorelease];
	name_section = [[[NSView alloc] init] autorelease];
	[content addSubview:name_section];
	name_label = [[[NSTextView alloc] init] autorelease];
	[name_label setEditable:NO];
	[name_label setDrawsBackground:NO];
	[name_label setString:@"Name:"];
	[name_section addSubview:name_label];
    name_text = [[[NSTextView alloc] init] autorelease];
    [name_text setEditable:YES];
    [name_text setDrawsBackground:YES];
    [name_text setString:[NSString stringWithCString:new_game->GetName().c_str() encoding:NSASCIIStringEncoding]];
	[name_section addSubview:name_text];
    name_randomiser = [NSButton buttonWithTitle:@"?" target:controller action:@selector(GenRandomName)];
    [name_randomiser setBezelStyle:NSBezelStyleRegularSquare];
	[name_section addSubview:name_randomiser];
	middle_section = [[[NSView alloc] init] autorelease];
	[content addSubview:middle_section];
	left_column = [[[NSView alloc] init] autorelease];
	centre_column = [[[NSView alloc] init] autorelease];
	right_column = [[[NSView alloc] init] autorelease];
	[middle_section addSubview:left_column];
	[middle_section addSubview:centre_column];
	[middle_section addSubview:right_column];
//    main_widget = new QWidget;
//    vlayout = new QVBoxLayout;
//    name_layout = new QHBoxLayout;
//    name_label = new QLabel("Name");
//    std::string name = new_game->GetName();
//    name_text = new QLineEdit(name.c_str());
//    name_randomiser = new QPushButton("?");
//    hlayout = new QHBoxLayout;
//    race_group = new QGroupBox("Race");
//    race_group->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
//    race_layout = new QVBoxLayout;
//    race_options = new QButtonGroup;
//    std::string selected_race = new_game->GetRace();
//    for (auto &race_name: new_game->GetAvailableRaces()) {
//        QRadioButton *race_option = new QRadioButton(race_name.c_str());
//        race_options->addButton(race_option);
//        race_layout->addWidget(race_option);
//        if (selected_race == race_name) {
//            race_option->setChecked(true);
//        }
//    }
//    class_group = new QGroupBox("Class");
//    class_group->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
//    class_layout = new QVBoxLayout;
//    class_options = new QButtonGroup;
//    std::string selected_class = new_game->GetClass();
//    for (auto &class_name: new_game->GetAvailableClasses()) {
//        QRadioButton *class_option = new QRadioButton(class_name.c_str());
//        class_options->addButton(class_option);
//        class_layout->addWidget(class_option);
//        if (selected_class == class_name) {
//            class_option->setChecked(true);
//        }
//    }
//    stats_group = new QGroupBox("Stats");
//    stats_group->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
//    stats_layout = new QGridLayout;
//    str_label = new QLabel("STR");
//    str_text = new QLineEdit;
//    str_text->setReadOnly(true);
//    con_label = new QLabel("CON");
//    con_text = new QLineEdit;
//    con_text->setReadOnly(true);
//    dex_label = new QLabel("DEX");
//    dex_text = new QLineEdit;
//    dex_text->setReadOnly(true);
//    int_label = new QLabel("INT");
//    int_text = new QLineEdit;
//    int_text->setReadOnly(true);
//    wis_label = new QLabel("WIS");
//    wis_text = new QLineEdit;
//    wis_text->setReadOnly(true);
//    cha_label = new QLabel("CHA");
//    cha_text = new QLineEdit;
//    cha_text->setReadOnly(true);
//    total_label = new QLabel("Total");
//    total_text = new QLineEdit;
//    total_text->setReadOnly(true);
//    roll_button = new QPushButton("Roll");
//    unroll_button = new QPushButton("Unroll");
//    button_layout = new QHBoxLayout;
//    start_button = new QPushButton("Sold!");
//    name_layout->addWidget(name_label);
//    name_layout->addWidget(name_text);
//    name_layout->addWidget(name_randomiser);
//    name_layout->addStretch();
//    vlayout->addLayout(name_layout);
//    race_layout->addStretch();
//    race_group->setLayout(race_layout);
//    hlayout->addWidget(race_group);
//    class_layout->addStretch();
//    class_group->setLayout((class_layout));
//    hlayout->addWidget(class_group);
//    stats_layout->addWidget(str_label, 0, 0);
//    stats_layout->addWidget(str_text, 0, 1);
//    stats_layout->addWidget(con_label, 1, 0);
//    stats_layout->addWidget(con_text, 1, 1);
//    stats_layout->addWidget(dex_label, 2, 0);
//    stats_layout->addWidget(dex_text, 2, 1);
//    stats_layout->addWidget(int_label, 3, 0);
//    stats_layout->addWidget(int_text, 3, 1);
//    stats_layout->addWidget(wis_label, 4, 0);
//    stats_layout->addWidget(wis_text, 4, 1);
//    stats_layout->addWidget(cha_label, 5, 0);
//    stats_layout->addWidget(cha_text, 5, 1);
//    stats_layout->setRowStretch(6, 1);
//    stats_layout->addWidget(total_label, 7, 0);
//    stats_layout->addWidget(total_text, 7, 1);
//    stats_layout->addWidget(roll_button, 8, 0, 1, 2);
//    stats_layout->addWidget(unroll_button, 9, 0, 1, 2);
//    stats_layout->setRowStretch(10, 10);
//    stats_group->setLayout(stats_layout);
//    hlayout->addWidget(stats_group);
//    vlayout->addLayout(hlayout);
//    button_layout->addStretch();
//    button_layout->addWidget(start_button);
//    vlayout->addLayout(button_layout);
//    main_widget->setLayout(vlayout);
//    setCentralWidget(main_widget);
//    connect(name_randomiser, &QPushButton::clicked, this, &QTCharacterCreator::GenRandomName);
//    connect(race_options, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &QTCharacterCreator::RaceButtonClicked);
//    connect(class_options, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &QTCharacterCreator::ClassButtonClicked);
//    connect(roll_button, &QPushButton::clicked, this, &QTCharacterCreator::RollStats);
//    connect(unroll_button, &QPushButton::clicked, this, &QTCharacterCreator::UnrollStats);
//    connect(start_button, &QPushButton::clicked, this, &QTCharacterCreator::Start);
//    UpdateStats();
	[window setContentView:content];
	[window center];
	Resize();
	closing = false;
}

CocoaCharacterCreator::~CocoaCharacterCreator() = default;

void CocoaCharacterCreator::Show() {
	[controller showWindow:window];
	[window setIsVisible:YES];
	[window makeKeyWindow];
}

void CocoaCharacterCreator::Hide() {
	[window setIsVisible:NO];
}

void CocoaCharacterCreator::Close() {
	if (!closing) {
		closing = true;
		message_handler("cancel");
	}
}

void CocoaCharacterCreator::GenRandomName() {
    new_game->GenerateName();
    std::string name = new_game->GetName();
    [name_text setString:[NSString stringWithCString:name.c_str() encoding:NSASCIIStringEncoding] ];
}

void CocoaCharacterCreator::RaceButtonClicked() {
//    new_game->SetRace(StripShortcuts(button->text()));
}

void CocoaCharacterCreator::ClassButtonClicked() {
//    new_game->SetClass(StripShortcuts(button->text()));
}

void CocoaCharacterCreator::RollStats() {
    new_game->ReRoll();
    UpdateStats();
}

void CocoaCharacterCreator::UnrollStats() {
    new_game->UnRoll();
    UpdateStats();
}

void CocoaCharacterCreator::Start() {
//    new_game->SetName(name_text->text().toStdString());
    new_game->ConfirmCharacter();
    message_handler("start");
}

void CocoaCharacterCreator::UpdateStats() {
//    str_text->setText(StringValue(new_game->GetSTR()));
//    con_text->setText(StringValue(new_game->GetCON()));
//    dex_text->setText(StringValue(new_game->GetDEX()));
//    int_text->setText(StringValue(new_game->GetINT()));
//    wis_text->setText(StringValue(new_game->GetWIS()));
//    cha_text->setText(StringValue(new_game->GetCHA()));
//    total_text->setText(StringValue(new_game->GetTotal()));
//    switch (new_game->GetTotalColor()) {
//        case ui::ColorRed:
//            total_text->setStyleSheet("background:#FF0000;");
//            break;
//        case ui::ColorYellow:
//            total_text->setStyleSheet("background:#FFFF00;");
//            break;
//        case ui::ColorGray:
//            total_text->setStyleSheet("background:#808080;");
//            break;
//        case ui::ColorSilver:
//            total_text->setStyleSheet("background:#C0C0C0;");
//            break;
//        default:
//            total_text->setStyleSheet("background:#FFFFFF;");
//    }
}

void CocoaCharacterCreator::Resize() {
	NSSize content_size = content.frame.size;
	[name_section setFrame:NSMakeRect(0, content_size.height - 50, content_size.width, 50)];
	[name_label setFrame:NSMakeRect(0, 0, 100, 20)];
    [name_text setFrame:NSMakeRect(100, 0, name_section.frame.size.width - 200, 20)];
    [name_randomiser setFrame:NSMakeRect(name_section.frame.size.width - 100, 0, 100, 20)];
//	middle_section setFrame:NSMakeRect(content_size., <#CGFloat y#>, <#CGFloat w#>, <#CGFloat h#>)
}

