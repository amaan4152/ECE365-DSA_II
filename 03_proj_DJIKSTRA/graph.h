/*
Amaan Rahman
DSA-II
Project 3: Dijkstra's Algorithm
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <iterator>
#include <list>
#include <string>
#include <vector>
#include "heap.h"

#define COST_INF 1000000
#define DIST_INF 1000000000

class Graph
{
public:
    Graph(int capacity);
    
    /* Deallocate all vertices */
    ~Graph();

    /* 
    Add edge to graph 

    Parameters:
        src_id: source vertex id
        dest_id: destination vertex id
        weight: weight/cost of edge from source to destination verticies
    */
    void addEdge(std::string &src_id, std::string &dest_id, int weight);
    
    /* Dijkstra's algorithm */
    int Dijkstra(std::string &start_id);

    /* Print out shortest paths after Dijkstra's algorithm */
    void printDijkstra(std::ofstream &outfile, std::string &start_id, int index);

    /* 
        Print entire graph structure as a composition
        of adjacency lists to a file 
    */
    void printGraph(std::string filename);

private:
    class Vertex
    {
    public:
        struct Edge
        {
            int weight{COST_INF};       // weight/cost of edge
            Vertex *dest{nullptr};      // destination vertex
        };
        std::string id{""};             // vertex id
        int dist{DIST_INF};             // distance from start vertex
        bool known{false};              // visited status
        std::list<Edge> adjList;        // adjacency list
        Vertex *prev{nullptr};          // previous vertex in shortest/optimal path from start vertex

        Vertex() = default;
        void printPath(std::ofstream &outfile);
    };

    int size{0};
    hashTable graphTable;                   // graph structure
    std::vector<std::string> vertex_ids;    // vertex ids record to preserve order from file read

    /* Add/create vertex to graph */
    Vertex *addVertex(std::string id);
};

#endif
