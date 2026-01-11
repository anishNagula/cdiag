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

        if (d.severity == Severity::Error || d.severity == Severity::Warning) {
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

    // rule-1 syntax errors always win
    for (const auto& g : groups) {
        if (g.primary.normalized_id == "EXPECTED_SEMICOLON" ||
            g.primary.normalized_id == "EXPECTED_CLOSING_BRACE") {
            return g;
        }
    }

    // rule-2 implicit declaration warning explains conflicting types
    for (size_t i = 0; i + 1 < groups.size(); ++i) {
        if (groups[i].primary.normalized_id == "IMPLICIT_FUNCTION_DECL" &&
            groups[i + 1].primary.normalized_id == "CONFLICTING_TYPES") {
            return groups[i];
        }
    }

    // rule-3 fallback to first error
    return groups.front();
}