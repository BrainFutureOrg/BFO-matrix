#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include "library/terminal_bfo/terminal_funcs.h"
#include "library/loging_bfo/log.h"
#include "rain.h"
#include "signal_redifinition.h"

#if __has_include("git_variables.h")
#include "git_variables.h"
#include "random_letter.h"
#endif

#define PROGRAM_NAME                "BFO-matrix"
#define SPACE_FOR_HELP              "    "

#ifndef GIT_LAST_COMMIT_HASH
#define GIT_LAST_COMMIT_HASH "hasn't_version"
#endif

enum STOP_RESUME
{
    STOP_PROGRAM,
    RESUME_PROGRAM
};

void print_help(char *prog_name)
{
    printf("NAME\n" SPACE_FOR_HELP PROGRAM_NAME " - matrix effect from Matrix movie\n");
    printf("SYNOPSIS\n" SPACE_FOR_HELP "%s [OPTION]\n", prog_name);
    printf("OPTIONS\n");
    printf(SPACE_FOR_HELP "Parameter       Full version  Opinion\n");
    printf(SPACE_FOR_HELP "-h              --help        Show help info\n");
    printf(SPACE_FOR_HELP "-v              --version     Show version info\n");
    printf(SPACE_FOR_HELP "-t <theme>      --theme       Default theme name (takes color and position lists from\n");
    printf(SPACE_FOR_HELP "                              default theme). <theme> is name from list: red_green_magenta,\n");
    printf(SPACE_FOR_HELP "                              Ukrainian, green, BSOD\n");

    printf("RAIN COLOR SETTINGS\n");
    printf(SPACE_FOR_HELP "-c <colors>     --color       Set color of letters. <colors> is either one <color>\n");
    printf(SPACE_FOR_HELP "                              or comma-separated <color> list (several colors will\n");
    printf(SPACE_FOR_HELP "                              create gradient)\n\n");
    printf(SPACE_FOR_HELP "-p <positions>  --positions   Set positions for gradient colors. <positions> is a\n");
    printf(SPACE_FOR_HELP "                              comma-separated list of floating-point numbers\n");
    printf(SPACE_FOR_HELP "                              normalized to fit in [0,1] range. This list must be of\n");
    printf(SPACE_FOR_HELP "                              colors list size. If this arg is absent, positions are\n");
    printf(SPACE_FOR_HELP "                              made uniformly\n\n");
    printf(SPACE_FOR_HELP "-b <color>      --background  Set color of background.\n");
//    printf("\n");

    printf("RAIN SETTINGS\n");
    printf(SPACE_FOR_HELP "--rain_len <number>           Set len for each rain part (default is %u)\n",
           rain_params.rain_len);
    printf(SPACE_FOR_HELP "--rain_drop_chance <number>   Set chance for appearing rain part (default is %f)\n",
           rain_params.drop_chance);
    printf(SPACE_FOR_HELP "--rain_speed <number>         Set speed of screen updating in milliseconds (default is %u)\n",
           rain_params.milliseconds_delay);
    printf(SPACE_FOR_HELP "--rain_chars <theme>          Set characters randomizer, for choice:\n");
    printf(SPACE_FOR_HELP "                              unicode (u), ascii (a), cyrillic (c), emoji (e),\n");
    printf(SPACE_FOR_HELP "                              cyrillic_ascii (ca), number (n), english (eng),\n");
    printf(SPACE_FOR_HELP "                              ukrainian (ukr), chinese (chi), arabic (ara)\n");

    printf("KEYWORDS DESCRIPTIONS\n");
    printf(SPACE_FOR_HELP "Keyword         Description\n");
    printf(SPACE_FOR_HELP "<color>         Color specification. Can be either name (from these: ) or hex color\n");
    printf(SPACE_FOR_HELP "                in #XXXXXX format,where each X is a hex digit (0-9 and a-f or A-F)\n");
}

void print_version()
{
    printf(PROGRAM_NAME " - Version betta 0.1.%s\n\n", GIT_LAST_COMMIT_HASH);
    printf("It is free software: you are free to modify and distribute it.\n");
    printf("NO WARRANTIES are made to you, other than those provided by law.\n\n");
    printf("Authors of program are: Kosenko Olexander, Shkarupylo Maksym\n");
}

char is_comma(char *c)
{
    return *c == ',';
}

//#define CODE_READY

