#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

void depthFirstSearch(const unordered_map<char, vector<char>>& graph, char startNode, ostream& out) {
    unordered_set<char> visited;
    stack<char> stack;
    stack.push(startNode);

    while (!stack.empty()) {
        char node = stack.top();
        stack.pop();
        if (visited.find(node) == visited.end()) {
            visited.insert(node);
            out << node << " ";

            for (int i = graph.at(node).size() - 1; i >= 0; --i) {
                char neighbor = graph.at(node)[i];
                if (visited.find(neighbor) == visited.end()) {
                    stack.push(neighbor);
                }
            }
        }
    }
}

bool runTest() {
    unordered_map<char, vector<char>> graph = {
        {'A', {'B', 'C'}},
        {'B', {'D', 'E'}},
        {'C', {'F'}},
        {'D', {}},
        {'E', {'F'}},
        {'F', {}}
    };

    stringstream output;
    depthFirstSearch(graph, 'A', output);

    string expected = "A B D E F C ";

    string actual = output.str();

    if (actual == expected) {
        return true;
    } else {
        cerr << "Test failed.\nExpected output: '" << expected << "'\nActual output:   '" << actual << "'" << endl;
        return false;
    }
}

int main() {
    if (runTest()) {
        cout << "Test passed." << endl;
        return 0;
    } else {
        cout << "Test failed." << endl;
        return 1;
    }
}
