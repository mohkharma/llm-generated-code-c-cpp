#include <iostream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

// BFS function that prints traversal to the provided output stream
void bfs(const std::unordered_map<char, std::vector<char>>& graph, char start, std::ostream& out) {
    std::unordered_set<char> visited;
    std::queue<char> queue;

    queue.push(start);
    visited.insert(start);

    while (!queue.empty()) {
        char vertex = queue.front();
        queue.pop();
        out << vertex << " ";

        auto it = graph.find(vertex);
        if (it != graph.end()) {
            for (char neighbor : it->second) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    queue.push(neighbor);
                }
            }
        }
    }
}

// Run a test case: graph input, start node, expected BFS output string
bool runTest(const std::string& testName,
             const std::unordered_map<char, std::vector<char>>& graph,
             char start,
             const std::string& expectedOutput)
{
    std::stringstream ss;
    bfs(graph, start, ss);
    std::string actualOutput = ss.str();

    // Trim trailing spaces from actualOutput
    while (!actualOutput.empty() && actualOutput.back() == ' ') {
        actualOutput.pop_back();
    }

    if (actualOutput != expectedOutput) {
        std::cerr << testName << " Failed\n";
        std::cerr << "Expected: \"" << expectedOutput << "\"\n";
        std::cerr << "Got     : \"" << actualOutput << "\"\n";
        return false;
    }
    return true;
}

int main() {
    int failCount = 0;

    // Test graph from prompt
    std::unordered_map<char, std::vector<char>> graph = {
        {'A', {'B', 'C'}},
        {'B', {'A', 'D', 'E'}},
        {'C', {'A', 'F'}},
        {'D', {'B'}},
        {'E', {'B', 'F'}},
        {'F', {'C', 'E'}}
    };

    failCount += !runTest("Test Case 1 (start A)", graph, 'A', "A B C D E F");
    failCount += !runTest("Test Case 2 (start D)", graph, 'D', "D B A E C F");
    failCount += !runTest("Test Case 3 (start F)", graph, 'F', "F C E A B D");

    // Additional tests
    std::unordered_map<char, std::vector<char>> graph2 = {
        {'X', {'Y'}},
        {'Y', {'Z'}},
        {'Z', {}}
    };
    failCount += !runTest("Test Case 4 (linear X)", graph2, 'X', "X Y Z");
    failCount += !runTest("Test Case 5 (single node)", {{'M', {}}}, 'M', "M");

    if (failCount == 0)
        std::cout << "All test cases passed!\n";
    else
        std::cout << failCount << " test(s) failed.\n";

    return failCount;
}
