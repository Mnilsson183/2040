// Copyright 2025 Morgan Nilsson

#include "tree.hpp"
#include "table.hpp"
#include <_stdio.h>
#include <cstdint>
#include <cstdio>
#include <iostream>

/**
 * @brief translate a buffer of plain text(src) to morse code(dest)
 * 
 * @param dest the destination for the morse code
 * @param src the plain text to translate
 */
void translate_to_morse(char *dest, char *src) {
    // ' ' delim between words
    // '/' delim between letters
    uint64_t index = 0;

    while (*src != '\0') {

        while (*src != ' ') {

            if (*src == '\0') {

                *dest = '\0';
                return;

            }

            *dest = '/';
            ++dest;
            char *morse = get_morse_code(*src);
            memcpy(dest, morse, strlen(morse));
            dest += strlen(morse);

            ++src;

        }

        ++src;
        *dest = ' ';
        ++dest;

    }

    *dest = '\0';

}

/**
 * @brief translate a buffer of morse code(src) to a buffer of plaintext(dest)
 * 
 * @param tree the decription tree
 * @param dest the buffer of plaintext
 * @param src the buffer of morsecode
 */
void translate_morse_to_plain(tree_t *tree, char *dest, char *src) {

    uint64_t index = 0;

    while (*src != '\0') {

        if (*src == ' ') {

            *dest = ' ';

            ++src;
            ++dest;

        } else if (*src == '/') {

            ++src;

            // copy the morse to another buffer
            char buf[5];
            char *ptr = buf;
            while (*src != ' ' && *src != '/' && *src != '\0') {

                *ptr = *src;

                ++src;
                ++ptr;

            }
            *ptr = '\0';

            *dest = get_value(tree, buf);
            ++dest;


        }

    }

    *dest = '\0';

}

/**
 * @brief helper function to read lines from a file to a destination buffer
 * 
 * @param line_count a pointer to amount of lines this is populated by the function
 * @param max_lines the max amount of lines to read from a file
 * @param max_line_size the max size of any given lines
 * @param file the file to read from
 * 
 * @return a char** of lines
 */
char **get_lines(uint64_t *line_count, uint64_t max_lines, uint64_t max_line_size, FILE* file) {

    char **lines = (char**)malloc(sizeof(char*) * max_lines);

    if (lines == NULL) return NULL;

    *line_count = 0;

    lines[*line_count] = (char*)malloc(sizeof(char) * max_line_size);

    if (lines[*line_count] == NULL) {

        free(lines);
        return NULL;

    }

    while (fgets(lines[(*line_count)], max_line_size, file) != NULL) {

        ++(*line_count);

        if (*line_count == max_lines) return lines;

        lines[*line_count] = (char*)malloc(sizeof(char) * max_line_size);

        if (lines[*line_count] == NULL) {

            --(*line_count);
            return lines;

        }

    }

    return lines;
}

/**
 * @brief populate the structs that I need to translate
 * 
 * @param tree the tree to be populated
 * @param filename the name of the file to populate from
 * 
 * @note this also populates the morse code lookup table
 */
void populate_structs(tree_t *tree, const char *filename) {
    char **lines = NULL;
    uint64_t line_count = 0;
    uint64_t max_lines = 64;
    uint64_t max_line_size = 64;

    FILE *file = fopen(filename, "r");

    lines = get_lines(&line_count, max_lines, max_line_size, file);

    char c;
    char buf[5];

    for (uint64_t line_index = 0; line_index < line_count; line_index++) {

        c = lines[line_index][0];

        char *ptr = &lines[line_index][1];
        char *buf_ptr = buf;
        while (*ptr != '\0' && *ptr != '\n' && (buf_ptr - buf) < 4) {

            *buf_ptr = *ptr;
            ++buf_ptr;
            ++ptr;

        }
        *buf_ptr = '\0';

        // insert to tree
        insert_value(tree, c, buf);

        // insert to table
        insert_morse_code(c, buf);

    }

    fclose(file);
}

/**
 * @brief demonstrate the encode/decode functions
 * 
 * @param tree the tree decoding structure
 * @param string the demonstration string
 */
void demonstrate_encode_decode(tree_t *tree, char *string) {

    char encode_buf[2048];
    char decode_buf[2048];

    printf("Given: %s\n", string);

    translate_to_morse(encode_buf, string);

    printf("    Encoded: %s\n", encode_buf);

    translate_morse_to_plain(tree, decode_buf, encode_buf);

    printf("    Decoded: %s\n", decode_buf);

}

/**
 * @brief Main function
 * 
 * @return int Return code
 * 
 * ./program
 *      Translation table: default "translation.txt"
 *      Input: stdin
 */
int main(void) {

    tree_t *tree = make_tree();

    populate_structs(tree, "translation.txt");

    char buf[128];

    printf("\"exit\" to quit\n");

    while (strcmp(buf, "exit") != 0) {

        printf("> ");
        std::cin >> buf;
        printf("\n");
        demonstrate_encode_decode(tree, buf);

    }






}
