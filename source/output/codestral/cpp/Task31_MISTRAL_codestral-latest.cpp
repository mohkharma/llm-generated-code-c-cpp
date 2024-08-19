#include <string>
#include <unordered_map>

std::string DNAStrand(const std::string& dna) {
    std::unordered_map<char, char> complement = {{'A', 'T'}, {'T', 'A'}, {'C', 'G'}, {'G', 'C'}};
    std::string result;
    for (char base : dna) {
        result += complement[base];
    }
    return result;
}