#pragma once

#include <vector>
#include "diagnostics/Diagnostic.h"

class DiagnosticNormalizer {
    public:
        void normalize(std::vector<Diagnostic>& diagnostics);
};