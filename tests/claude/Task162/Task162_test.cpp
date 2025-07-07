// TaskDijkstra_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <unordered_map>
#include <limits>
#include <cassert>
#include <vector>
#include <algorithm>   // <-- Add this

using namespace std;

typedef pair<int, string> pis;

unordered_map<string, int> dijkstra(const unordered_map<string, unordered_map<string, int>>& graph, const string& start) {
    unordered_map<string, int> distances;
    for (const auto& node : graph) {
        distances[node.first] = numeric_limits<int>::max();
    }
    distances[start] = 0;

    priority_queue<pis, vector<pis>, greater<pis>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        string current_node = pq.top().second;
        pq.pop();

        if (current_distance > distances[current_node]) {
            continue;
        }

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

// This function parses the input graph and starting node from stringstream,
// runs Dijkstra, and outputs distances in sorted key order for deterministic output.
string runProgram(const string& input) {
    stringstream in(input);
    stringstream out;

    // Read number of nodes
    int n;
    out << "Enter number of nodes: ";
    in >> n;

    // Read nodes names
    vector<string> nodes(n);
    out << "Enter node names:\n";
    for (int i = 0; i < n; ++i) {
        in >> nodes[i];
    }

    // Read number of edges
    int m;
    out << "Enter number of edges: ";
    in >> m;

    unordered_map<string, unordered_map<string, int>> graph;
    for (const auto& node : nodes) {
        graph[node] = unordered_map<string,int>{};
    }

    out << "Enter edges (from to weight):\n";
    for (int i = 0; i < m; ++i) {
        string u, v;
        int w;
        in >> u >> v >> w;
        graph[u][v] = w;
    }

    // Read start node
    string start;
    out << "Enter start node: ";
    in >> start;

    unordered_map<string, int> shortest_paths = dijkstra(graph, start);

    // Output distances sorted by node name
    vector<string> sorted_nodes = nodes;
    sort(sorted_nodes.begin(), sorted_nodes.end());
    for (const string& node : sorted_nodes) {
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
        // Sample graph same as Python example
        string input =
            "5\n"
            "A B C D E\n"
            "7\n"
            "A B 4\n"
            "A C 2\n"
            "B D 3\n"
            "B E 1\n"
            "C B 1\n"
            "C D 5\n"
            "D E 2\n"
            "A\n";
        string expected =
            "Enter number of nodes: "
            "Enter node names:\n"
            "Enter number of edges: "
            "Enter edges (from to weight):\n"
            "Enter start node: "
            "A: 0\n"
            "B: 3\n"
            "C: 2\n"
            "D: 6\n"
            "E: 4\n";
        string output = runProgram(input);
        assert(output == expected);
    }

    {
        // Graph with unreachable node
        string input =
            "3\n"
            "X Y Z\n"
            "2\n"
            "X Y 5\n"
            "Y X 5\n"
            "X\n";
        string expected =
            "Enter number of nodes: "
            "Enter node names:\n"
            "Enter number of edges: "
            "Enter edges (from to weight):\n"
            "Enter start node: "
            "X: 0\n"
            "Y: 5\n"
            "Z: INF\n";
        string output = runProgram(input);
        assert(output == expected);
    }
}

int main() {
    test();
    cout << "All tests passed successfully.\n";
    return 0;
}
