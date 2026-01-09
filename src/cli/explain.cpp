#include <iostream>
#include <string>
#include <vector>

int run_explain() {
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(std::cin, line)) {
        lines.push_back(line);
    }

    std::cout << "[diagnostics read: " << lines.size() << " lines]\n";

    return 0;
}