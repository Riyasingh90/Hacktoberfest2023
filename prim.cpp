#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Define a structure to represent an edge in the graph
struct Edge {
    int to;
    int weight;

    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

class Graph {
private:
    int V; // Number of vertices
    vector<vector<Edge>> adj; // Adjacency list to represent the graph

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    // Add an edge to the graph
    void addEdge(int from, int to, int weight) {
        adj[from].emplace_back(to, weight);
        adj[to].emplace_back(from, weight); // For undirected graph
    }

    // Find the MST using Prim's algorithm
    vector<Edge> primMST() {
        vector<Edge> mst; // To store the MST
        vector<bool> inMST(V, false); // To track vertices in the MST
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // Priority queue for edge selection

        // Start with the first vertex (vertex 0)
        pq.push(Edge(0, 0));

        while (!pq.empty()) {
            Edge currentEdge = pq.top();
            pq.pop();

            int u = currentEdge.to;

            // If the vertex is already in the MST, skip it
            if (inMST[u])
                continue;

            // Include the current edge in the MST
            inMST[u] = true;
            mst.push_back(currentEdge);

            // Add adjacent edges to the priority queue
            for (Edge edge : adj[u]) {
                if (!inMST[edge.to])
                    pq.push(edge);
            }
        }

        return mst;
    }
};

int main() {
    int V = 5;
    Graph graph(V);

    // Add edges to the graph (from, to, weight)
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 8);
    graph.addEdge(1, 4, 5);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 4, 9);

    vector<Edge> mst = graph.primMST();

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (Edge edge : mst) {
        cout << edge.to << " - " << edge.weight << endl;
    }

    return 0;
}
