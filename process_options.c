//
// Created by Sidharth Gurbani on 12/1/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "process_options.h"
#include "error_handler.h"

options *process_options(int argc, char *argv[]) {
    if (argc == 1) {
        exit(EXIT_FAILURE);
    }
    options *opt = malloc(sizeof(options));
    opt->filepath = malloc(sizeof(char) * 4096);
    opt->p = 1024;
    opt->m = 1 * MEGA;

    int index = 1;
    int c = 0;
    while ((c = getopt(argc, argv, "p::m::")) != -1) {
        switch (c) {
            case 'p':
                if (optarg == NULL) {
                    InvalidInputError(-1);
                    exit(EXIT_FAILURE);
                }
                else
                    opt->p = atoi(optarg);
                index += 2;
                break;
            case 'm':
                if (optarg == NULL) {
                    InvalidInputError(-1);
                    exit(EXIT_FAILURE);
                }
                else
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

/*
    if (argc==1)
        printf("this is should throw error!\n");
    else if (argc==2) {
        if (strcmp(argv[1], "-p")==0 || strcmp(argv[1], "-m")==0)
            printf("this is error!\n");
        opt->filename = argv[1];
    }
    else if (argc==3) {
        if (strcmp(argv[1], "-p")==0 && strcmp(argv[2], "-m")==0)
            printf("this is error!\n");
        if (strcmp(argv[1], "-m")==0 && strcmp(argv[2], "-p")==0)
            printf("this is error!\n");

        if (strcmp(argv[1], "-p")==0)
        opt->filename = argv[2];
    }
    else if (argc==4)
        opt->filename = argv[3];
    */