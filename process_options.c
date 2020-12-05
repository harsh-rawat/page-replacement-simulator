/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "process_options.h"
#include "error_handler.h"

int isNumString(char *str);

options *process_options(int argc, char *argv[]) {
    if (argc == 1) {
        OptionParsingError();
    }
    options *opt = malloc(sizeof(options));
    ValidateMemoryAllocationError(opt);
    opt->filepath = malloc(sizeof(char) * 4096);
    ValidateMemoryAllocationError(opt->filepath);
    opt->p = 4096;
    opt->m = 1 * MEGA;

    int index = 1;
    char *myarg;
    int c = 0;
    while ((c = getopt(argc, argv, "p::m::")) != -1) {
        switch (c) {
            case 'p':
                if (index + 1 >= argc)
                    OptionParsingError();
                myarg = argv[index + 1];
                if (!isNumString(myarg))
                    OptionParsingError();
                opt->p = atoi(myarg);
                index += 2;
                break;
            case 'm':
                if (index + 1 >= argc)
                    OptionParsingError();
                myarg = argv[index + 1];
                if (!isNumString(myarg))
                    OptionParsingError();
                opt->m = atoi(myarg) * MEGA;
                index += 2;
                break;
            default:
                OptionParsingError();
        }
    }

    if (argc - index > 1) {
        OptionParsingError();
    }
    strcpy(opt->filepath, argv[index]);
    return opt;
}

int isNumString(char *str) {
    while (isdigit((unsigned char) *str)) {
        str++;
    }
    return *str == '\0' ? 1 : 0;
}