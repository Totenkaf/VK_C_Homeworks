// Copyright 2022 by Artem Ustsov
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM_CONST 10
enum exit_result {_EXIT_SUCCESS = 0, _EXIT_FAILURE};

char input_char(FILE* file) {
    char c = '\0';
    int result = 0;
    do {
        result = fscanf(file, "%c", &c);
    } while (result != 1 && result != EOF);

    if(result == EOF) {
        return EOF;
    }
    return c;
}

char *input_string(FILE* file) {
    struct buffer {
        char *string;
        size_t size;
        size_t capacity;
    } buf = {NULL, 0, 0};
    char c = '\0';
    bool error = false;
    while (c = input_char(file), c != EOF && c != '\n' && !error) {
        if (buf.size + 1 >= buf.capacity) {
            size_t new_capacity = !buf.capacity ? 1 : buf.capacity * 2;
            char *tmp = (char *)malloc((new_capacity + 1) * sizeof(char));
            if (!tmp) {
                if (buf.string) {
                    free(buf.string);
                }
                error = true;
            }
            if(!error) {
                if (buf.string) {
                    tmp = strncpy(tmp, buf.string, buf.size);
                    free(buf.string);
                }
            }
            buf.string = tmp;
            buf.capacity = new_capacity;
        }
        if(!error) {
            buf.string[buf.size] = c;
            buf.string[buf.size + 1] = '\0';
            ++buf.size;
        }
    }
    if(error) {
        return NULL;
    }
    return buf.string;
}

int input_int(FILE* file) {
    char c = '\0';
    int result = 0;
    bool error = false;
    while (c = input_char(file), c != EOF && c != '\n' && !error) {
        if (!(c >= '0' && c <= '9')) {
            char *buf = input_string(file); /* Read to the end of the string */
            if (buf) {
                free(buf);
            }
            return 0;
        }
        if (!error) {
            result = result * NUM_CONST + c - '0';
        }
    }
    if (error) {
        return 0;
    }
    return result;
}

void print_string(const char* symbol) {
    size_t i = 0;
    do {
        printf("%c", symbol[i]);
        ++i;
    } while(symbol[i] != '\0');
}
