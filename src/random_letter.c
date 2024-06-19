//
// Created by maksym on 18.06.24.
//

#include <locale.h>
#include "random_letter.h"
#include "library/random_bfo/statistical_random.h"

wchar_t get_random_unicode_char(){
    int codepoint = randint(0, 0xFFFF + 1); // Generate a random number between 0 and 0xFFFF

    wchar_t character = codepoint;
    return character;
}