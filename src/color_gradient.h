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

int* color_gradient_get(color_gradient_settings settings, double position);

#endif //BFO_MATRIX_SRC_COLOR_GRADIENT_H
