#include <iostream>
#include <vector>
#include <string>

int number() {
    std::vector<std::string> lines = {"a", "b", "c"};
    for (int i = 0; i < lines.size(); i++) {
        std::cout << (i + 1) << ": " << lines[i] << std::endl;
    }
    return 0;
}