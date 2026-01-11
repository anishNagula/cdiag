#include <iostream>
#include <string>
#include <vector>

#include "diagnostics/Parser.h"
#include "diagnostics/Normalizer.h"
#include "diagnostics/Grouping.h"
#include "rules/RootCauseEngine.h"


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

    RootCauseEngine engine;
    Explanation e = engine.explain(root);

    std::cout << "Likely root cause\n";
    std::cout << "-----------------\n";
    std::cout << e.title << "\n\n";

    std::cout << "Why this happens:\n";
    std::cout << "  " << e.why << "\n\n";

    std::cout << "What to check next:\n";
    for (const auto& item : e.what_to_check) {
        std::cout << "  • " << item << "\n";
    }

    std::cout << "\nConfidence:\n";
    std::cout << "  " << e.confidence << "\n";

    std::cout << "\nSuppressed diagnostics: " << (groups.size() - 1) << "\n";

    return 0;
}