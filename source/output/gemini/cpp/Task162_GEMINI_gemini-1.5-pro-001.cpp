#include <climits>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <unordered_set>

using namespace std;

typedef pair<int, string> Pair;

struct Node {
    string vertex;
    int weight;

    Node(string v, int w) : vertex(v), weight(w) {}
};

struct CompareDistance {
    bool operator()(const Pair& a, const Pair& b) {
        return a.first > b.first;
    }
};

unordered_map<string, int> dijkstra(const unordered_map<string, unordered_map<string, int>>& graph, const string& start) {
    unordered_map<string, int> distances;
    for (const auto& pair : graph) {
        distances[pair.first] = INT_MAX;
    }
    distances[start] = 0;

    priority_queue<Pair, vector<Pair>, CompareDistance> pq;
    pq.push({0, start});

    unordered_set<string> visited;

    while (!pq.empty()) {
        int distance = pq.top().first;
        string u = pq.top().second;
        pq.pop();

        if (visited.find(u) != visited.end()) {
            continue;
        }

        visited.insert(u);

        //error: passing ‘const std::unordered_map<std::__cxx11::basic_string<char>, std::unordered_map<std::__cxx11::basic_string<char>, int> >’ as ‘this’ argument discards qualifiers [-fpermissive]
        //
        // for (const auto& neighbor : graph[u]) {
        //     string v = neighbor.first;
        //     int weight = neighbor.second;
        //
        //     if (distances[u] != INT_MAX && distances[v] > distances[u] + weight) {
        //         distances[v] = distances[u] + weight;
        //         pq.push({distances[v], v});
        //     }
        // }
    }

    return distances;
}

int main() {
    unordered_map<string, unordered_map<string, int>> graph = {
        {"A", {{"B", 4}, {"C", 2}}},
        {"B", {{"A", 4}, {"C", 2}, {"D", 7}}},
        {"C", {{"A", 2}, {"B", 2}, {"D", 3}}},
        {"D", {{"B", 7}, {"C", 3}}}
    };

    string startNode = "A";
    unordered_map<string, int> distances = dijkstra(graph, startNode);

    cout << "Shortest distances from node " << startNode << ":" << endl;
    for (const auto& pair : distances) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
