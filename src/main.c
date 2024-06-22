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
#include "constants.h"
#include "signal_redifinition.h"

#define background_fill color_to_rgb_background(20, 20, 20);

int main()
{
    init_logger(DEBUG, "log.txt");
    write_log(INFO, "Program start");

    terminal_save_screen;
    terminal_invisible_cursor;
    srandom(time(NULL));
    setlocale(LC_ALL, "");
    terminal_erase_display;

    redefine_signals();
    start_rain();

    write_log(INFO, "Program end");

    terminal_visible_cursor;
    terminal_restore_screen;
    return 0;
}