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
    printf(SPACE_FOR_HELP "-c <colors>     --color       Set color of letters. <colors> is either one <color>\n");
    printf(SPACE_FOR_HELP "                              or comma-separated <color> list (several colors will\n");
    printf(SPACE_FOR_HELP "                              create gradient)\n\n");
    printf(SPACE_FOR_HELP "-p <positions>  --positions   Set positions for gradient colors. <positions> is a\n");
    printf(SPACE_FOR_HELP "                              comma-separated list of floating-point numbers\n");
    printf(SPACE_FOR_HELP "                              normalized to fit in [0,1] range. This list must be of\n");
    printf(SPACE_FOR_HELP "                              colors list size. If this arg is absent, positions are\n");
    printf(SPACE_FOR_HELP "                              made uniformly\n\n");
    printf(SPACE_FOR_HELP "-b <color>      --background  Set color of background.\n");
    printf(SPACE_FOR_HELP "-t <theme>      --theme       Default theme name (takes color and position lists from\n");
    printf(SPACE_FOR_HELP "                              default theme). <theme> is name from list: red_green_magenta,\n");
    printf(SPACE_FOR_HELP "                              Ukrainian, green, BSOD\n");
    printf("\n");
    printf("KEYWORDS DESCRIPTIONS\n");
    printf(SPACE_FOR_HELP "Keyword         Description\n");
    printf(SPACE_FOR_HELP "<color>         Color specification. Can be either name (from these: ) or hex color\n");
    printf(SPACE_FOR_HELP  "               in #XXXXXX format,where each X is a hex digit (0-9 and a-f or A-F)\n");
}

void print_version()
{
    printf(PROGRAM_NAME " - Version betta 0.1.%s\n\n", GIT_LAST_COMMIT_HASH);
    printf("It is free software: you are free to modify and distribute it.\n");
    printf("NO WARRANTIES are made to you, other than those provided by law.\n\n");
    printf("Authors of program are: Kosenko Olexander, Shkarupylo Maksym\n");
}

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
        if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0)
        {
            print_version();
            return STOP_PROGRAM;
        }
        if (strcmp(argv[i], "--color") == 0 || strcmp(argv[i], "-c") == 0)
        {
            print_version();
            return RESUME_PROGRAM;
        }
        if (strcmp(argv[i], "--positions") == 0 || strcmp(argv[i], "-p") == 0)
        {
            print_version();
            return RESUME_PROGRAM;
        }
        if (strcmp(argv[i], "--background") == 0 || strcmp(argv[i], "-b") == 0)
        {
            print_version();
            return RESUME_PROGRAM;
        }

        printf("To see available options type '%s --help'\n", argv[0]);
        return STOP_PROGRAM;
    }
    return RESUME_PROGRAM;
}
int main(int argc, char **argv)
{
    init_logger(DEBUG, "log.txt");
    write_log(INFO, "Program start");

    redefine_signals();

//    init_rain_params();

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