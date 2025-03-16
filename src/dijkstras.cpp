// dijkstras.cpp
#include "dijkstras.h"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <algorithm>
using namespace std;

struct Node {
    /*
    Structure to represent a node in the graph for Dijkstra's algorithm.

    Attributes:
        vertex (int): The index of the vertex.
        distance (int): The current computed distance from the source vertex.
    */

    int vertex;
    int distance;

    // Constructor initializes the vertex and its current distance.
    Node(int v, int d) : vertex(v), distance(d) {}
};

struct NodeComparator {
    /*
    Comparator functor for Node.
    This is used in the priority queue to order nodes by their distance,
    ensuring that the node with the smallest distance has the highest priority.

    Parameters:
        n1 (const Node&): The first node to compare.
        n2 (const Node&): The second node to compare.

    Returns:
        bool: True if n1's distance is greater than n2's distance, indicating that n2 should come before n1.
    */

    bool operator()(const Node& n1, const Node& n2) {

        // Compare the distances of two nodes.
        return n1.distance > n2.distance;
    }
};


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    /*
    Computes the shortest path distances from a source vertex to all other vertices in a graph using Dijkstra's algorithm.

    Parameters:
        G (const Graph&): The graph represented as an adjacency list.
        source (int): The source vertex from which distances are calculated.
        previous (vector<int>&): A reference vector that will be updated with the previous vertex in the shortest path for each vertex.

    Returns:
        vector<int>: A vector of distances from the source to each vertex.
    */

    int n = G.numVertices;
    std::vector<int> distances(n, INF);
    std::vector<bool> visited(n, false);
    previous.assign(n, -1);

     // Priority queue to select the vertex with the smallest tentative distance.
    priority_queue<Node, std::vector<Node>, NodeComparator> pq;
    distances[source] = 0;
    pq.push(Node(source, 0));
    
    // Process the queue until it's empty.
    while (!pq.empty()){

        // Get the node with the smallest distance.
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;

        // If vertex u is already visited, skip it.
        if(visited[u]){
            continue;
        }
        visited[u] = true;

        // Loop over all the edges from vertex u.
        for (auto &edge : G[u]){
            int v = edge.dst;
            int weight = edge.weight;

            // If vertex v has not been visited and a shorter path through u is found.
            if (!visited[v] && distances[u] + weight < distances[v]) {

                // Update the distance for vertex v.
                distances[v] = distances[u] + weight;

                // Update the previous vertex for v to be u.
                previous[v] = u;

                // Push the updated node into the priority queue.
                pq.push(Node(v, distances[v]));
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {

    /*
    Extracts the shortest path from the source to a given destination vertex using the 'previous' vector.

    Parameters:
        distances (const vector<int>&): The vector of computed shortest distances.
        previous (const vector<int>&): The vector storing the previous vertex for each vertex in the shortest path.
        destination (int): The destination vertex for which to extract the path.

    Returns:
        vector<int>: A vector representing the path from the source to the destination.
                   Returns an empty vector if no path exists.
    */

    std::vector<int> path;

     // If the destination is unreachable, return an empty path.
    if(distances[destination] == INF){
        return path; 
    }

    // Trace back from the destination to the source using the 'previous' vector.
    for (int at = destination; at != -1; at = previous[at]){
        path.push_back(at);
    }

    // The path is constructed in reverse order, so reverse it before returning.
    reverse(path.begin(), path.end());
    return path;
}


void print_path(const vector<int>& path, int total) {
    /*
    Prints a path of vertices and the total cost of the path.

    Parameters:
        path (const vector<int>&): The vector containing the sequence of vertices in the path.
        total (int): The total cost of the path.

    Returns:
        None.
    */

    // Check if the path is empty.
    if(path.empty()){
        std::cout << "No path found." << std::endl;
        return;
    }
    
    // Loop through the path and print each vertex.
    for (size_t i = 0; i < path.size(); i++){
        std::cout << path[i] << " ";
        // if(i != path.size()-1){
        //     std::cout << " -> ";
        // }
            
    }
    std::cout << "" << std::endl;
    std::cout << "Total cost is: " << total << std::endl;
}
