//
// Created by kosenko on 19.06.24.
//

#include "print_raindrop.h"
#include "library/terminal_bfo/terminal_funcs.h"
#include "library/loging_bfo/log.h"

void print_raindrop(rain_drop raindrop, int row_num, int col_num, print_raindrop_settings settings)
{
    printf("%s", settings.background.line);
    if (raindrop.column < col_num)
    {
        int end = raindrop.used + raindrop.row;//
        end = end > row_num ? row_num : end;
        for (int i = raindrop.row; i < end; i++)
        {
            terminal_goto_xy(raindrop.column + 1, i + 1);
            int position = i - raindrop.row + raindrop.size - raindrop.used;
            printf("%s%lc", raindrop.colors[position].line, raindrop.line[position - raindrop.size + raindrop.used]);
        }
    }
}

void fill_bg(int row_num, int col_num, print_raindrop_settings settings)
{
    printf("%s", settings.background.line);
    for (int i = 0; i++ < row_num;)
    {
        for (int j = 0; j++ < col_num;)
        {
            printf(" ");
        }
        printf("\n");
    }
}