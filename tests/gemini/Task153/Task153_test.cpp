#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

void breadthFirstSearch(const vector<list<int>>& graph, int startNode, ostream& out) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        out << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

bool runTest(const string& testName, const vector<list<int>>& graph, int startNode, const string& expectedOutput) {
    stringstream ss;
    breadthFirstSearch(graph, startNode, ss);
    string result = ss.str();
    while (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    if (result != expectedOutput) {
        cerr << testName << " Failed\nExpected: \"" << expectedOutput << "\"\nGot     : \"" << result << "\"\n";
        return false;
    }
    return true;
}

int main() {
    vector<list<int>> graph = {
        {1, 2},    // node 0
        {3, 4},    // node 1
        {5},       // node 2
        {},        // node 3
        {5},       // node 4
        {}         // node 5
    };

    int failCount = 0;
    failCount += !runTest("Test BFS from node 0", graph, 0, "0 1 2 3 4 5");
    failCount += !runTest("Test BFS from node 1", graph, 1, "1 3 4 5");
    failCount += !runTest("Test BFS from node 5", graph, 5, "5");

    if (failCount == 0) {
        cout << "All test cases passed!\n";
    } else {
        cout << failCount << " test(s) failed.\n";
    }

    return failCount;
}
