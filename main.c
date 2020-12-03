#include <stdio.h>
#include <stdlib.h>
#include "process_options.h"
#include "process.h"
#include "page_table.h"
#include "inverted_page_table.h"


int main(int argc, char *argv[]) {
    //Parse the program arguments. If provided else consider the default ones
    options *opt = process_options(argc, argv);
    char *filepath = opt->filepath;
    int p_arg = opt->p;
    int m_arg = opt->m;

    // Parse trace file here
    void *process_root = ParseTraceFile(filepath);

    // Create inverted page Table with max_pages
    int max_pages = m_arg / p_arg;
    void *ipt_root = CreateInvertedPageTable(max_pages);

    RunSimulation(filepath, process_root, ipt_root);

    return 0;
}
