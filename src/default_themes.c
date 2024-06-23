//
// Created by kosenko on 19.06.24.
//

#include "default_themes.h"

const COLOR bg_empty = {"", 0};
double positions_dipole[2] = {0, 1};

unsigned char colors_t1[][3] = {{255, 0, 0}, {0, 255, 0}, {255, 0, 255}};
double positions_t1[3] = {0, 0.7, 1};
const color_gradient_settings settings_t1 = {colors_t1, (double *)positions_t1, 3};
const print_raindrop_settings theme_red_green_magenta = {settings_t1, color_interpolator_square, bg_empty};

unsigned char colors_t2[][3] = {{0, 0, 255}, {255, 255, 0}};
const color_gradient_settings settings_t2 = {colors_t2, (double *)positions_dipole, 2};
const print_raindrop_settings theme_Ukraine = {settings_t2, color_interpolator_square, bg_empty};

unsigned char colors_t3[][3] = {{0, 0, 0}, {0, 255, 0}};
const color_gradient_settings settings_t3 = {colors_t3, (double *)positions_dipole, 2};
const print_raindrop_settings theme_green = {settings_t3, color_interpolator_square, bg_empty};

unsigned char colors_t4[][3] = {{255, 255, 255}};
double positions_t4[1] = {1};
print_raindrop_settings get_theme_BSOD()
{
    COLOR bg_t4 = color_create_background_rgb(0, 0, 255);
    const color_gradient_settings settings_t4 = {colors_t4, (double *)positions_t4, 1};
    const print_raindrop_settings theme_BSOD = {settings_t4, color_interpolator_square, bg_t4};
    return theme_BSOD;
}

print_raindrop_settings get_theme_red_green_magenta()
{
    return theme_red_green_magenta;
}

print_raindrop_settings get_theme_Ukraine()
{
    return theme_Ukraine;
}

print_raindrop_settings get_theme_green()
{
    return theme_green;
}