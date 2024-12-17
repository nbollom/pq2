//
// Created by nbollom on 27/06/16.
//

#ifndef PQ2_SIGNALS_H
#define PQ2_SIGNALS_H

#include <functional>

int AddSignalCallback(int signal_code, const std::function<void(int)> &callback);
int RemoveSignalCallback(int signal_code);
void RaiseSignal(int signal_code);

#endif //PQ2_SIGNALS_H
