#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

void dfs(unordered_map<char, vector<char>>& graph, char node, unordered_set<char>& visited, ostream& out) {
    if (visited.find(node) == visited.end()) {
        visited.insert(node);
        out << node << " ";
        for (char neighbour : graph[node]) {
            dfs(graph, neighbour, visited, out);
        }
    }
}

bool runTest() {
    unordered_map<char, vector<char>> graph = {
        {'A', {'B', 'C'}},
        {'B', {'A', 'D', 'E'}},
        {'C', {'A', 'F'}},
        {'D', {'B'}},
        {'E', {'B', 'F'}},
        {'F', {'C', 'E'}}
    };

    unordered_set<char> visited;
    stringstream output;

    dfs(graph, 'A', visited, output);

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
