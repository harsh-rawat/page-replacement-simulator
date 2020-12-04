//
// Created by Sidharth Gurbani on 12/1/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "process_options.h"
#include "error_handler.h"

int isNumString(char* str);

options *process_options(int argc, char *argv[]) {
    if (argc == 1) {
        exit(EXIT_FAILURE);
    }
    options *opt = malloc(sizeof(options));
    opt->filepath = malloc(sizeof(char) * 4096);
    opt->p = 4096;
    opt->m = 1 * MEGA;

    int index = 1;
    int c = 0;
    while ((c = getopt(argc, argv, "p::m::")) != -1) {
        switch (c) {
            case 'p':
                if (!isNumString((char*)optarg))
                    InvalidInputError(-1);
                opt->p = atoi(optarg);
                index += 2;
                break;
            case 'm':
                if (!isNumString((char*)optarg))
                    InvalidInputError(-1);
                opt->m = atoi(optarg) * MEGA;
                index += 2;
                break;
            default:
                printf("Nothing here!\n");
        }
    }

    if (argc - index > 1) {
        InvalidInputError(-1);
        exit(EXIT_FAILURE);
    }
    strcpy(opt->filepath, argv[index]);
    return opt;
}

int isNumString(char* str) {
    while(isdigit((unsigned char)*str)) {
        str++;
    }
    return *str == '\0' ? 1 : 0;
}