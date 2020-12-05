/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_ERROR_HANDLER_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_ERROR_HANDLER_H

#define ERROR_TEMPLATE "%d: %s: %s\n"

void BufferOverflowError(int index, char *line);

void NullByteInLineError(int index, char *line);

void ValidateMemoryAllocationError(void *arg);

void InvalidInputError();

void ThrowError(char *error_msg);

void TSearchError();

void OptionParsingError();

#endif
