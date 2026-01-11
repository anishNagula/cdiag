#pragma once

#include <vector>
#include "diagnostics/Diagnostic.h"

struct DiagnosticGroup {
    Diagnostic primary;
    std::vector<Diagnostic> notes;
};

class DiagnosticGrouper {
    public:
        // group diagnostics and return candidate root cause
        std::vector<DiagnosticGroup> group(const std::vector<Diagnostic>& diagnostics);

        // select most likely root cause group
        DiagnosticGroup select_root(const std::vector<DiagnosticGroup>& groups);
};