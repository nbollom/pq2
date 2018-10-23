# pq2
A cross-platform remake of the awesome idle game Progress Quest

For the original Progress Quest go [here](http://progressquest.com)

## Current Status

Game core:
At the current time the game is not "playable", the character creation logic is done, but the game logic is not. The load/save functionality also does not yet work

QT Interface:
The QT interface is the most complete and allows the player to create a new character and show the in-progress design screen

NCurses Interface:
The ncurses interface has the main menu done, but in an older style that didn't work well and need re-coding

Other Interfaces:
The GTK/Winforms/Cocoa(OS X)/Webserver interfaces are not yet started

## Building

Linux:

```
git clone https://github.com/nbollom/pq2.git
cd pq2
mkdir build
cd build
cmake -DNCURSES_ENABLED=OFF -DGTK_ENABLED=OFF ..
make
```

other OS's not currently supported although it can be compiled on osx with the QT interface:

```
cmake -DNCURSES_ENABLED=OFF -DGTK_ENABLED=OFF -DCOCOA_ENABLED=OFF -DDEFAULT_GUI_LIBRARY=GUI_QT -DQt5_DIR=<PATH_TO_Qt5Config.cmake> ..
```
