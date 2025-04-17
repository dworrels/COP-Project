//File to run test cases

#include "Graph.hpp"
#include <iostream>

// Define custom struct for edges
struct EdgeStruct {
    std::string from;
    std::string to;
    unsigned long weight;
};

void runGraph1() {
    Graph g;
    std::vector<std::string> vertices1 = { "1", "2", "3", "4", "5", "6" };
    std::vector<EdgeStruct> edges1 = {
        {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3", 10},
        {"2", "4", 15}, {"3", "4", 11}, {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9}
    };

    for (const auto& v : vertices1) g.addVertex(v);
    for (const auto& edge : edges1) g.addEdge(edge.from, edge.to, edge.weight);

    std::vector<std::string> path;
    unsigned long dist = g.shortestPath("1", "5", path);

    std::cout << "Graph 1 shortest path from 1 to 5:\n";
    std::cout << "Distance: " << dist << "\nPath: ";
    for (const auto& node : path) std::cout << node << " ";
    std::cout << "\n\n";
}

void runGraph2() {
    Graph g;
    std::vector<std::string> vertices2 = {
        "BSN", "LIB", "ENB", "MSC", "CAS", "SUB", "SUN"
    };
    std::vector<EdgeStruct> edges2 = {
        {"BSN", "LIB", 871}, {"BSN", "CAS", 1672}, {"BSN", "MSC", 2355},
        {"SUN", "SUB", 1265}, {"LIB", "MSC", 1615}, {"LIB", "SUN", 1847},
        {"ENB", "SUN", 2885}, {"ENB", "CAS", 454}, {"ENB", "LIB", 1078}
    };

    for (const auto& v : vertices2) g.addVertex(v);
    for (const auto& edge : edges2) g.addEdge(edge.from, edge.to, edge.weight);

    std::vector<std::string> path1;
    unsigned long dist1 = g.shortestPath("ENB", "SUN", path1);

    std::cout << "Graph 2 shortest path from ENB to SUN:\n";
    std::cout << "Distance: " << dist1 << "\nPath: ";
    for (const auto& node : path1) std::cout << node << " ";
    std::cout << "\n\n";

    std::vector<std::string> path2;
    unsigned long dist2 = g.shortestPath("LIB", "CAS", path2);

    std::cout << "Graph 2 shortest path from LIB to CAS:\n";
    std::cout << "Distance: " << dist2 << "\nPath: ";
    for (const auto& node : path2) std::cout << node << " ";
    std::cout << "\n";
}

int main()
{
    runGraph1();
    runGraph2();
    return 0;
}
