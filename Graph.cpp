#include "Graph.hpp"

//Constant to hold value for "infinity"
const unsigned long MAX_WEIGHT = 1000000000;

//Adds a vertex with the given label if it doesn't already exist on graph
void Graph::addVertex(std::string label)
{
    if (findVertexIndex(label) != -1)   //Vertex exists already
        return;

    vertices.push_back({label, {}});
}

//Removes specified vertex and its edges from graph
void Graph::removeVertex(std::string label)
{
    int idx = findVertexIndex(label);
    if (idx == -1) return;  //Vertex DNE

    vertices.erase(vertices.begin() + idx); //Remove vertex

    for (auto& vertex : vertices)   //Remove edges of vertex
    {
        for (auto it = vertex.adj.begin(); it != vertex.adj.end(); )
        {
            if (it->label == label)
                it = vertex.adj.erase(it);  //Remove edge
            else
                ++it;
        }
    }
}

//Adds an edge between two vertices with specified weight
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
    if (label1 == label2) return;   //Prevents self loops

    int i = findVertexIndex(label1);
    int j = findVertexIndex(label2);
    
    if (i == -1 || j == -1 || edgeExists(label1, label2))   //Invalid vertices or edge already exists
        return;

    //Add edge to both vertices
    vertices[i].adj.emplace_back(Edge{label2, weight});
    vertices[j].adj.emplace_back(Edge{label1, weight});
}

//Removes an edge between two vertices
void Graph::removeEdge(std::string label1, std::string label2)
{
    int i = findVertexIndex(label1);
    int j = findVertexIndex(label2);
    if (i == -1 || j == -1) //Vertices DNE
        return;

    //Removes edge from vertex i -> j
    for (auto it = vertices[i].adj.begin(); it != vertices[i].adj.end(); )
    {
        if (it->label == label2)
            it = vertices[i].adj.erase(it);
        else
            ++it;
    }

    //Removes edge from vertex j -> i
    for (auto it = vertices[j].adj.begin(); it != vertices[j].adj.end(); )
    {
        if (it->label == label1)
            it = vertices[j].adj.erase(it);
        else
            ++it;
    }
}

//Dijkstra's algorithm to find the shortest path between vertices
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path)
{
    std::vector<std::pair<unsigned long, std::string>> dist; //(Distance, Label) pairs
    std::vector<std::string> prev(vertices.size(), ""); //Store previous vertices for path

    // Initialize distances to "infinity"
    for (const auto& vertex : vertices)
    {
        dist.push_back({MAX_WEIGHT, vertex.label});
    }
    dist[findVertexIndex(startLabel)].first = 0;    //Distance to start vertex = 0

    //Array to track visitied vertices
    std::vector<bool> visited(vertices.size(), false);

    //Loop for Dijkstra's algorithm
    for (size_t i = 0; i < vertices.size(); ++i) 
    {
        //Find the vertex with the smallest distance
        unsigned long minDist = MAX_WEIGHT;
        int u = -1;

        for (size_t j = 0; j < dist.size(); ++j)
        {
            if (!visited[j] && dist[j].first < minDist)
            {
                minDist = dist[j].first;
                u = j;
            }
        }

        if (u == -1) break; //All reachable vertices have been visited

        visited[u] = true;
        std::string currLabel = dist[u].second;
        int vertexIndex = findVertexIndex(currLabel);

        //Update distances for neighboring vertices
        for (const auto& edge : vertices[vertexIndex].adj)
        {
            int v = findVertexIndex(edge.label);

            if (visited[v])
            continue;   //Skip visited vertices

            unsigned long alt = dist[u].first + edge.weight;
            if (alt < dist[v].first)
            {
                dist[v].first = alt;
                prev[v] = currLabel;
            }
        }
    }

    //Reconstruct the shortest path end to start labels
    path.clear();
    std::string curr = endLabel;
    int endIndex = findVertexIndex(curr);

    if (dist[endIndex].first == MAX_WEIGHT)
        return MAX_WEIGHT;  //No path found

    //Go back from end to start
    while (curr != startLabel)
    {
        path.insert(path.begin(), curr);
        curr = prev[findVertexIndex(curr)];
    }
    path.insert(path.begin(), startLabel);

    return dist[findVertexIndex(endLabel)].first; //Return weight of the shortest path
}

//Finds the index of a vertex by label
int Graph::findVertexIndex(const std::string& label) const
{
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        if (vertices[i].label == label)
            return static_cast<int>(i);
    }
    return -1;  //Vertex not found
}

//Checks if an edge exists between two vertices
bool Graph::edgeExists(const std::string& label1, const std::string& label2) const
{
    int i = findVertexIndex(label1);

    if (i == -1)
        return false;

    for (const auto& edge : vertices[i].adj)
    {
        if (edge.label == label2)
            return true;
    }
    return false;
}
