//
// Created by maksym on 19.06.24.
//

#include "rain.h"
#include "random_letter.h"

rain_drop rain_drop_init()
{
    int rain_size = 6;
    return (rain_drop){0, 0, rain_size, 0, calloc(rain_size, sizeof(wchar_t))};
}

void rain_drop_iteration(rain_drop *drop)
{
    wchar_t new_char = get_random_unicode_char();
    if(drop->used == drop->size)
    {
        for(int i = 0; i < drop->size - 1; i++){
            drop->line[i] = drop->line[i + 1];
        }
        drop->row++;
    }
    drop->line[drop->used - 1] = new_char;
}

void rain_iteration(wchar_t **screen, rain *rain_list){

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

}