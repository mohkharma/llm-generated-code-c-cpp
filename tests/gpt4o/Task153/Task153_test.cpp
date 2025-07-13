#include <iostream>
#include <list>
#include <queue>
#include <map>
#include <set>
#include <sstream>
#include <string>

class Graph {
    std::map<int, std::list<int>> adj;

public:
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void bfs(int start, std::ostream& out) {
        std::set<int> visited;
        std::queue<int> queue;
        queue.push(start);
        visited.insert(start);

        while (!queue.empty()) {
            int node = queue.front();
            out << node << " ";
            queue.pop();

            for (int neighbour : adj[node]) {
                if (visited.find(neighbour) == visited.end()) {
                    queue.push(neighbour);
                    visited.insert(neighbour);
                }
            }
        }
    }
};

bool runTest(const std::string& testName, Graph& g, int start, const std::string& expected) {
    std::stringstream ss;
    g.bfs(start, ss);
    std::string actual = ss.str();
    while (!actual.empty() && actual.back() == ' ')
        actual.pop_back();

    if (actual != expected) {
        std::cerr << testName << " Failed\nExpected: \"" << expected << "\"\nGot     : \"" << actual << "\"\n";
        return false;
    }
    return true;
}

int main() {
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    int failCount = 0;
    failCount += !runTest("Test Case BFS from 2", g, 2, "2 0 3 1");
    failCount += !runTest("Test Case BFS from 0", g, 0, "0 1 2 3");
    failCount += !runTest("Test Case BFS from 3", g, 3, "3");

    if (failCount == 0)
        std::cout << "All test cases passed!\n";
    else
        std::cout << failCount << " test(s) failed.\n";

    return failCount;
}
