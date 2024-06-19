#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include "library/terminal_bfo/terminal_funcs.h"
#include "library/string_bfo/String_struct.h"
#include "library/loging_bfo/log.h"
#include "library/random_bfo/statistical_random.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include "./library/terminal_bfo/colors_bfo/colors.h"
#include "random_letter.h"
#include "rain.h"
#include "print_raindrop.h"

#define background_fill color_to_rgb_background(20, 20, 20);
/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do
    {
        res = nanosleep(&ts, &ts);
    }
    while (res && errno == EINTR);

    return res;
}

struct winsize get_window_size()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}
//struct uint_pair{
//    uint x,y:3;
//};



int main() {
    terminal_save_screen;
    terminal_invisible_cursor;
    srandom(time(NULL));
    setlocale(LC_ALL, "");
    terminal_erase_display;

    init_logger(DEBUG, "log.txt");
    write_log(INFO, "Program start");

//    float snow_chance = 0.05;
    struct winsize size = get_window_size();
    rain_screen rain_screen1 = init_rain(size.ws_col, size.ws_row);

    for (int I = 0; I < 100; ++I)
    {
//        terminal_erase_screen;

        unsigned char colors[][3] = {{255,0,0}, {0,255,0}, {255,0,255}};
        unsigned char (*colors1)[3] = colors;
        double positions[3] = {0,0.7, 1};
        color_gradient_settings settings = {colors, (double *)positions, 3};
        COLOR bg = color_create_background_rgb(0,0,0);
        print_raindrop_settings r_settings = {settings, color_interpolator_square, bg};
        fill_bg(size.ws_row, size.ws_col, r_settings);
        write_log(INFO, "Screen filed %d", I);

        rain_iteration(rain_screen1);
        write_log(INFO, "Snow rendered %d", I);
        fflush(stdout);
//        printf("C");
        fflush(stdout);
        msleep(100);
    }
    free_rain_screen(rain_screen1);

    write_log(INFO, "Program end");

    terminal_visible_cursor;
    terminal_restore_screen;
    return 0;
}