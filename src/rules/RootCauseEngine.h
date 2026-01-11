#pragma once

#include "diagnostics/Grouping.h"
#include "rules/Rule.h"

class RootCauseEngine {
    public:
        Explanation explain(const DiagnosticGroup& root);
};