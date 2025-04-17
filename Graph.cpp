// This one

#include "Graph.hpp"

// Define a constant for max value
const unsigned long MAX_WEIGHT = 1000000000; // A large value for the "infinity"

void Graph::addVertex(std::string label) {
    if (findVertexIndex(label) != -1) return;
    vertices.push_back({label, {}});
}

void Graph::removeVertex(std::string label) {
    int idx = findVertexIndex(label);
    if (idx == -1) return;

    vertices.erase(vertices.begin() + idx);
    for (auto& vertex : vertices) {
        // Manually remove the edge from adj list
        for (auto it = vertex.adj.begin(); it != vertex.adj.end(); ) {
            if (it->label == label) {
                it = vertex.adj.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    if (label1 == label2) return;
    int i = findVertexIndex(label1);
    int j = findVertexIndex(label2);
    if (i == -1 || j == -1 || edgeExists(label1, label2)) return;

    vertices[i].adj.emplace_back(Edge{label2, weight});
    vertices[j].adj.emplace_back(Edge{label1, weight});
}

void Graph::removeEdge(std::string label1, std::string label2) {
    int i = findVertexIndex(label1);
    int j = findVertexIndex(label2);
    if (i == -1 || j == -1) return;

    // Manually remove the edge from adj list
    for (auto it = vertices[i].adj.begin(); it != vertices[i].adj.end(); ) {
        if (it->label == label2) {
            it = vertices[i].adj.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = vertices[j].adj.begin(); it != vertices[j].adj.end(); ) {
        if (it->label == label1) {
            it = vertices[j].adj.erase(it);
        } else {
            ++it;
        }
    }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path) {
    std::vector<std::pair<unsigned long, std::string>> dist; // Stores distances (using label and distance)
    std::vector<std::string> prev(vertices.size(), ""); // To store previous vertices for path

    // Initialize distances to "infinity"
    for (const auto& vertex : vertices) {
        dist.push_back({MAX_WEIGHT, vertex.label});
    }
    dist[findVertexIndex(startLabel)].first = 0; // Distance from start to itself is 0

    // Initialize the visited array
    std::vector<bool> visited(vertices.size(), false);

    // Start Dijkstra's algorithm (no priority queue, linear search for min dist)
    for (size_t i = 0; i < vertices.size(); ++i) {
        // Find the vertex with the smallest distance
        unsigned long minDist = MAX_WEIGHT;
        int u = -1;
        for (size_t j = 0; j < dist.size(); ++j) {
            if (!visited[j] && dist[j].first < minDist) {
                minDist = dist[j].first;
                u = j;
            }
        }

        if (u == -1) break; // All reachable vertices have been visited

        visited[u] = true;
        std::string currLabel = dist[u].second;
        int vertexIndex = findVertexIndex(currLabel);

        // Update distances to neighboring vertices
        for (const auto& edge : vertices[vertexIndex].adj) {
            int v = findVertexIndex(edge.label);
            if (visited[v]) continue; // Skip visited vertices

            unsigned long alt = dist[u].first + edge.weight;
            if (alt < dist[v].first) {
                dist[v].first = alt;
                prev[v] = currLabel;
            }
        }
    }

    // Reconstruct the shortest path
    path.clear();
    std::string curr = endLabel;
    int endIndex = findVertexIndex(curr);

    if (dist[endIndex].first == MAX_WEIGHT) {
        return MAX_WEIGHT; // no path found
    }

    while (curr != startLabel) {
        path.insert(path.begin(), curr);
        curr = prev[findVertexIndex(curr)];
    }
    path.insert(path.begin(), startLabel);

    return dist[findVertexIndex(endLabel)].first;
}

int Graph::findVertexIndex(const std::string& label) const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i].label == label) return static_cast<int>(i);
    }
    return -1;
}

bool Graph::edgeExists(const std::string& label1, const std::string& label2) const {
    int i = findVertexIndex(label1);
    if (i == -1) return false;
    for (const auto& edge : vertices[i].adj) {
        if (edge.label == label2) return true;
    }
    return false;
}
