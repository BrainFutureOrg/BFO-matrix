//
// Created by maksym on 19.06.24.
//

#include <locale.h>
#include <time.h>
#include "rain.h"
#include "random_letter.h"
#include "library/random_bfo/statistical_random.h"
#include "print_raindrop.h"
#include "library/loging_bfo/log.h"
#include "default_themes.h"
#include "constants.h"
#include "library/terminal_bfo/terminal_funcs.h"
#include "signal_redifinition.h"

struct rainparams rain_params;

typedef struct int_color_list int_color_list;
struct int_color_list
{
    int key;
    COLOR *value;
    int_color_list *next;
};

int_color_list *color_dict = NULL;

COLOR *recalculate_color(int len)
{
    print_raindrop_settings
        settings = rain_params.use_default_theme ? rain_params.get_settings() : rain_params.raindrop_settings;
    COLOR *colors = malloc(len * sizeof(COLOR));
    for (int i = 0; i < len; i++)
    {
        double position_norm = i / (len - 1.);
        unsigned char
            *rgb = color_gradient_get_general(settings.gradient_settings, position_norm, settings.interpolator);
        colors[i] = color_create_foreground_rgb(rgb[0], rgb[1], rgb[2]);
        free(rgb);
    }
    return colors;
}

COLOR *get_or_create_colors(int len)
{
    int_color_list **color_dict_ptr = &color_dict;
    if (color_dict != NULL)
    {
        int_color_list *color_dict_current = color_dict;
        do
        {
            if (color_dict_current->key == len)
            {
                return color_dict_current->value;
            }
            color_dict_current = color_dict_current->next;
        }
        while (color_dict_current->next != NULL);
        color_dict_ptr = &color_dict_current->next;
    }

    *color_dict_ptr = malloc(sizeof(int_color_list));
    (*color_dict_ptr)->key = len;
    (*color_dict_ptr)->value = recalculate_color(len);
    (*color_dict_ptr)->next = NULL;
    return (*color_dict_ptr)->value;
    /* message from valgrind:
⠀⠀⠀⠀⠀⣀⡴⠖⠒⠒⢒⣒⡖⠒⠒⠒⠒⠒⠒⠶⠶⠤⣤⣀⣀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣴⠋⠀⠀⠤⣪⣝⡲⠯⠭⠥⠀⠀⠀⠀⠀⣀⣐⣒⡒⠉⠙⢦⡀⠀⠀
⠀⠀⠀⣼⠃⠀⠈⠰⠫⠋⣀⣀⣀⣀⠀⠃⠀⠀⠀⠸⠀⠀⠀⠈⠆⠀⠀⢧⠀⠀
⠀⣠⡾⠁⠀⡀⠠⠄⢰⣿⠿⠿⢯⣍⣙⣶⠀⠀⢀⣠⣶⣾⣿⠶⠆⠤⠤⢜⢷⡄
⡾⢻⢡⡞⠋⣽⠛⠲⠤⡤⠴⠋⠀⠀⠉⠁⠀⠀⠈⣿⠁⠀⢀⣀⣠⠶⠶⣽⣵⣿
⣇⢠⢸⡥⠶⣟⠛⠶⣤⣀⠀⠀⠀⢲⡖⣂⣀⠀⠀⠈⢳⣦⡀⠉⠉⣽⡄⠰⣻⣿
⠙⣮⡪⠁⠀⠻⣶⣄⣸⣍⠙⠓⠶⣤⣥⣉⣉⠀⠠⠴⠋⠁⣈⣥⣴⣿⡇⠈⣽⠃
⠀⠈⢻⡄⠀⠀⠙⣆⢹⡟⠷⣶⣤⣇⣀⠉⠙⡏⠉⢻⡟⢉⣹⣅⣼⣿⡇⠀⡏⠀
⠀⠀⠀⠻⣄⠀⠀⠈⠻⢦⡀⠀⣽⠉⠛⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⡇⠀
⠀⠀⠀⠀⠙⢦⣀⠄⡀⢄⡙⠻⠧⣤⣀⣀⣿⠀⠀⣿⢀⣼⣃⣾⣼⠟⠁⠀⡇⠀
⠀⠀⠀⠀⠀⠀⠉⠓⢮⣅⡚⠵⣒⡤⢄⣉⠉⠉⠉⠉⠉⠉⠉⢀⡠⠀⠀⠀⣷⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠳⢦⣄⡉⠙⠛⠃⠀⠀⠀⠀⠉⠁⠀⠀⠀⠀⡿⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠲⠶⢤⣤⣀⣀⣀⣀⣀⣀⡤⠞⠁⠀⠀⠀⠀⠀⠀
     */
}

