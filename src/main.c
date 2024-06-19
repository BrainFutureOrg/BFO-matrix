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

string generate_snow_string(float snow_chance, int size)
{
    string_fast sf = string_fast_create_new(size);
    for (int I = 0; I < size; ++I)
    {
        float chance = rand_plain;
        if (chance < snow_chance)
        {
            string_fast_add_char(&sf, get_random_unicode_char());
        }
        else
        {
            string_fast_add_char(&sf, ' ');
        }
    }
    return sf.string_part;
}

string_array generate_snow(float snow_chance)
{
    struct winsize w = get_window_size();
    string_array array = string_array_create();
    for (int i = 0; i < w.ws_row; ++i)
    {
        string_array_push(&array, generate_snow_string(snow_chance, w.ws_col));
    }
    write_log(INFO, "snow size = %d", array.size);
    return array;
}

void render_snow(string_array *snow, float snow_chance, int num, int even)
{
    terminal_invisible_cursor;
    for (int i = 0; i < snow->size; ++i)
    {
        printf("%s\n", snow->elements[i].line);
        write_log(DEBUG, "Snow showed %d", i);
    }
    write_log(DEBUG, "Snow showed");
    if (num % even == 0)
    {
        string poped = string_array_pop(snow);
        struct winsize w = get_window_size();
        string new_line = generate_snow_string(snow_chance, w.ws_col);
        write_log(DEBUG, "New line created");
        free_string(poped);
        write_log(DEBUG, "Line fried");
        string_array_push_to_start(snow, new_line);
        write_log(INFO, "snow size = %d", snow->size);
        write_log(DEBUG, "Line added");
    }
//    terminal_visible_cursor;
}

void fill_screen(struct winsize size)
{
    background_fill
    terminal_goto_xy(0, 0);
    for (int i = 0; i < size.ws_row; i++)
    {
        for (int j = 0; j < size.ws_col; j++)
        {
            printf(" ");
        }
    }
}

int main() {
    terminal_save_screen;
    terminal_invisible_cursor;
    srandom(time(NULL));
    setlocale(LC_ALL, "");
    terminal_erase_display;

    init_logger(INFO, "log.txt");
    write_log(INFO, "Program start");

    float snow_chance = 0.05;
    string_array snow = generate_snow(snow_chance);

    for (int I = 0; I < 100; ++I)
    {
//        terminal_erase_screen;

        struct winsize size = get_window_size();
        fill_screen(size);
        write_log(INFO, "Screen filed %d", I);
        render_snow(&snow, snow_chance, I, 2);
        write_log(INFO, "Snow rendered %d", I);
        fflush(stdout);
        //printf("C");
        fflush(stdout);
        msleep(100);
    }
    free_string_array(&snow);
    write_log(INFO, "Program end");

    terminal_visible_cursor;
    terminal_restore_screen;
    return 0;
}