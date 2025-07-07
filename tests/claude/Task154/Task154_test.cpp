#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> graph;

    void dfsUtil(int v, unordered_set<int>& visited, ostream& out) {
        visited.insert(v);
        out << v << " ";

        for (int neighbour : graph[v]) {
            if (visited.find(neighbour) == visited.end()) {
                dfsUtil(neighbour, visited, out);
            }
        }
    }

public:
    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }

    void dfs(int v, ostream& out) {
        unordered_set<int> visited;
        dfsUtil(v, visited, out);
    }
};

// Function to simulate the Python test logic exactly
bool runTest() {
    // Simulated input is fixed, so no input reading needed.
    // We build the graph as per the Python code
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    // Capture output into a stringstream
    stringstream output;
    output << "Depth First Traversal (starting from vertex 2):\n";
    g.dfs(2, output);

    string expected = "Depth First Traversal (starting from vertex 2):\n2 0 1 2 3 3 ";


    expected = "Depth First Traversal (starting from vertex 2):\n2 0 1 3 ";

    string actual = output.str();

    if (actual == expected) {
        return true;
    } else {
        cerr << "Test failed.\nExpected output:\n" << expected
             << "\nActual output:\n" << actual << endl;
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
