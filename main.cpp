#include <iostream>
#include <memory>
#include <stdlib.h>
#include "config.h"
#include "commandline.h"
#include "game/game.h"

using namespace std;

int main(int argc, const char * const *argv) {
    bool runWebServer = false;
    int port = 8094;
    string filename = "";
    int gui = DEFAULT_GUI_LIBRARY;
    CommandLineProcessor cmdProcessor("Progress Quest 2 - The Progression", "A streamlined RPG experience", VERSION);
    try {
        cmdProcessor.AddOption('d', "daemon", "Run as a daemon", false);
#ifdef QT_ENABLED
        cmdProcessor.AddOption('q', "qt", "Run QT interface", false);
#endif
#ifdef GTK_ENABLED
        cmdProcessor.AddOption('g', "gtk", "Run GTK interface", false);
#endif
#ifdef COCOA_ENABLED
        cmdProcessor.AddOption('c', "cocoa", "Run Cocoa(Mac OS X) interface", false);
#endif
#ifdef WINFORMS_ENABLED
        cmdProcessor.AddOption('w', "winforms", "Run Winforms(Windows) interface", false);
#endif
#ifdef NCURSES_ENABLED
        cmdProcessor.AddOption('n', "ncurses", "Run NCurses(console) interface", false);
#endif
#ifdef WEBSERVER_ENABLED
        cmdProcessor.AddOption('s', "webserver", "Run web server", true, "The port to run the webserver on (default 8094)", "8094");
#endif
        cmdProcessor.AddValueOnlyOption("Filename", "Load a saved game");
        cmdProcessor.Parse(argc, argv);
        if (cmdProcessor.IsSet('d')) {
            gui = GUI_NONE;
        }
        if (cmdProcessor.IsSet('n')) {
            gui = GUI_NCURSES;
        }
        if (cmdProcessor.IsSet('g')) {
            gui = GUI_GTK;
        }
        if (cmdProcessor.IsSet('q')) {
            gui = GUI_QT;
        }
        if (cmdProcessor.IsSet('c')) {
            gui = GUI_COCOA;
        }
        if (cmdProcessor.IsSet('w')) {
            gui = GUI_WINFORMS;
        }
        if (cmdProcessor.IsSet('s')) {
            runWebServer = true;
            port = atoi(cmdProcessor.GetOptionValue('s').c_str());
        }
        filename = cmdProcessor.GetValueOnlyOptionValue("Filename");
    }
    catch (BaseOptionExistsException *ex) {
        cerr << ex->what() << endl;
        cerr << ex->GetConflictMessage() << endl;
        return 1;
    }
    catch (ParseException *ex) {
        cerr << ex->what() << endl;
        cerr << ex->GetExceptionMessage() << endl;
        return 1;
    }
    catch (CommandLineException *ex) {
        cerr << "Unknown error: " << ex->what() << endl;
        return 1;
    }
    if (gui == GUI_NONE) {
        cout << "Running in daemon mode" << endl;
    }
    else {
        cout << "Running with " << MODE_NAME[gui] << " gui mode" << endl;
    }
    if (runWebServer) {
        cout << "Running webserver on port " << port << endl;
    }
    Game *g = new Game();
    for (int i = 0; i < 10; ++i) {
        g->StartNewGame();
    }
    return 0;
}
