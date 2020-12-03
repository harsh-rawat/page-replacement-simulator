#include <stdlib.h>
#include <stdio.h>
#include "statistics.h"

statistics *CreateStatistics() {
    statistics *stats = malloc(sizeof(statistics));
    stats->average_memory_utilization_count_total = 0.0;
    stats->average_runnable_processes_count_total = 0.0;
    stats->total_memory_references = 0;
    stats->total_page_faults = 0;
    stats->run_time = 0;

    return stats;
}

void UpdateAverageMemoryUtilization(statistics *stats, int occupied_pf) {
    stats->average_memory_utilization_count_total += occupied_pf;
}

void UpdateAverageRunnableProcesses(statistics *stats, int non_blocked) {
    stats->average_runnable_processes_count_total += non_blocked;
}

void UpdateTotalMemoryReferences(statistics *stats, int references) {
    stats->total_memory_references = references;
}

void UpdateTotalPageFaults(statistics *stats) {
    stats->total_page_faults += 1;
}

void UpdateRunningTime(statistics *stats) {
    stats->run_time += 1;
}

void PrintStatistics(statistics *stats) {
    double amu = (stats->average_memory_utilization_count_total / (1.0 * stats->run_time));
    double arp = (stats->average_runnable_processes_count_total / (1.0 * stats->run_time));
    printf("Average Memory Utilization: %f\n"
           "Average Runnable Processes: %f\n"
           "Total Memory References: %d\n"
           "Total Page Faults: %d\n"
           "Running Time: %d",
           amu, arp, stats->total_memory_references, stats->total_page_faults, stats->run_time);
}
