#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

class Graph {
public:
    int numNodes;
    vector<vector<int>> adjList;

    Graph(int numNodes) {
        this->numNodes = numNodes;
        this->adjList.resize(numNodes);
    }

    void addEdge(int u, int v) {
        this->adjList[u].push_back(v);
    }

    void bfs(int startNode, ostream& out) {
        vector<bool> visited(numNodes, false);
        queue<int> q;

        q.push(startNode);
        visited[startNode] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            out << node << " ";

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
};

bool runTest(const string& testName, Graph& g, int startNode, const string& expected) {
    stringstream ss;
    g.bfs(startNode, ss);
    string actual = ss.str();
    while (!actual.empty() && actual.back() == ' ')
        actual.pop_back();

    if (actual != expected) {
        cerr << testName << " Failed\nExpected: \"" << expected << "\"\nGot     : \"" << actual << "\"\n";
        return false;
    }
    return true;
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    int failCount = 0;
    failCount += !runTest("Test BFS from 0", g, 0, "0 1 2 3 4");
    failCount += !runTest("Test BFS from 1", g, 1, "1 3");
    failCount += !runTest("Test BFS from 2", g, 2, "2 4");
    failCount += !runTest("Test BFS from 3", g, 3, "3");
    failCount += !runTest("Test BFS from 4", g, 4, "4");

    if (failCount == 0)
        cout << "All test cases passed!\n";
    else
        cout << failCount << " test(s) failed.\n";

    return failCount;
}
