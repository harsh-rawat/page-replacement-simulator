#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"

void BufferOverflowError(int index, char *line){

}

void NullByteInLineError(int index, char *line){

}

void ValidateMemoryAllocationError(void *arg){

}

void InvalidInputError(int index){
    printf("Invalid\n");
    exit(EXIT_FAILURE);
}

void TSearchError(){
    printf("Insufficient memory\n");
    exit(EXIT_FAILURE);
}