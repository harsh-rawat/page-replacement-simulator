#ifndef PAGE_REPLACEMENT_SIMULATOR_STATISTICS_H
#define PAGE_REPLACEMENT_SIMULATOR_STATISTICS_H

typedef struct statistics {
    double average_memory_utilization_count_total;
    double average_runnable_processes_count_total;
    int total_memory_references;
    int total_page_faults;
    int run_time;
    int max_page_size;
} statistics;

statistics *CreateStatistics(int max_page_size);

void UpdateAverageMemoryUtilization(statistics *stats, int occupied_pf);

void UpdateAverageRunnableProcesses(statistics *stats, int non_blocked);

void UpdateTotalMemoryReferences(statistics *stats, int references);

void UpdateTotalPageFaults(statistics *stats);

void UpdateRunningTime(statistics *stats);

void PrintStatistics(statistics *stats);

#endif
