//
// Created by kosenko on 18.06.24.
//

#ifndef BFO_MATRIX_SRC_COLOR_GRADIENT_H
#define BFO_MATRIX_SRC_COLOR_GRADIENT_H

typedef struct{
    int** colors; // dimensions: index, rgb
    double* positions; //positions normalized to fit in [0,1]
    int len;
} color_gradient_settings;

typedef int* (*color_interpolator)(int* rgb1, int* rgb2, double position);

// calculate color at certain position in gradient
// position must be normalized to fit in [0,1]
// color is linearly interpolated
int* color_gradient_get(color_gradient_settings settings, double position);

// calculate color at certain position in gradient
// position must be normalized to fit in [0,1]
// interpolator is applied between every pair of colors
int* color_gradient_get_general(color_gradient_settings settings, double position, color_interpolator interpolator);

// interpolates r, g and b linearly between two points
// position should be normalized to fit in [0,1]
int* linear_color_interpolator(int* rgb1, int* rgb2, double position);

#endif //BFO_MATRIX_SRC_COLOR_GRADIENT_H
