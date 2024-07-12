cmake_minimum_required(VERSION 3.28)
project(BFO_matrix C)

set(CMAKE_C_STANDARD 11)

execute_process(COMMAND git log -1 --pretty=format:%h
        OUTPUT_VARIABLE outv)
file(WRITE src/git_variables.h "#define GIT_LAST_COMMIT_HASH \"${outv}\"")

add_executable(BFO_matrix
        src/main.c
        src/library/terminal_bfo/colors_bfo/colors.c
        src/library/terminal_bfo/colors_bfo/bins.c
        src/library/terminal_bfo/progress_bar/progres_bar.c
        src/library/string_bfo/String_array_struct.c
        src/library/string_bfo/String_struct.c
        src/library/string_bfo/String_struct_formatting.c
        src/library/loging_bfo/log.c
        src/library/tests_bfo/test_funcs.c
        src/library/terminal_bfo/terminal_funcs.h
        src/library/random_bfo/statistical_random.c
        src/random_letter.c
        src/random_letter.h
        src/color_gradient.c
        src/color_gradient.h
        src/rain.c
        src/rain.h
        src/print_raindrop.c
        src/print_raindrop.h
        src/default_themes.c
        src/default_themes.h
        src/constants.h
        src/signal_redifinition.c
        src/signal_redifinition.h
        src/free_list.c
        src/free_list.h
)

target_link_libraries(BFO_matrix m)