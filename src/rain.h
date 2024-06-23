//
// Created by maksym on 19.06.24.
//

#ifndef BFO_MATRIX_RAIN_H
#define BFO_MATRIX_RAIN_H

#include <wchar.h>
#include <stdlib.h>
#include "print_raindrop.h"
#include "color_gradient.h"

typedef struct
{
    int column;
    int row;
    int size;
    int used;
    wchar_t *line;
} rain_drop;

struct
{
    uint rain_len;
    uint milliseconds_delay;
    double drop_chance;
    print_raindrop_settings
    (*get_settings)(void);
    char use_default_theme;
    color_gradient_settings gradient_settings;
} rain_params;

typedef struct rain
{
    rain_drop drop;
    struct rain *next;
} rain;

typedef struct
{
    int col_num, row_num;
    rain **rain_list;
} rain_screen;

rain_screen init_rain(int col_num, int row_num);

void rain_iteration(rain_screen screen);

void free_rain_screen(rain_screen screen);

void start_rain();
void restart_rain();
void end_rain();
#endif //BFO_MATRIX_RAIN_H
