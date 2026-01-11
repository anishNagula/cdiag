#include <iostream>
#include <string>
#include <vector>

#include "diagnostics/Parser.h"
#include "diagnostics/Normalizer.h"
#include "diagnostics/Grouping.h"


int run_explain() {
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(std::cin, line)) {
        lines.push_back(line);
    }

    DiagnosticParser parser;
    auto diagnostics = parser.parse(lines);

    DiagnosticNormalizer normalizer;
    normalizer.normalize(diagnostics);

    DiagnosticGrouper grouper;
    auto groups = grouper.group(diagnostics);

    if (groups.empty()) {
        std::cout << "No compiler errors detected.\n";
    }

    DiagnosticGroup root = grouper.select_root(groups);

    std::cout << "Likely root cause\n";
    std::cout << "-----------------\n";
    std::cout << root.primary.file << ":" << root.primary.line << "\n";
    std::cout << root.primary.message << "\n";
    
    if (!root.primary.normalized_id.empty()) {
        std::cout << "[" << root.primary.normalized_id << "]\n";
    }

    std::cout << "\nSuppressed diagnostics: " << (groups.size() - 1) << "\n";

    return 0;
}