unsigned char *parse_color_arg(char *arg)
{
    unsigned char *result = malloc(3 * sizeof(char));
    if (arg[0] == '#')
    {
        for (int i = 0; i < 3; i++)
        {
            char str_hex[2];
            str_hex[0] = arg[1 + i * 2];
            str_hex[1] = arg[2 + i * 2];
            result[i] = strtol(str_hex, NULL, 16);
        }
    }
    else if (!(strcmp(arg, "black") && strcmp(arg, "k")))
    {
        result[0] = 0;
        result[1] = 0;
        result[2] = 0;
    }
    else if (!(strcmp(arg, "red") && strcmp(arg, "r")))
    {
        result[0] = 255;
        result[1] = 0;
        result[2] = 0;
    }
    else if (!(strcmp(arg, "green") && strcmp(arg, "g")))
    {
        result[0] = 0;
        result[1] = 255;
        result[2] = 0;
    }
    else if (!(strcmp(arg, "blue") && strcmp(arg, "b")))
    {
        result[0] = 0;
        result[1] = 0;
        result[2] = 255;
    }
    else if (!(strcmp(arg, "yellow") && strcmp(arg, "y")))
    {
        result[0] = 255;
        result[1] = 255;
        result[2] = 0;
    }
    else if (!(strcmp(arg, "cyan") && strcmp(arg, "c")))
    {
        result[0] = 0;
        result[1] = 255;
        result[2] = 255;
    }
    else if (!(strcmp(arg, "magenta") && strcmp(arg, "m")))
    {
        result[0] = 255;
        result[1] = 0;
        result[2] = 255;
    }
    else if (!(strcmp(arg, "white") && strcmp(arg, "w")))
    {
        result[0] = 255;
        result[1] = 255;
        result[2] = 255;
    }
    return result;
}
#ifdef CODE_READY
print_raindrop_settings (*theme_from_name(char *c))(void)
{
    if(!strcmp(c, "green")){
        return
    }
}
#endif

