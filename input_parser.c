#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input_parser.h"

char *extractLineFromFile(FILE *file, int index);

char *reallocateString(char *buffer, int len);

memory_reference *split(char *str, int initialIndex, int maxLen, int lineIndex);

memory_reference *ReadLine(FILE *file, int index) {
    //Extract the line from the file
    char *line = extractLineFromFile(file, index);
    //Extract memory reference from the line
    memory_reference *reference = split(line, 0, strlen(line), index);
    return reference;
}

memory_reference *CreateMemoryReference(int pid, int vpn, int lineIndex) {
    memory_reference *mem_ref = malloc(sizeof(memory_reference));
    mem_ref->lineIndex = lineIndex;
    mem_ref->pid = pid;
    mem_ref->vpn = vpn;
    return mem_ref;
}

/**
 * This method is used to extract a line from a file. We perform buffer overflow and null byte check as we extract the line.
 * This method has been reused from our last assignment.
 * */
char *extractLineFromFile(FILE *file, int index) {
    char *buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
    int len = 0;
    char ch;

    while (1) {
        ch = fgetc(file);

        if (len >= MAX_BUFFER_SIZE) { // During buffer overflow exit with error
            buffer[MAX_BUFFER_SIZE - 1] = '\0';
            BufferOverflowError(index, buffer);
        } else if (ch == '\0') { // If a null byte is found in line then exit with error
            buffer[len] = '\0';
            NullByteInLineError(index, buffer);
        } else if (ch == EOF || ch == '\n') {
            buffer[len++] = '\0';
            break;
        } else {
            buffer[len++] = ch;
        }
    }

    char *final_str = reallocateString(buffer, len);
    return final_str;
}

/**
 * This method is used to reallocate a string to its size
 * This method has been reused from our last assignment.
 * */
char *reallocateString(char *buffer, int len) {
    char const *final_str = malloc(sizeof(char) * len);
    ValidateMemoryAllocationError(final_str);
    strcpy(final_str, buffer);
    free(buffer);
    return final_str;
}

/**
 * This method is used to split the line on whitespaces for getting (pid,vpn)
 * */
memory_reference *split(char *str, int initialIndex, int maxLen, int lineIndex) {
    memory_reference *ref = CreateMemoryReference(0, 0, lineIndex);
    int index;
    int num_count = 0;
    char *curr = malloc(sizeof(char) * MAX_BUFFER_SIZE);
    int curr_index = 0;

    for (index = initialIndex; index <= maxLen; index++) {
        if (index == maxLen || str[index] == ' ' || str[index] == '\t' || str[index] == '\r') {
            //Record this num
            if (curr_index > 0) {
                curr[curr_index] = '\0';
                if (num_count == 0)
                    ref->pid = atoi(curr);
                else if (num_count == 1)
                    ref->vpn = atoi(curr);
                else
                    InvalidInputError(lineIndex);

                num_count++;
                memset(curr, '\0', MAX_BUFFER_SIZE);
            }
            curr_index = 0;
            continue;
        }
        if (!isdigit(str[index - initialIndex]))
            InvalidInputError(lineIndex);
        curr[curr_index++] = str[index - initialIndex];
    }

    free(curr);
    return ref;
}