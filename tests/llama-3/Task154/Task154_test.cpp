#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <string>

class Graph {
public:
    Graph(int numNodes) : numNodes(numNodes), adjList(numNodes) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void dfs(int startNode, std::ostream& out) {
        std::vector<bool> visited(numNodes, false);
        dfsHelper(startNode, visited, out);
    }

private:
    void dfsHelper(int node, std::vector<bool>& visited, std::ostream& out) {
        visited[node] = true;
        out << node << " ";
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, visited, out);
            }
        }
    }

    int numNodes;
    std::vector<std::list<int>> adjList;
};

bool runTest() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    std::stringstream output;
    g.dfs(0, output);

    std::string expected = "0 1 3 2 4 ";
    std::string actual = output.str();

    if (actual == expected) {
        return true;
    } else {
        std::cerr << "Test failed.\nExpected: '" << expected << "'\nGot:      '" << actual << "'\n";
        return false;
    }
}

int main() {
    if (runTest()) {
        std::cout << "Test passed." << std::endl;
        return 0;
    } else {
        std::cout << "Test failed." << std::endl;
        return 1;
    }
}
