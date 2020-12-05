/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"

void BufferOverflowError(int index, char *line) {
    fprintf(stderr, ERROR_TEMPLATE, index, "line size exceeds max buffer size", line);
    exit(EXIT_FAILURE);
}

void NullByteInLineError(int index, char *line) {
    fprintf(stderr, ERROR_TEMPLATE, index, "null byte found while parsing the line", line);
    exit(EXIT_FAILURE);
}

void ValidateMemoryAllocationError(void *arg) {
    if (arg == NULL) {
        fprintf(stderr, "Memory could not be allocated using malloc/calloc. Exiting!\n");
        exit(EXIT_FAILURE);
    }
}

void InvalidInputError() {
    printf("Invalid input found! Exiting now!\n");
    exit(EXIT_FAILURE);
}

void TSearchError() {
    printf("Insufficient memory while allocation of objects of tsearch\n");
    exit(EXIT_FAILURE);
}

void ThrowError(char *error_msg) {
    printf("%s Exiting now!\n", error_msg);
    exit(EXIT_FAILURE);
}

void OptionParsingError() {
    printf("An error occured while parsing the options passed to the program. Exiting now!\n");
    exit(EXIT_FAILURE);
}