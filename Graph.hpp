//To compile g++ main.cpp Graph.cpp

#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include "HeapQueue.hpp"

struct Edge {
    std::string label;
    unsigned long weight;
};

class Graph : public GraphBase {
public:
    void addVertex(std::string label) override;
    void removeVertex(std::string label) override;
    void addEdge(std::string label1, std::string label2, unsigned long weight) override;
    void removeEdge(std::string label1, std::string label2) override;
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path) override;

private:
    struct Vertex {
        std::string label;
        std::vector<Edge> adj;
    };

    std::vector<Vertex> vertices;

    int findVertexIndex(const std::string& label) const;
    bool edgeExists(const std::string& label1, const std::string& label2) const;
};

#endif