//
// Created by kosenko on 19.06.24.
//

#include "print_raindrop.h"
#include "library/terminal_bfo/terminal_funcs.h"
#include "library/loging_bfo/log.h"

/*unsigned char *color_gradient_get_reuse(int position,
                                        int size,
                                        color_gradient_settings gradient_settings,
                                        color_interpolator interpolator)
{
    static char first_start = 1;
    static color_gradient_settings gradient_settings_prev;
    static color_interpolator interpolator_prev;
    if (first_start)
    {

    }
    else
    {
        if (gradient_settings_prev != gradient_settings)
        {

        }
    }
}*/

void print_raindrop(rain_drop raindrop, int row_num, int col_num, print_raindrop_settings settings)
{
//    write_log(DEBUG, "Snow printed %d", row_num);
    printf("%s", settings.background.line);
    if (raindrop.column < col_num)
    {
        int end = raindrop.used + raindrop.row;//
        end = end > row_num ? row_num : end;
        for (int i = raindrop.row; i < end; i++)
        {
            terminal_goto_xy(raindrop.column + 1, i + 1);
            int position = i - raindrop.row + raindrop.size - raindrop.used;
            //double position_norm = (double)(position + raindrop.size - raindrop.used) / (raindrop.size - 1);
            //unsigned char
            //*rgb = color_gradient_get_general(settings.gradient_settings, position_norm, settings.interpolator);
            //COLOR color = color_create_foreground_rgb(rgb[0], rgb[1], rgb[2]);
            /*write_log(DEBUG,
                      "pre-print, position is %d, i = %d, row = %d, size = %d, used = %d, line = %ls",
                      position,
                      i,
                      raindrop.row,
                      raindrop.size,
                      raindrop.used,
                      raindrop.line);*/
            printf("%s%lc", raindrop.colors[position].line, raindrop.line[position - raindrop.size + raindrop.used]);
            //write_log(DEBUG, "post-print");
//            write_log(DEBUG, "Line to print: %lc", raindrop.line[position]);
            //free_color(color);
            //free(rgb);
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