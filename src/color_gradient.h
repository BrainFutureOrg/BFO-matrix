//
// Created by kosenko on 18.06.24.
//

#ifndef BFO_MATRIX_SRC_COLOR_GRADIENT_H
#define BFO_MATRIX_SRC_COLOR_GRADIENT_H

typedef struct{
    unsigned char (*colors)[3]; // dimensions: index, rgb
    double* positions; //positions normalized to fit in [0,1]
    int len;
} color_gradient_settings;

typedef unsigned char* (*color_interpolator)(unsigned char* rgb1, unsigned char* rgb2, double position);

// calculate color at certain position in gradient
// position must be normalized to fit in [0,1]
// color is linearly interpolated
unsigned char* color_gradient_get(color_gradient_settings settings, double position);

// calculate color at certain position in gradient
// position must be normalized to fit in [0,1]
// interpolator is applied between every pair of colors
unsigned char* color_gradient_get_general(color_gradient_settings settings, double position, color_interpolator interpolator);

// interpolates r, g and b linearly between two points
// position should be normalized to fit in [0,1]
unsigned char* linear_color_interpolator(unsigned char* rgb1, unsigned char* rgb2, double position);

// color interpolation that applies f_inner to r, g and b, linearly interpolates results and applies f_outer
// position should be normalized to fit in [0,1]
unsigned char* color_interpolator_simple_nonlinear(unsigned char* rgb1, unsigned char* rgb2, double position, double(*f_inner)(double), double(*f_outer)(double));

unsigned char* color_gradient_root(unsigned char* rgb1, unsigned char* rgb2, double position);

unsigned char* color_interpolator_square(unsigned char* rgb1, unsigned char* rgb2, double position);

#endif //BFO_MATRIX_SRC_COLOR_GRADIENT_H