enum STOP_RESUME argv_checker(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        write_log(INFO, "argc = %d", argc);
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            print_help(argv[0]);
            return STOP_PROGRAM;
        }
        else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0)
        {
            print_version();
            return STOP_PROGRAM;
        }
        else if (strcmp(argv[i], "--color") == 0 || strcmp(argv[i], "-c") == 0)
        {
            string unsplit = string_create_new(0);
            while (++i < argc && argv[i][0] != '-')
            {
                string_add_charp(&unsplit, argv[i]);
            }
            i--;
            if (!string_charp_equals(unsplit, ""))
            {
                string_array split = string_split(unsplit.line, is_comma);
                unsigned char (*color_list)[3] = malloc(split.size * sizeof(unsigned char[3]));//TODO FREE SOMEWHERE
                for (int j = 0; j < split.size; j++)
                {
                    unsigned char *parsed = parse_color_arg(string_array_get_element(&split, j).line);
                    for (int k = 0; k < 3; k++)
                    {
                        color_list[j][k] = parsed[k];
                    }
                    free(parsed);
                }
                rain_params.raindrop_settings.gradient_settings.len = split.size;
                free_string_array(&split);
                rain_params.raindrop_settings.gradient_settings.colors = color_list;
                rain_params.use_default_theme = 0;
            }
            else
            {
                printf("Colors not specified. See help");
            }
            free_string(unsplit);
        }
        else if (strcmp(argv[i], "--positions") == 0 || strcmp(argv[i], "-p") == 0)
        {
            string unsplit = string_create_new(0);
            while (++i < argc && argv[i][0] != '-')
            {
                string_add_charp(&unsplit, argv[i]);
            }
            i--;
            if (!string_charp_equals(unsplit, ""))
            {
                string_array split = string_split(unsplit.line, is_comma);
                double *position_list = malloc(split.size * sizeof(double));//TODO FREE SOMEWHERE
                for (int j = 0; j < split.size; j++)
                {
                    position_list[j] = strtod(string_array_get_element(&split, j).line, NULL);
                }
                rain_params.raindrop_settings.gradient_settings.len = split.size;
                free_string_array(&split);
                rain_params.raindrop_settings.gradient_settings.positions = position_list;
                rain_params.use_default_theme = 0;
            }
            else
            {
                printf("Positions not specified. See help");
            }
            free_string(unsplit);
        }
        else if (strcmp(argv[i], "--background") == 0 || strcmp(argv[i], "-b") == 0)
        {
            unsigned char *parsed = parse_color_arg(argv[++i]);
            rain_params.raindrop_settings.background =
                color_create_background_rgb(parsed[0], parsed[1], parsed[2]);//TODO: FREE
            rain_params.use_default_theme = 0;
        }
        else if (strcmp(argv[i], "--theme") == 0 || strcmp(argv[i], "-t") == 0)
        {

        }

        else if (strcmp(argv[i], "--rain_len") == 0)
        {
            char *rain_len = argv[++i];
            uint len_long = (uint)strtol(rain_len, NULL, 10);
            if (errno)
            {
                printf("Error happened in --rain_len\n");
                printf("To see available options for rain_len type '%s --help'\n", argv[0]);
                return STOP_PROGRAM;
            }
            rain_params.rain_len = len_long;
        }

        else if (strcmp(argv[i], "--rain_drop_chance") == 0)
        {
            char *rain_drop_chance = argv[++i];
            double len_long = strtod(rain_drop_chance, NULL);
            if (errno)
            {
                printf("Error happened in --rain_drop_chance\n");
                printf("To see available options for rain_drop_chance type '%s --help'\n", argv[0]);
                return STOP_PROGRAM;
            }
            rain_params.drop_chance = len_long;
        }

        else if (strcmp(argv[i], "--rain_speed") == 0)
        {
            char *rain_speed = argv[++i];
            uint len_long = (uint)strtol(rain_speed, NULL, 10);
            if (errno)
            {
                printf("Error happened in --rain_speed\n");
                printf("To see available options for rain_speed type '%s --help'\n", argv[0]);
                return STOP_PROGRAM;
            }
            rain_params.milliseconds_delay = len_long;
        }
        else if (strcmp(argv[i], "--rain_chars") == 0)
        {
            char *rain_char_func = argv[++i];
            if (strcmp(rain_char_func, "unicode") == 0 || strcmp(rain_char_func, "u") == 0)
            {
                rain_params.char_randomizer = get_random_unicode_char;
            }
            else if (strcmp(rain_char_func, "ascii") == 0 || strcmp(rain_char_func, "a") == 0)
            {
                rain_params.char_randomizer = get_random_ascii_char;
            }
            else if (strcmp(rain_char_func, "cyrillic") == 0 || strcmp(rain_char_func, "c") == 0)
            {
                rain_params.char_randomizer = get_random_cyrillic_char;
            }
            else if (strcmp(rain_char_func, "emoji") == 0 || strcmp(rain_char_func, "e") == 0)
            {
                rain_params.char_randomizer = get_random_emoji_char;
            }
            else if (strcmp(rain_char_func, "cyrillic_ascii") == 0 || strcmp(rain_char_func, "ca") == 0)
            {
                rain_params.char_randomizer = get_random_cyrillic_ascii_char;
            }
            else if (strcmp(rain_char_func, "number") == 0 || strcmp(rain_char_func, "n") == 0)
            {
                rain_params.char_randomizer = get_random_number_char;
            }
            else if (strcmp(rain_char_func, "english") == 0 || strcmp(rain_char_func, "eng") == 0)
            {
                rain_params.char_randomizer = get_random_english_character;
            }
            else if (strcmp(rain_char_func, "ukrainian") == 0 || strcmp(rain_char_func, "ukr") == 0)
            {
                rain_params.char_randomizer = get_random_ukrainian_character;
            }
            else if (strcmp(rain_char_func, "chinese") == 0 || strcmp(rain_char_func, "chi") == 0)
            {
                rain_params.char_randomizer = get_random_chinese_character;
            }
            else if (strcmp(rain_char_func, "arabic") == 0 || strcmp(rain_char_func, "ara") == 0)
            {
                rain_params.char_randomizer = get_random_arabic_letter;
            }
            else
            {
                printf("Error happened in --rain_chars, unrecognized option\n");
                printf("To see available options for rain_chars type '%s --help'\n", argv[0]);
            }

        }
        else
        {
            printf("To see available options type '%s --help'\n", argv[0]);
            return STOP_PROGRAM;
        }
    }
    return RESUME_PROGRAM;
}
int main(int argc, char **argv)
{
    init_logger(DEBUG, "log.txt");
    write_log(INFO, "Program start");

    redefine_signals();

    init_rain_params();

    if (argv_checker(argc, argv) == STOP_PROGRAM)
    {
        write_log(INFO, "Program end");
        return 0;
    }

    terminal_save_screen;
    terminal_invisible_cursor;
    srandom(time(NULL));
    setlocale(LC_ALL, "");
    terminal_erase_display;
    start_rain();

    write_log(INFO, "Program end");

    terminal_visible_cursor;
    terminal_restore_screen;
    return 0;
}