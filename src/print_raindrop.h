//
// Created by kosenko on 19.06.24.
//

#ifndef BFO_MATRIX_SRC_PRINT_RAINDROP_H
#define BFO_MATRIX_SRC_PRINT_RAINDROP_H

#include "color_gradient.h"
#include "library/terminal_bfo/colors_bfo/colors.h"

typedef struct
{
    color_gradient_settings gradient_settings;
    color_interpolator interpolator;
    COLOR background;
} print_raindrop_settings;

#include "rain.h"

void print_raindrop(rain_drop raindrop, int row_num, int col_num, print_raindrop_settings settings);

void fill_bg(int row_num, int col_num, print_raindrop_settings settings);

#endif //BFO_MATRIX_SRC_PRINT_RAINDROP_H
