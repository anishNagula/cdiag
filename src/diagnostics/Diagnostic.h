#pragma once

#include <string>

enum class Severity {
    Error,
    Warning,
    Note,
    Unknown
};

struct Diagnostic {
    std::string file;       // source file path
    int line = -1;          // line number
    int column = -1;        // column number

    Severity severity = Severity::Unknown;
    std::string message;    // compiler message


    std::string normalized_id;
};