rain_drop rain_drop_init()
{
    int rain_size = (int)rain_params.rain_len;
    return (rain_drop){0, 0, rain_size, 0, get_or_create_colors(rain_size),
                       calloc(rain_size, sizeof(wchar_t))};
}

void free_rain_drop(rain_drop drop)
{
    free(drop.line);
}

void free_rain(rain *rain_list)
{
    while (rain_list != NULL)
    {
        free_rain_drop(rain_list->drop);
        rain *prev = rain_list;
        rain_list = rain_list->next;
        free(prev);
    }
}

void free_rain_screen(rain_screen screen)
{
    free_rain(*screen.rain_list);
    free(screen.rain_list);
}

void rain_drop_iteration(rain_drop *drop)
{
    wchar_t new_char = rain_params.char_randomizer();
    if (drop->used == drop->size)
    {
        for (int i = 0; i < drop->size - 1; i++)
        {
            drop->line[i] = drop->line[i + 1];
        }
        drop->row++;
        drop->used--;
    }
    drop->used++;
    drop->line[drop->used - 1] = new_char;
}

void generate_rain_drop(rain_screen screen)
{
    for (int i = 0; i < screen.col_num; ++i)
    {
        if (rand_plain < rain_params.drop_chance)
        {
            rain_drop new_drop = rain_drop_init();
            new_drop.column = i;
            rain *new_list_elem = calloc(1, sizeof(rain));
            new_list_elem->drop = new_drop;

            new_list_elem->next = *screen.rain_list;
            *screen.rain_list = new_list_elem;
        }
    }
}

rain_screen init_rain(int col_num, int row_num)
{
    rain_screen new_screen;
    new_screen.col_num = col_num;
    new_screen.row_num = row_num;
    new_screen.rain_list = calloc(1, sizeof(rain *));
    *new_screen.rain_list = NULL;
    generate_rain_drop(new_screen);
    return new_screen;
}

void rain_iteration(rain_screen screen)
{

    generate_rain_drop(screen);
    rain *rain_list = *screen.rain_list;
    rain *prev_rain = NULL;

    while (rain_list != NULL)
    {
        rain_drop_iteration(&rain_list->drop);

        if (rain_list->drop.row == screen.row_num - 1)
        {
            rain *for_delete = rain_list;
            if (prev_rain == NULL)
            {
                *screen.rain_list = rain_list->next;
            }
            else
            {
                prev_rain->next = rain_list->next;
                rain_list = rain_list->next;
            }
            free_rain_drop(for_delete->drop);
            free(for_delete);
        }
        else
        {
            unsigned char colors[][3] = {{255, 0, 0}, {0, 255, 0}, {255, 0, 255}};
            double positions[3] = {0, 0.7, 1};
            color_gradient_settings settings = {colors, (double *)positions, 3};
            COLOR bg = string_create_new(0);
            print_raindrop_settings
                r_settings = rain_params.use_default_theme ? rain_params.get_settings() : rain_params.raindrop_settings;
            print_raindrop(rain_list->drop, screen.row_num, screen.col_num, r_settings);
            free_color(bg);
            prev_rain = rain_list;
            rain_list = rain_list->next;

        }

    }
}

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

int end_rain_var = 0;
int restart_rain_var = 0;

void start_rain()
{
start_rain:
    end_rain_var = 0;

    struct winsize size = get_window_size();
    rain_screen rain_screen1 = init_rain(size.ws_col, size.ws_row);

#ifdef END_WITH_ITER_NUM
    for (int I = 0; I < ITER_NUM; ++I)
#else
    while (!end_rain_var)
#endif
    {
        terminal_erase_screen;
        rain_iteration(rain_screen1);

        fflush(stdout);
        msleep(rain_params.milliseconds_delay);
        if (restart_rain_var)
        {
            restart_rain_var = 0;
            free_rain_screen(rain_screen1);
            goto start_rain;
        }
    }
    free_rain_screen(rain_screen1);
}

void restart_rain()
{
    restart_rain_var = 1;
}

void end_rain()
{
    end_rain_var = 1;
}

void init_rain_params()
{
    rain_params.rain_len = RAIN_LEN;
    rain_params.milliseconds_delay = MILLISECONDS_DELAY;
    rain_params.drop_chance = DROP_CHANCE;
    rain_params.get_settings = DEFAULT_THEME;
    rain_params.use_default_theme = 1;
    rain_params.raindrop_settings = DEFAULT_THEME();
    rain_params.char_randomizer = CHAR_RANDOM;
}