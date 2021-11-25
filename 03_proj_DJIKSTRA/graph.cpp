#include <algorithm>
#include <fstream>
#include <iostream>
#include "graph.h"

Graph::Graph(int capacity) : size(capacity),
                             graphTable(capacity)
{}

Graph::~Graph()
{
    for (std::string id : this->vertex_ids){
        Vertex *v = static_cast<Vertex *>(this->graphTable.getPointer(id));
        delete v;
    }
}

Graph::Vertex *Graph::addVertex(std::string id)
{
    bool found = false;
    Vertex *v = static_cast<Vertex *>(this->graphTable.getPointer(id, &found));
    if (!found){
        v = new Vertex();
        v->id = id;
        this->graphTable.insert(id, v);
        this->vertex_ids.push_back(id);
    }
    return v;
}

void Graph::addEdge(std::string &src_id, std::string &dest_id, int weight)
{
    Vertex::Edge newEdge;
    Vertex *src = this->addVertex(src_id);
    newEdge.dest = this->addVertex(dest_id);
    newEdge.weight = weight;
    src->adjList.push_back(newEdge);
}

int Graph::Dijkstra(std::string &start_id)
{
    bool found = false;
    void *ppData = nullptr;
    Vertex *v = nullptr;
    // check if start vertex is valid
    v = static_cast<Vertex *>(this->graphTable.getPointer(start_id, &found));
    if (!found)     return 1;

    v->dist = 0;
    v->prev = nullptr;
    heap vertexSet = heap(this->size * 10);
    vertexSet.insert(start_id, v->dist, v);

    // find shortest/optimal path and update accordingly
    while (!(vertexSet.deleteMin(nullptr, nullptr, &ppData)))
    {
        // get vertex with minimum distance from start vertex
        v = static_cast<Vertex *>(ppData);
        if (v->known)   continue;
        v->known = true;

        // iterate through adjacency list and find shortest distance
        for (Vertex::Edge edge : v->adjList){
            int new_dist = v->dist + edge.weight;
            Vertex *w = edge.dest;
            vertexSet.insert(w->id, edge.weight, w);
            // if shortest distance found, update and add to path
            if (w->dist == DIST_INF || new_dist < w->dist){
                w->dist = new_dist;
                w->prev = v;
                vertexSet.setKey(w->id, new_dist);
            }
        }
    }
    return 0;
}

void Graph::printDijkstra(std::ofstream &outfile, std::string &start_id, int index)
{
    for (std::string id : this->vertex_ids){
        Vertex *v = static_cast<Vertex *>(this->graphTable.getPointer(id));
        
        outfile << id << ": ";
        if (v->dist == DIST_INF){
            outfile << "NO PATH\n"; 
            continue; 
        }
        outfile << v->dist << " [";
        v->printPath(outfile);
        outfile << "]\n";
    }
}

void Graph::printGraph(std::string filename)
{
    std::ofstream outfile(filename);
    for (std::string id : this->vertex_ids){
        Vertex *src = static_cast<Vertex *>(this->graphTable.getPointer(id));
        outfile << src->id << ": ";
        for (Vertex::Edge edge : src->adjList)
            outfile << " --{ " << edge.weight << " }--> " << edge.dest->id;

        outfile << " [END]" << std::endl;
    }
}

/* Helper function for printing path to each destination vertex */
void Graph::Vertex::printPath(std::ofstream &outfile)
{
    if (this->prev){
        this->prev->printPath(outfile);
        outfile << ", ";
    }
    outfile << this->id;
    return;
}