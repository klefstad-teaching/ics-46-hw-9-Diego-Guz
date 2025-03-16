// dijkstras_main.cpp
#include "dijkstras.h"
#include <iostream>
#include <vector>
using namespace std;


int main(int argc, char* argv[]){
    /*
    Main function for the Dijkstra's algorithm program.
    Reads a graph from a file, runs Dijkstra's algorithm from vertex 0, and prints the shortest path and cost from vertex 0 to every other vertex.

    Parameters:
        argc (int): The number of command-line arguments.
        argv (char*[]): The command-line arguments.

    Returns:
        int: Exit status (0 if successful, non-zero otherwise).
    */

    std::string filename;

    // If a filename is provided as a command-line argument, use it.
    // Otherwise, prompt the user to enter the filename.
    if(argc >= 2){
        filename = argv[1];
    } else {
        std::cout << "Enter graph filename: ";
        std::cin >> filename;
    }
    
    Graph G;

    // Attempt to load the graph from the specified file.
    // If an error occurs (e.g., file not found), catch the exception and exit.
    try {
        file_to_graph(filename, G);
    } catch(const exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::vector<int> previous;
    std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
     // For each vertex in the graph, extract and print the shortest path from vertex 0.
    for (int v = 0; v < G.numVertices; v++){
        //std::cout << "Path from 0 to " << v << ": ";

        // Retrieve the shortest path for vertex v.
        std::vector<int> path = extract_shortest_path(distances, previous, v);

        // Check if a path exists.
        if(path.empty()){
            std::cout << "No path found." << std::endl;
        } else {
            print_path(path, distances[v]);
        }
    }
    return 0;
}
