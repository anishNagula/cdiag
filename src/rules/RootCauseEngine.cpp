#include "rules/RootCauseEngine.h"

Explanation RootCauseEngine::explain(const DiagnosticGroup& root) {
    Explanation e;

    const std::string& id = root.primary.normalized_id;

    if (id == "EXPECTED_SEMICOLON") {
        e.title = "Missing semicolon after declaration";

        e.why =
            "C requires declarations to end with a semicolon. "
            "When it is missing, the compiler merges multiple declarations "
            "and loses track of where statements begin.";

        e.what_to_check = {
            "Check the line immediately before the reported error",
            "Ensure struct, enum, and typedef definitions end with ';'",
            "Look for macro expansions that may remove a semicolon"
        };

        e.confidence = "High — this error commonly triggers cascading diagnostics.";
        return e;
    }

    if (id == "EXPECTED_CLOSING_BRACE") {
        e.title = "Missing closing brace '}'";

        e.why =
            "An opening brace was not properly closed. "
            "This causes the compiler to treat large portions of the file "
            "as part of the same scope.";

        e.what_to_check = {
            "Check for an unmatched '{' earlier in the file",
            "Verify conditional compilation blocks (#if / #endif)",
            "Ensure braces inside macros are balanced"
        };

        e.confidence = "High — missing braces frequently cause widespread errors.";
        return e;
    }

    if (id == "IMPLICIT_FUNCTION_DECL") {
        e.title = "Function used without a prior declaration";

        e.why =
            "The function was called before the compiler saw a prototype. "
            "In C, this leads to implicit declarations and type mismatches.";

        e.what_to_check = {
            "Include the correct header file",
            "Add a function prototype before use",
            "Check for mismatched function names"
        };

        e.confidence = "Medium — may also indicate header ordering issues.";
        return e;
    }

    if (id == "UNKNOWN_TYPE_NAME") {
        e.title = "Unknown type name";

        e.why =
            "The compiler encountered a type identifier it does not recognize. "
            "This often occurs when a typedef or struct definition is missing or misplaced.";

        e.what_to_check = {
            "Ensure the type is declared before use",
            "Check for missing headers",
            "Verify conditional compilation guards"
        };

        e.confidence = "Medium — sometimes caused by earlier syntax errors.";
        return e;
    }

    // fallback
    e.title = "Unrecognized compiler error pattern";
    e.why =
        "The compiler reported an error that cdiag does not yet recognize. "
        "This may be a secondary effect of an earlier issue.";

    e.what_to_check = {
        "Inspect the first reported compiler error",
        "Check for syntax issues earlier in the file"
    };

    e.confidence = "Low — unsupported diagnostic pattern.";
    return e;
}