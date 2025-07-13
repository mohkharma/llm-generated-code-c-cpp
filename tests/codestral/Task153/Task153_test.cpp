#include <iostream>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <sstream>
#include <string>

void bfs(const std::map<char, std::list<char>>& graph, char start, std::ostream& out) {
    std::set<char> visited;
    std::queue<char> queue;

    visited.insert(start);
    queue.push(start);

    while (!queue.empty()) {
        char node = queue.front();
        out << node << " ";
        queue.pop();

        for (char neighbor : graph.at(node)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue.push(neighbor);
            }
        }
    }
}

bool runTest(const std::string& testName,
             const std::map<char, std::list<char>>& graph,
             char start,
             const std::string& expectedOutput) {
    std::stringstream ss;
    bfs(graph, start, ss);
    std::string actualOutput = ss.str();
    while (!actualOutput.empty() && actualOutput.back() == ' ') {
        actualOutput.pop_back();
    }

    if (actualOutput != expectedOutput) {
        std::cerr << testName << " Failed\nExpected: \"" << expectedOutput
                  << "\"\nGot     : \"" << actualOutput << "\"\n";
        return false;
    }
    return true;
}

int main() {
    int failCount = 0;

    std::map<char, std::list<char>> graph = {
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

    if (failCount == 0) {
        std::cout << "All test cases passed!\n";
    } else {
        std::cout << failCount << " test(s) failed.\n";
    }

    return failCount;
}
