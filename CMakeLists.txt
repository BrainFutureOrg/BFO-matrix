cmake_minimum_required(VERSION 3.28)
project(BFO_matrix C)

set(CMAKE_C_STANDARD 11)

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
        src/color_gradient.h)

target_link_libraries(BFO_matrix m)