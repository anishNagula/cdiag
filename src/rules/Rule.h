#pragma once

#include <vector>
#include <string>

struct Explanation {
    std::string title;
    std::string why;
    std::vector<std::string> what_to_check;
    std::string confidence;
};