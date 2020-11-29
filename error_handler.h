#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_ERROR_HANDLER_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_ERROR_HANDLER_H

void BufferOverflowError(int index, char *line);
void NullByteInLineError(int index, char *line);
void ValidateMemoryAllocationError(void *arg);
void InvalidInputError(int index);
void TSearchError();

#endif
