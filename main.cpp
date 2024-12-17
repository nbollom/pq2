#include <iostream>
#include <memory>
#include <thread>
#include "config.h"
#include "utils.h"
#include "game.h"

#ifdef GUI_ENABLED
#include "pq2gui.h"
#ifdef QT_ENABLED
#include "pq2qt.h"
#endif //QT_ENABLED
#ifdef GTK_ENABLED
// #include "pq2gtk.h"
#endif //GTK_ENABLED
#ifdef COCOA_ENABLED
// #include "pq2cocoa.h"
#endif //COCOA_ENABLED
#ifdef WINFORMS_ENABLED
// #include "pq2winforms.h"
#endif //WINFORMS_ENABLED
#ifdef NCURSES_ENABLED
#include "pq2ncurses.h"
#endif //NCURSES_ENABLED
#endif //GUI_ENABLED

using namespace std;

typedef std::chrono::steady_clock Clock;
typedef std::chrono::steady_clock::time_point TimePoint;

int main(const int argc, const char * const *argv) {
    bool runWebServer = false;
    int port = 8094;
    string filename;
    int gui = DEFAULT_GUI_LIBRARY;
    CommandLineProcessor cmdProcessor("Progress Quest 2 - The Progression", "A streamlined RPG experience", VERSION);
    try {
        cmdProcessor.AddOption('d', "daemon", "Run as a daemon", false);
#ifdef GUI_ENABLED
#ifdef QT_ENABLED
        cmdProcessor.AddOption('q', "qt", "Run QT interface", false);
#endif //QT_ENABLED
#ifdef GTK_ENABLED
        cmdProcessor.AddOption('g', "gtk", "Run GTK interface", false);
#endif //GTK_ENABLED
#ifdef COCOA_ENABLED
        cmdProcessor.AddOption('c', "cocoa", "Run Cocoa(Mac OS X) interface", false);
#endif //COCOA_ENABLED
#ifdef WINFORMS_ENABLED
        cmdProcessor.AddOption('w', "winforms", "Run Winforms(Windows) interface", false);
#endif //WINFORMS_ENABLED
#ifdef NCURSES_ENABLED
        cmdProcessor.AddOption('n', "ncurses", "Run NCurses(console) interface", false);
#endif //NCURSES_ENABLED
#endif //GUI_ENABLED
#ifdef WEBSERVER_ENABLED
        cmdProcessor.AddOption('s', "webserver", "Run web server", true, "The port to run the webserver on (default 8094)", "8094");
#endif
        cmdProcessor.AddValueOnlyOption("Filename", "Load a saved game");
        if (cmdProcessor.Parse(argc, argv) == false) {
            return 0;
        }
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
            port = stoi(cmdProcessor.GetOptionValue('s'));
        }
        filename = cmdProcessor.GetValueOnlyOptionValue("Filename");
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
        const file::LoadError error = game->LoadGame(filename);
        if (error != file::LoadErrorNone) {
            cout << "Error loading save " << filename << endl;
            if (gui == GUI_NONE) {
                return 1; //Daemon mode requires an existing save to run
            }
        }
    }
    if (gui == GUI_NONE) {
        cout << "Running in daemon mode" << endl;
        game->SetDaemonMode();
        if (game->GetState() == game::GameStateReady) {
            const TimePoint start = Clock::now();
            while (game->GetState() != game::GameStateFinished) {
                TimePoint now = Clock::now();
                const uint64_t milliseconds = static_cast<uint64_t>(abs(chrono::duration_cast<chrono::milliseconds>(now - start).count()));
                game->Tick(milliseconds);
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
        else {
            cout << "Daemon mode can only be run with an existing save" << endl;
            cout << "Please re-run with a valid save or create a new game with a GUI interface." << endl;
            return 1;
        }
    }
#ifdef GUI_ENABLED
    else {
        cout << "Running with " << MODE_NAME[gui] << " gui mode" << endl;
        unique_ptr<GUI> g;
#ifdef QT_ENABLED
        if (gui == GUI_QT) {
            g = make_unique<QTGUI>(game);
        }
#endif //QT_ENABLED
#ifdef GTK_ENABLED
        // if (gui == GUI_GTK) {
        //     g = make_unique<GTKGUI>(game);
        // }
#endif //GTK_ENABLED
#ifdef COCOA_ENABLED
        // if (gui == GUI_COCOA) {
        //     g = make_unique<CocoaGUI>(game);
        // }
#endif //COCOA_ENABLED
#ifdef WINFORMS_ENABLED
        // if (gui == GUI_WINFORMS) {
        //     g = make_unique<WinformsGUI>(game);
        // }
#endif //WINFORMS_ENABLED
#ifdef NCURSES_ENABLED
        if (gui == GUI_NCURSES) {
            g = make_unique<NCursesGUI>(game);
        }
#endif //NCURSES_ENABLED
        g->Run();
        g.reset();
    }
#endif //GUI_ENABLED
    if (runWebServer) {
        cout << "Running webserver on port " << port << endl;
    }

    return 0;
}
