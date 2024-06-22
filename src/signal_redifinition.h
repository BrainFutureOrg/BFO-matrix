//
// Created by maksym on 22.06.24.
//

#ifndef BFO_MATRIX_SIGNAL_REDIFINITION_H
#define BFO_MATRIX_SIGNAL_REDIFINITION_H

#include <sys/ioctl.h>
#include <unistd.h>
#include "library/loging_bfo/log.h"
#include <signal.h>
#include <stdlib.h>

struct winsize get_window_size();
void redefine_signals();
#endif //BFO_MATRIX_SIGNAL_REDIFINITION_H
