#include "diagnostics/Parser.h"

#include <regex>

static Severity parse_severity(const std::string& s) {
    if (s == "error") return Severity::Error;
    if (s == "warning") return Severity::Warning;
    if (s == "note") return Severity::Note;
    return Severity::Unknown;
}

std::vector<Diagnostic>
DiagnosticParser::parse(const std::vector<std::string>& lines) {
    std::vector<Diagnostic> diagnostics;

    for (const auto& line : lines) {
        Diagnostic d = parse_line(line);
        if (d.severity != Severity::Unknown) {
            diagnostics.push_back(d);
        }
    }

    return diagnostics;
}

Diagnostic DiagnosticParser::parse_line(const std::string& line) {
    Diagnostic d;

    static const std::regex with_col(
        R"(^(.*?):(\d+):(\d+):\s*(error|warning|note):\s*(.*)$)"
    );

    static const std::regex no_col(
        R"(^(.*?):(\d+):\s*(error|warning|note):\s*(.*)$)"
    );

    std::smatch m;

    if (std::regex_match(line, m, with_col)) {
        d.file     = m[1];
        d.line     = std::stoi(m[2]);
        d.column   = std::stoi(m[3]);
        d.severity = parse_severity(m[4]);
        d.message  = m[5];
        return d;
    }

    if (std::regex_match(line, m, no_col)) {
        d.file     = m[1];
        d.line     = std::stoi(m[2]);
        d.severity = parse_severity(m[3]);
        d.message  = m[4];
        return d;
    }

    return d;
}