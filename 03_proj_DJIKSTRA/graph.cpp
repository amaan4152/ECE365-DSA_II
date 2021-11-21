#include <algorithm>
#include <fstream>
#include <iostream>
#include "graph.h"

Graph::Graph(int capacity) : vertexSet(capacity),
                             graphTable(capacity)
{
}

int Graph::addEdge(std::string &src_id, std::string &dest_id, int weight)
{
    Vertex *src, *dest;

    // check if graph verticies exist in graph (via hash table)
    if (!(src = static_cast<Vertex *>(this->graphTable.getPointer(src_id))))
    {
        src = new Vertex();
        src->id = src_id;
        this->graphTable.insert(src_id, src);
        this->vertex_ids.push_back(src_id);
    }
    if (!(dest = static_cast<Vertex *>(this->graphTable.getPointer(dest_id))))
    {
        dest = new Vertex();
        dest->id = dest_id;
        this->graphTable.insert(dest_id, dest);
        this->vertex_ids.push_back(dest_id);
    }

    // create edge
    Vertex edgeNode;
    edgeNode.id = dest_id;
    edgeNode.weight = weight;
    if (src)
    {
        // append adjacency list with new edge
        src->adjList.push_back(edgeNode);
        return 0;
    }
    // create new source vertex and add to graph
    src->adjList.push_back(edgeNode);

    return 0;
}

int Graph::Djikstra(std::string &start_id)
{
    Vertex *src = nullptr, *v = nullptr;
    // check if start vertex is valid
    if (!(src = static_cast<Vertex *>(this->graphTable.getPointer(start_id))))
        return 1;
    // DEFAULT:
    //      all verticies in the loaded graph have an
    //      initial distance and weight of DIST_INF and COST_INF, respectively.
    //      Also, the previous path list is empty for each vertex.
    // initial condition of start vertex
    src->dist = 0;
    this->vertexSet.insert(start_id, src->dist, src);
    void *ppData;
    while (!(this->vertexSet.deleteMin(nullptr, nullptr, ppData)))
    {
        v = *static_cast<Vertex **>(ppData);
        // === DEBUG MESSAGE ===
        // std::cout << "ID: " << v->id << std::endl;
        if (v->known)
            break;
        v->known = true;

        for (Vertex w : v->adjList)
        {
            Vertex *wNode = static_cast<Vertex *>(this->graphTable.getPointer(w.id));
            if (v->dist + w.weight < wNode->dist)
            {
                wNode->dist = v->dist + w.weight;
                wNode->path.push_back(v);
                // === DEBUG MESSAGES ===
                // w.dist = wNode->dist;
                // std::cout << "\td_" << v->id << ": " << v->dist << " | "
                //           << w.id << ": (w: " << w.weight << ", d: " << w.dist << ")" << std::endl;
                this->vertexSet.insert(wNode->id, wNode->dist, wNode);
            }
        }
    }
    return 0;
}

void Graph::printGraph(std::string filename)
{
    std::ofstream outfile(filename);
    for (std::string id : this->vertex_ids)
    {
        Vertex *src = static_cast<Vertex *>(this->graphTable.getPointer(id));
        outfile << src->id << ": ";
        for (Vertex v : src->adjList)
            outfile << " --{ " << v.weight << " }--> " << v.id;

        outfile << " [END]" << std::endl;
    }
}

void Graph::printDjikstra(std::ofstream &outfile, std::string &start_id, int index)
{
    if (index == this->vertex_ids.size())
        return;

    std::string vId = this->vertex_ids.at(index);
    Vertex *v = static_cast<Vertex *>(this->graphTable.getPointer(vId));
    outfile << v->id << ": ";
    if (v->dist == 0 || (v->dist != 0 && !v->path.empty()))
    {
        outfile << v->dist << " [" << start_id;
        for (Vertex *u : v->path)
        {
            if (u->id == start_id)
                continue;
            outfile << ", ";
            outfile << u->id;
        }
        if (v->id != start_id)
            outfile << ", " << v->id << "]\n";
        else
            outfile << "]\n";
    }
    else
        outfile << "NO PATH\n";
    this->printDjikstra(outfile, start_id, ++index);
}
