#include <iostream>
#include <string>
#include <vector>

#include "diagnostics/Parser.h"

int run_explain() {
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(std::cin, line)) {
        lines.push_back(line);
    }

    DiagnosticParser parser;
    auto diagnostics = parser.parse(lines);

    std::cout << "[parsed diagnostics: " << diagnostics.size() << "]\n";

    for (const auto& d : diagnostics) {
        std::cout << d.file << ":" << d.line << " ";

        switch (d.severity) {
            case Severity::Error:   std::cout << "error"; break;
            case Severity::Warning: std::cout << "warning"; break;
            case Severity::Note:    std::cout << "note"; break;
            default:                std::cout << "unknown"; break;
        }

        std::cout << ":" << d.message << "\n";
    }

    return 0;
}