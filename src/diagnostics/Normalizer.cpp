#include "diagnostics/Normalizer.h"

#include <regex>

void DiagnosticNormalizer::normalize(std::vector<Diagnostic>& diagnostics) {
    static const std::regex expected_semicolon(
        "expected.*;"
    );
    
    static const std::regex expected_closing_brace(
        "expected.*\\}"
    );
    
    static const std::regex implicit_function_decl(
        "implicit declaration of function"
    );
    
    static const std::regex unknown_type_name(
        "unknown type name"
    );
    
    static const std::regex conflicting_types(
        "conflicting types for"
    );

    for (auto& d : diagnostics) {
        const std::string& msg = d.message;
        
        if (std::regex_search(msg, expected_semicolon)) {
            d.normalized_id = "EXPECTED_SEMICOLON";
        } else if (std::regex_search(msg, expected_closing_brace)) {
            d.normalized_id = "EXPECTED_CLOSING_BRACE";
        } else if (std::regex_search(msg, implicit_function_decl)) {
            d.normalized_id = "IMPLICIT_FUNCTION_DECL";
        } else if (std::regex_search(msg, unknown_type_name)) {
            d.normalized_id = "UNKNOWN_TYPE_NAME";
        } else if (std::regex_search(msg, conflicting_types)) {
            d.normalized_id = "CONFLICTING_TYPES";
        } else {
            d.normalized_id.clear();     // unknown or unsupported command
        } 
    }
}