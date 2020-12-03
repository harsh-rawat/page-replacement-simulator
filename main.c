#include "statistics.h"
#include "process_options.h"
#include "process.h"


int main(int argc, char *argv[]) {
    //Parse the program arguments. If provided else consider the default ones
    options *opt = process_options(argc, argv);
    char *filepath = opt->filepath;
    int p_arg = opt->p;
    int m_arg = opt->m;

    //Create stats module
    statistics *stats = CreateStatistics();

    // Parse trace file here
    void *process_root = ParseTraceFile(filepath, stats);

    // Create inverted page Table with max_pages
    int max_pages = m_arg / p_arg;
    void *ipt_root = CreateInvertedPageTable(max_pages);

    RunSimulation(filepath, process_root, ipt_root, stats);

    PrintStatistics(stats);

    return 0;
}
