/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#ifndef PAGE_REPLACEMENT_SIMULATOR_STATISTICS_H
#define PAGE_REPLACEMENT_SIMULATOR_STATISTICS_H

#include "error_handler.h"

typedef struct statistics {
    long average_memory_utilization_count_total;
    long average_runnable_processes_count_total;
    int total_memory_references;
    int total_page_faults;
    long run_time;
    int max_page_size;
} statistics;

statistics *CreateStatistics(int max_page_size);

void UpdateAverageMemoryUtilization(statistics *stats, long occupied_pf);

void UpdateAverageRunnableProcesses(statistics *stats, int non_blocked);

void UpdateTotalMemoryReferences(statistics *stats, long references);

void UpdateTotalPageFaults(statistics *stats);

void UpdateRunningTime(statistics *stats, long count);

void PrintStatistics(statistics *stats);

#endif
