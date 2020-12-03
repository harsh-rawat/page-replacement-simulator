#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_INPUT_PARSER_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_INPUT_PARSER_H

#include <stdio.h>
#include "error_handler.h"

#define MAX_BUFFER_SIZE 4096

struct memory_reference {
    long file_ptr;
    int pid;
    int vpn;
};
typedef struct memory_reference memory_reference;

memory_reference *ReadLine(FILE *file, long file_ptr);

memory_reference *ReadLineAtIndex(FILE *fp, long file_ptr);

memory_reference *CreateMemoryReference(int pid, int vpn, long file_ptr);

#endif
