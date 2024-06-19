//
// Created by maksym on 19.06.24.
//

#include "rain.h"
#include "random_letter.h"
#include "library/random_bfo/statistical_random.h"
#include "print_raindrop.h"
#include "library/loging_bfo/log.h"
#include "default_themes.h"

#define DROP_CHANCE 0.003

rain_drop rain_drop_init()
{
    int rain_size = 13;
    return (rain_drop){0, 0, rain_size, 0, calloc(rain_size, sizeof(wchar_t))};
}

void free_rain_drop(rain_drop drop){
    free(drop.line);
}

void free_rain(rain *rain_list){
    while (rain_list != NULL)
    {
        free_rain_drop(rain_list->drop);
        rain *prev = rain_list;
        rain_list = rain_list->next;
        free(prev);
    }
}

void free_rain_screen(rain_screen screen){
    free_rain(*screen.rain_list);
    free(screen.rain_list);
}

void rain_drop_iteration(rain_drop *drop)
{
    write_log(DEBUG, "START RAIN DROP ITERATION");
    wchar_t new_char = get_random_unicode_char();
    if(drop->used == drop->size)
    {
        for(int i = 0; i < drop->size - 1; i++){
            drop->line[i] = drop->line[i + 1];
        }
        drop->row++;
        drop->used--;
        write_log(DEBUG, "Screen app %d", drop->row);
    }
    drop->used++;
    drop->line[drop->used - 1] = new_char;

    write_log(DEBUG, "END RAIN DROP ITERATION");
}

void generate_rain_drop(rain_screen screen)
{
    for (int i = 0; i < screen.col_num; ++i) {
        if(rand_plain < DROP_CHANCE)
        {
            rain_drop new_drop = rain_drop_init();
            new_drop.column = i;
            rain *new_list_elem = calloc(1, sizeof(rain));
            new_list_elem->drop = new_drop;

            new_list_elem->next = *screen.rain_list;
            *screen.rain_list = new_list_elem;
        }
    }
}

rain_screen init_rain(int col_num, int row_num){
    rain_screen new_screen;
    new_screen.col_num = col_num;
    new_screen.row_num = row_num;
    new_screen.rain_list = calloc(1, sizeof(rain*));
    *new_screen.rain_list = NULL;
    generate_rain_drop(new_screen);
    return new_screen;
}

void rain_iteration(rain_screen screen){

    generate_rain_drop(screen);
    write_log(DEBUG, "Screen app %ld", *screen.rain_list);
    rain *rain_list = *screen.rain_list;
    rain *prev_rain = NULL;

    while (rain_list != NULL)
    {
        write_log(DEBUG, "rain_list row %d", rain_list->drop.row);
        rain_drop_iteration(&rain_list->drop);
        write_log(DEBUG, "rain_list upd row %d used %d size %d", rain_list->drop.row, rain_list->drop.used, rain_list->drop.size);
        write_log(DEBUG, "rain_list end");

        if(rain_list->drop.row == screen.row_num - 1)
        {
            rain *for_delete = rain_list;
            if(prev_rain == NULL)
            {
                *screen.rain_list = rain_list->next;
            }
            else
            {
                prev_rain->next = rain_list->next;
                rain_list = rain_list->next;
            }
            free_rain_drop(for_delete->drop);
            free(for_delete);
        }
        else
        {
            unsigned char colors[][3] = {{255,0,0}, {0,255,0}, {255,0,255}};
            double positions[3] = {0,0.7, 1};
            color_gradient_settings settings = {colors, (double *)positions, 3};
            COLOR bg = string_create_new(0);//color_create_background_rgb(0,0,0);
            //print_raindrop_settings r_settings = {settings, color_interpolator_square, bg};
            print_raindrop_settings r_settings = theme_Ukraine;
            print_raindrop(rain_list->drop, screen.row_num, screen.col_num, r_settings);
            free_color(bg);
            prev_rain = rain_list;
            rain_list = rain_list->next;

        }

    }
}