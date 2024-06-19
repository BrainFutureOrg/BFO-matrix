//
// Created by maksym on 19.06.24.
//

#ifndef BFO_MATRIX_RAIN_H
#define BFO_MATRIX_RAIN_H

#include <wchar.h>
#include <stdlib.h>


typedef struct {
    int column;
    int row;
    int size;
    int used;
    wchar_t *line;
} rain_drop;

typedef struct rain{
    rain_drop drop;
    struct rain *next;
} rain;

typedef struct{
    int col_num, row_num;
    rain *rain_list;
    wchar_t **screen;
} rain_screen;

rain_screen init_rain(int col_num, int row_num);

void rain_iteration(wchar_t **screen, rain *rain_list);
void show_rain();
#endif //BFO_MATRIX_RAIN_H
