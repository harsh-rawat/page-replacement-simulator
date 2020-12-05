#include "process_options.h"
#include "process.h"

#if USE_MODULE == FIFO
fifo_module *page_replacement_algo = NULL;
#elif USE_MODULE == LRU
fifo_module *page_replacement_algo = NULL;
#else
clock_pra *page_replacement_algo = NULL;
#endif

void initialize_page_replacement_algo(int max_pages);

int main(int argc, char *argv[]) {
    //Parse the program arguments. If provided else consider the default ones
    options *opt = process_options(argc, argv);
    char *filepath = opt->filepath;
    int p_arg = opt->p;
    int m_arg = opt->m;

    // Create inverted page Table with max_pages
    int max_pages = m_arg / p_arg;

    //Create stats module
    statistics *stats = CreateStatistics(max_pages);

    // Parse trace file here
    void *process_root = ParseTraceFile(filepath, stats);

    void *ipt_root = CreateInvertedPageTable(max_pages);

    initialize_page_replacement_algo(max_pages);

    RunSimulation(filepath, process_root, ipt_root, stats);

    PrintStatistics(stats);

    return 0;
}

#if USE_MODULE == CLOCK
void initialize_page_replacement_algo(int max_pages){
    page_replacement_algo = CreateClockPRAModule(max_pages);
}
#else
void initialize_page_replacement_algo(int max_pages){
    page_replacement_algo = CreateFIFOModule(max_pages);
}
#endif