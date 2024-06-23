//
// Created by maksym on 20.06.24.
//

#ifndef BFO_MATRIX_CONSTANTS_H
#define BFO_MATRIX_CONSTANTS_H

#define RAIN_LEN 20
#define DROP_CHANCE 0.01

#define MILLISECONDS_DELAY 15

//get_theme_red_green_magenta, get_theme_Ukraine, get_theme_green, get_theme_BSOD
#define DEFAULT_THEME get_theme_Ukraine

/*
 * get_random_unicode_char
 * get_random_ascii_char
 * get_random_cyrillic_char
 * get_random_cyrillic_ascii_char
 * get_random_emoji_char
 * get_random_number_char
 * get_random_arabic_letter
 * get_random_chinese_character
 * get_random_ukrainian_character
 * get_random_english_letter
 */
#define CHAR_RANDOM get_random_ukrainian_character

//#define END_WITH_ITER_NUM
#ifdef END_WITH_ITER_NUM
#define ITER_NUM 500
#endif

#endif //BFO_MATRIX_CONSTANTS_H
