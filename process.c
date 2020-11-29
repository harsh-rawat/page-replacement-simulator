#include <stdlib.h>
#include <stdio.h>
#include "process.h"

void* ParseTraceFile(char* filepath){
    FILE* file = fopen(filepath, "r");
    int lineIndex = 0;

    while (feof(file) == 0) {
        memory_reference *reference = ReadLine(file, lineIndex);
        //Check if the process id exists in the hashtable
        process *existing_process = NULL;//Get the process from hashtable
        if(existing_process == NULL){//If process does not exist in hashtable
            process *new_process = malloc(sizeof(process));
            new_process->pid = reference->pid;
            new_process->start = lineIndex;
            new_process->end = lineIndex;
            //Put this new process in hashtable
        } else {//Take the existing process object and update the last value
            existing_process->end = lineIndex;
        }
        free(reference);
        lineIndex++;
    }
    //return hashtable reference
}