# pq2
A cross-platform remake of the awesome idle game Progress Quest

For the original Progress Quest go [here](http://progressquest.com)

## Current Status

- Game core: Complete 
- QT GUI: Complete
- NCurses GUI: Complete
- GTK GUI: Not started
- Windows GUI: Not Started
- MacOS GUI: Incomplete on old branch

## Building

Linux:

```
git clone https://github.com/nbollom/pq2.git
cd pq2
mkdir build
cd build
cmake ..
make
```

other OS's not currently supported, although it can be compiled on osx with the QT and ncurses interface:

```
cmake -DQt6_DIR=<PATH_TO_Qt6Config.cmake> ..
```
