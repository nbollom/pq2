//
// Created by nbollom on 27/06/16.
//

#include "signals.hpp"
#include <map>
#include <csignal>

using namespace std;

map<int, function<void(int)>> function_map;

void SignalCallback(const int signal_code) {
    if (function_map[signal_code]) {
        function_map[signal_code](signal_code);
    }
}

int AddSignalCallback(const int signal_code, const function<void(int)> &callback) {
    if (function_map[signal_code]) {
        return -1;
    }
    function_map[signal_code] = callback;
    signal(signal_code, SignalCallback);
    return 0;
}

int RemoveSignalCallback(const int signal_code) {
    if (function_map[signal_code]) {
        function_map[signal_code] = nullptr;
        signal(signal_code, SIG_DFL);
        return 0;
    }
    return -1;
}

void RaiseSignal(const int signal_code) {
    raise(signal_code);
}
