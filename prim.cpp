//All procedures including main
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
class graph
{
    public:
        graph(int vertices);
        ~graph();
        void addEdge(int u, int v, int weight);
        void prim();
        void printMST(const std::vector<int>& parent);
    private:
        int V; // number of vertices
        std::vector<std::list<int>> adjList; // adjacency list
        std::vector<std::vector<int>> weights; // edge weights
};

graph::graph(int vertices)
    : V(vertices),
      adjList(vertices),
      weights(vertices, std::vector<int>(vertices, 0))
{
}

graph::~graph() = default;

void graph::addEdge(int u, int v, int weight) {
    adjList[u].push_back(v);
    adjList[v].push_back(u); // For undirected graph
    weights[u][v] = weight;
    weights[v][u] = weight; // For undirected graph
}

void graph::prim() {
    if (V == 0) return; // No vertices in the graph

    std::vector<bool> visited(V, false); // Track visited vertices
    std::vector<int> parent(V, -1); // Store the parent of each vertex
    
    // Priority queue: {weight, u, v} where u is source, v is destination
    // Using greater to make it min-heap
    using T = std::tuple<int, int, int>;
    std::priority_queue<T, std::vector<T>, std::greater<T>> pq;
    
    // Start with vertex 0
    visited[0] = true;
    parent[0] = -1;
    
    // Add all edges from vertex 0 to the priority queue
    for (int neighbor : adjList[0]) {
        pq.push({weights[0][neighbor], 0, neighbor});
    }
    
    while (!pq.empty()) {
        auto [weight, u, v] = pq.top();
        pq.pop();
        
        if (visited[v]) continue; // Skip if already visited
        
        // Mark as visited and set parent
        visited[v] = true;
        parent[v] = u;
        
        // Add all edges from v to unvisited neighbors
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                pq.push({weights[v][neighbor], v, neighbor});
            }
        }
    }
    
    printMST(parent);
}

void graph::printMST(const std::vector<int>& parent) {
    for (int i = 1; i < V; ++i) {
        std::cout << parent[i] << " - " << i << std::endl;
    }
}
int main(int argc, char const *argv[])
{
    graph g(3); // Create a graph with 3 vertices
    g.addEdge(0, 1, 4); // Add edge with weight 4
    g.addEdge(1, 2, 5); // Add edge with weight 5
    g.addEdge(0, 2, 6); // Add edge with weight 6

    graph g2(6);
    g2.addEdge(0, 1, 4);
    g2.addEdge(0, 2, 3);
    g2.addEdge(1, 2, 1);
    g2.addEdge(1, 3, 2);
    g2.addEdge(2, 3, 4);
    g2.addEdge(3, 4, 2);
    g2.addEdge(4, 5, 6);
    
    
    g.prim(); // Run Prim's algorithm
    std::cout << "Second graph:" << std::endl;
    g2.prim(); // Run Prim's algorithm on the second graph
    
    return 0;
}
