//
// Created by kosenko on 18.06.24.
//

#include "color_gradient.h"
#include <stdlib.h>
#include <math.h>

unsigned char *color_gradient_get_general(color_gradient_settings settings,
                                          double position,
                                          color_interpolator interpolator)
{
    int position_after = 0;
    for (int i = 0; i < settings.len; i++)
    {
        if (position <= settings.positions[i])
        {
            position_after = i;
            break;
        }
    }
    if (position_after == 0)
    {
        unsigned char *rgb = malloc(3 * sizeof(unsigned char));
        for (int i = 0; i < 3; i++)
        {
            rgb[i] = settings.colors[0][i];
        }
        return rgb;
    }
    else
    {
        double interval = settings.positions[position_after] - settings.positions[position_after - 1];
        double before_norm = (position - settings.positions[position_after - 1]) / interval;
        return interpolator(settings.colors[position_after - 1], settings.colors[position_after], before_norm);
    }
}

unsigned char *linear_color_interpolator(unsigned char *rgb1, unsigned char *rgb2, double position)
{
    unsigned char *rgb = malloc(3 * sizeof(unsigned char));
    for (int i = 0; i < 3; i++)
    {
        rgb[i] = (unsigned char)(rgb1[i] * (1 - position) + rgb2[i] * position);
    }
    return rgb;
}

unsigned char *color_gradient_get(color_gradient_settings settings, double position)
{
    return color_gradient_get_general(settings, position, linear_color_interpolator);
}

unsigned char *color_gradient_root(unsigned char *rgb1, unsigned char *rgb2, double position)
{
    unsigned char *rgb = malloc(3 * sizeof(unsigned char));
    for (int i = 0; i < 3; i++)
    {
        rgb[i] = (unsigned char)(pow(sqrt(rgb1[i] / 255.) * (1 - position) + sqrt(rgb2[i] / 255.) * position, 2) * 255);
    }
    return rgb;
}

unsigned char *color_interpolator_simple_nonlinear(unsigned char *rgb1,
                                                   unsigned char *rgb2,
                                                   double position,
                                                   double(*f_inner)(double),
                                                   double(*f_outer)(double))
{
    unsigned char *rgb = malloc(3 * sizeof(unsigned char));
    for (int i = 0; i < 3; i++)
    {
        rgb[i] = (unsigned char)f_outer((f_inner(rgb1[i]) * (1 - position) + f_inner(rgb2[i]) * position));
    }
    return rgb;
}

double norm_square(double x)
{
    x /= 255;
    return x * x;
}

double sqrt_scale(double x)
{
    return 255 * sqrt(x);
}

unsigned char *color_interpolator_square(unsigned char *rgb1, unsigned char *rgb2, double position)
{
    unsigned char *color = color_interpolator_simple_nonlinear(rgb1, rgb2, position, norm_square, sqrt_scale);
}