#include <iostream>
#include <string>
#include "cli/explain.h"

int main(int argc, char** argv) {
    if (argc < 2 || std::string(argv[1]) != "explain") {
        std::cerr << "Usage: cdiag explain\n";
        return 1;
    }

    // stdin → explain pipeline
    return run_explain();
}