// TaskDijkstra_Test_StructNode.cpp
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

struct Node {
    string name;
    int distance;
    bool operator<(const Node& other) const {
        return distance > other.distance; // min-heap
    }
};

unordered_map<string, unordered_map<string, int>> graph = {
    {"A", {{"B", 1}, {"C", 4}}},
    {"B", {{"A", 1}, {"C", 2}, {"D", 5}}},
    {"C", {{"A", 4}, {"B", 2}, {"D", 1}}},
    {"D", {{"B", 5}, {"C", 1}}}
};

unordered_map<string, int> dijkstra(unordered_map<string, unordered_map<string, int>> graph, string start) {
    unordered_map<string, int> distances;
    for (auto& node : graph) {
        distances[node.first] = numeric_limits<int>::max();
    }
    distances[start] = 0;

    priority_queue<Node> pq;
    pq.push({start, 0});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.distance > distances[current.name]) {
            continue;
        }

        for (auto& neighbor : graph[current.name]) {
            int dist = current.distance + neighbor.second;
            if (dist < distances[neighbor.first]) {
                distances[neighbor.first] = dist;
                pq.push({neighbor.first, dist});
            }
        }
    }
    return distances;
}

// Test harness that simulates input/output with stringstream
string runProgram(const string& input) {
    stringstream in(input);
    stringstream out;

    out << "Enter start node: ";
    string start;
    in >> start;

    unordered_map<string, int> shortest_paths = dijkstra(graph, start);

    vector<string> nodes;
    for (const auto& p : graph) nodes.push_back(p.first);
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
