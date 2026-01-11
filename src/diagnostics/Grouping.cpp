#include "diagnostics/Grouping.h"

#include <stdexcept>

static bool is_syntax_error(const Diagnostic& d) {
    return d.normalized_id == "EXPECTED_SEMICOLON" ||
           d.normalized_id == "EXPECTED_CLOSING_BRACE";
}

std::vector<DiagnosticGroup>
DiagnosticGrouper::group(const std::vector<Diagnostic>& diagnostics) {
    std::vector<DiagnosticGroup> groups;
    DiagnosticGroup* current = nullptr;

    for (const auto& d : diagnostics) {
        if (d.severity == Severity::Note && current) {
            current->notes.push_back(d);
            continue;
        }

        if (d.severity == Severity::Error) {
            DiagnosticGroup g;
            g.primary = d;
            groups.push_back(g);
            current = &groups.back();
        } else {
            current = nullptr;
        }
    }

    return groups;
}

DiagnosticGroup
DiagnosticGrouper::select_root(const std::vector<DiagnosticGroup>& groups) {
    if (groups.empty()) {
        throw std::runtime_error("No error diagnostics found");
    }

    // rule-1 first syntax error wins
    for (const auto& g : groups) {
        if (is_syntax_error(g.primary)) {
            return g;
        }
    }

    // rule-2 fallback to first error
    return groups.front();
}