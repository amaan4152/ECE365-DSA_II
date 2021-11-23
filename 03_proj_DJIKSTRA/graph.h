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

    int addEdge(std::string &src_id, std::string &dest_id, int weight);

    int Djikstra(std::string &start_id);

    void printGraph(std::string filename);

    void printDjikstra(std::ofstream &outfile, std::string &start_id, int index);

private:
    class Vertex
    {
    public:
        struct Edge
        {
            int weight{COST_INF};
            Vertex *dest{nullptr};
        };
        std::string id{""};
        int dist{DIST_INF};
        bool known{false};
        std::list<Edge> adjList;
        std::list<Vertex *> path;

        Vertex() = default;
    };

    hashTable graphTable;
    heap vertexSet;
    std::vector<std::string> vertex_ids;

    Vertex *addVertex(std::string id);
};

#endif
