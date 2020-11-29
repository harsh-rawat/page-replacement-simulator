#ifndef ASSIGNMENT4_ERROR_HANDLER_H
#define ASSIGNMENT4_ERROR_HANDLER_H

void BufferOverflowError(int index, char *line);
void NullByteInLineError(int index, char *line);
void ValidateMemoryAllocationError(void *arg);
void InvalidInputError(int index);

#endif
