#include <stdio.h>
#include "input_parser.h"

int main(int argc, char *argv[]) {
    //Parse the program arguments. If provided else consider the default ones
    FILE* file = fopen("input.txt", "r");
    memory_reference* reference = ReadLine(file, 0);
    printf("%d\t%d\n", reference->pid, reference->vpn);
    return 0;
}
