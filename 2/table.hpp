// Copyright 2025 Morgan Nilsson
#ifndef TABLE_HPP
#define TABLE_HPP

#define ALPHA_SIZE 26
#define LOOKUP_TABLE_SIZE ALPHA_SIZE * 5

void insert_morse_code(char c, const char *morse_code);
char *get_morse_code(char c);

#endif