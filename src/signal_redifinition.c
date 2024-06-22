//
// Created by maksym on 22.06.24.
//

#include "signal_redifinition.h"
#include "rain.h"

struct winsize get_window_size()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}

int catch_signal(int sig, void (*handler)(int))
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

void is_window_changed(int signal)
{

    write_log(DEBUG, "window_changed");
    restart_rain();
}

void end_program(int signal)
{

    write_log(DEBUG, "program ended");
    end_rain();
}

void redefine_signals()
{

    catch_signal(SIGINT, end_program);
    catch_signal(SIGWINCH, is_window_changed);
}