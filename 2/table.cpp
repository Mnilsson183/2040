// Copyright 2025 Morgan Nilsson
#include "table.hpp"
#include <cstring>
#include <_printf.h>
#include <assert.h>

char morse_code_lookup_table[LOOKUP_TABLE_SIZE];

/**
 * @brief helper function to insert a character into the table
 * 
 * @param c the character as key
 * @param morse_code the value
 */
void insert_morse_code(char c, const char *morse_code) {

    // is upper
    if (c >= 65 && c <= 90) {

        c = c - 32;

    }
    
    if (c >= 97 && c <= 122) {

        // copy the morse to the lookup table
        memcpy(&morse_code_lookup_table[5 * (c - 'a')], morse_code, strlen(morse_code) + 1);


    } else {

        assert(0);

    }


}

/**
 * @brief get a morse code given a char
 * 
 * @param c the key to get from
 * 
 * @return pointer to the morse sequence
 */
char *get_morse_code(char c) {


    // is upper
    if (c >= 65 && c <= 90) {

        c = c - 32;

    }
    
    if (c >= 97 && c <= 122) {

        // return the table location
        return &morse_code_lookup_table[5 * (c - 'a')];


    } else {

        assert(0);

    }

}