// TaskDijkstra_Test_Fixed.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <unordered_map>
#include <limits>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, string> P;

unordered_map<string, unordered_map<string, int>> graph = {
    {"A", {{"B", 1}, {"C", 4}}},
    {"B", {{"A", 1}, {"C", 2}, {"D", 5}}},
    {"C", {{"A", 4}, {"B", 2}, {"D", 1}}},
    {"D", {{"B", 5}, {"C", 1}}}
};

unordered_map<string, int> dijkstra(const string& start) {
    priority_queue<P, vector<P>, greater<P>> pq;
    unordered_map<string, int> distances;
    for (const auto& node : graph) {
        distances[node.first] = numeric_limits<int>::max();
    }
    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        string current_node = pq.top().second;
        pq.pop();

        if (current_distance > distances[current_node])
            continue;

        for (const auto& neighbor : graph.at(current_node)) {
            int distance = current_distance + neighbor.second;
            if (distance < distances[neighbor.first]) {
                distances[neighbor.first] = distance;
                pq.push({distance, neighbor.first});
            }
        }
    }
    return distances;
}

// We simulate input/output so the test is fully self-contained and matches the python test case behavior
string runProgram(const string& input) {
    stringstream in(input);
    stringstream out;

    // Since graph is hardcoded, just read start node from input
    out << "Enter start node: ";
    string start;
    in >> start;

    unordered_map<string, int> shortest_paths = dijkstra(start);

    // Output sorted by node name for consistent order
    vector<string> nodes;
    for (const auto& kv : graph) nodes.push_back(kv.first);
    sort(nodes.begin(), nodes.end());

    for (const string& node : nodes) {
        out << node << ": ";
        if (shortest_paths[node] == numeric_limits<int>::max())
            out << "INF";
        else
            out << shortest_paths[node];
        out << "\n";
    }
    return out.str();
}

void test() {
    {
        string input = "A\n";
        string expected =
            "Enter start node: "
            "A: 0\n"
            "B: 1\n"
            "C: 3\n"
            "D: 4\n";
        assert(runProgram(input) == expected);
    }
    {
        string input = "B\n";
        string expected =
            "Enter start node: "
            "A: 1\n"
            "B: 0\n"
            "C: 2\n"
            "D: 3\n";
        assert(runProgram(input) == expected);
    }
}

int main() {
    test();
    cout << "All tests passed successfully.\n";
    return 0;
}
