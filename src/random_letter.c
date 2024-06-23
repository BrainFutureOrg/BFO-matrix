//
// Created by maksym on 18.06.24.
//

#include <locale.h>
#include "random_letter.h"
#include "library/random_bfo/statistical_random.h"

// Function to generate a random Unicode character within a specific range
wchar_t get_random_char_in_range(int min, int max)
{
    int codepoint = randint(min, max);
    wchar_t character = codepoint;
    return character;
}

wchar_t get_random_unicode_char()
{
    return get_random_char_in_range(0, 0xFFFF + 1);
}

wchar_t get_random_ascii_char()
{
    return get_random_char_in_range(0x20, 0x7F);
}

wchar_t get_random_cyrillic_char()
{
    return get_random_char_in_range(0x0400, 0x0500);
}

wchar_t get_random_cyrillic_ascii_char()
{
    if (random() % 2 == 0)
    {
        return get_random_ascii_char();
    }
    else
    {
        return get_random_cyrillic_char();
    }
}

wchar_t get_random_emoji_char()
{
    return get_random_char_in_range(0x1F600, 0x1F650);
}

wchar_t get_random_number_char()
{
    return get_random_char_in_range(0x30, 0x3A);
}

// Function to get a random Arabic letter
wchar_t get_random_arabic_letter()
{
    return get_random_char_in_range(0x0600, 0x0700); // Arabic letters
}

// Function to get a random Chinese character
wchar_t get_random_chinese_character()
{
    return get_random_char_in_range(0x4E00, 0xA000); // CJK Unified Ideographs
}

wchar_t get_random_ukrainian_character()
{
    int choice = random() % 65;
    if (choice < 58)
    { // Cyrillic letters common to Ukrainian
        if (choice < 26)
        { // 'А' to 'Щ'
            return get_random_char_in_range(0x0410, 0x0429 + 1);
        }
        else if (choice == 26)
        { // 'Ь'
            return (wchar_t)(0x042C);
        }
        else if (choice < 29)
        { // 'Ю' to 'Я'
            return get_random_char_in_range(0x042E, 0x042F + 1);
        }
        else if (choice < 55)
        { // 'а' to 'щ'
            return get_random_char_in_range(0x0430, 0x0449 + 1);
        }
        else if (choice == 55)
        { // 'ь'
            return (wchar_t)(0x044C);
        }

        else
        { // 'ь' to 'я'
            return get_random_char_in_range(0x044E, 0x044F + 1);
        }
    }
    else
    { // Specific Ukrainian letters
        switch (choice)
        {
            case 58:
                return L'Ґ';
            case 59:
                return L'ґ';
            case 60:
                return L'Є';
            case 61:
                return L'є';
            case 62:
                return L'Ї';
            case 63:
                return L'ї';
            case 64:
                return L'І';
            case 65:
                return L'і';
            default:
                return L'?'; // Fallback, should not reach here
        }
    }
    return L'?'; // Fallback, should not reach here
}

wchar_t get_random_english_character()
{
    if (random() % 2 == 0)
    {
        return get_random_char_in_range(0x41, 0x5B); // A-Z
    }
    else
    {
        return get_random_char_in_range(0x61, 0x7B); // a-z
    }
}