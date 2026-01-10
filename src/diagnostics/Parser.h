#pragma once

#include <string>
#include <vector>
#include "diagnostics/Diagnostic.h"

class DiagnosticParser {
    public:
        std::vector<Diagnostic> parse(const std::vector<std::string>& lines);

    private:
        Diagnostic parse_line(const std::string& line);
};