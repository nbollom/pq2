#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include "utils.hpp"
#include "game.hpp"
#include "pq2gui.hpp"

#ifdef QT_ENABLED
#include <pq2qt.hpp>
#endif //QT_ENABLED
#ifdef GTK_ENABLED
#include <pq2gtk.hpp>
#endif //GTK_ENABLED
#ifdef COCOA_ENABLED
#include <pq2mac.hpp>
#endif //COCOA_ENABLED
#ifdef WINFORMS_ENABLED
// #include <pq2win.hpp>
#endif //WINFORMS_ENABLED
#ifdef NCURSES_ENABLED
#include <pq2ncurses.hpp>
#endif //NCURSES_ENABLED

using namespace std;

int main(const int argc, const char * const *argv) {
    string filename;
    CommandLineProcessor cmdProcessor("Progress Quest 2 - The Progression", "A streamlined RPG experience", "2025.0");
    try {
        cmdProcessor.AddValueOnlyOption("savefile", "Load the saved game (optional unless run in daemon mode)");
        if (cmdProcessor.Parse(argc, argv) == false) {
            return 0;
        }
        filename = cmdProcessor.GetValueOnlyOptionValue("savefile");
    }
    catch (BaseOptionExistsException &ex) {
        cerr << ex.what() << endl;
        cerr << ex.GetConflictMessage() << endl;
        return 1;
    }
    catch (ParseException &ex) {
        cerr << ex.what() << endl;
        cerr << ex.GetExceptionMessage() << endl;
        return 1;
    }
    catch (CommandLineException &ex) {
        cerr << "Unknown error: " << ex.what() << endl;
        return 1;
    }
    auto game = make_shared<Game>();
    if (!filename.empty()) {
        if (const file::LoadError error = game->LoadGame(filename); error != file::LoadErrorNone) {
            cout << "Error loading save " << filename << endl;
            return 1;
        }
    }
    unique_ptr<GUI> g;
#ifdef QT_ENABLED
    g = make_unique<QTGUI>(game);
#endif //QT_ENABLED
#ifdef GTK_ENABLED
    g = make_unique<GTKGUI>(game);
#endif //GTK_ENABLED
#ifdef COCOA_ENABLED
    g = make_unique<MacGUI>(game);
#endif //COCOA_ENABLED
#ifdef WINFORMS_ENABLED
     // g = make_unique<WinformsGUI>(game);
#endif //WINFORMS_ENABLED
#ifdef NCURSES_ENABLED
    g = make_unique<NCursesGUI>(game);
#endif //NCURSES_ENABLED
    g->Run();
    g.reset();

    return 0;
}
