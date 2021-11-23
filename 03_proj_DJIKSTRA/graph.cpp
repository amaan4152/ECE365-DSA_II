#include <algorithm>
#include <fstream>
#include <iostream>
#include "graph.h"

Graph::Graph(int capacity) : vertexSet(capacity),
                             graphTable(capacity)
{
}

Graph::Vertex *Graph::addVertex(std::string id)
{
    bool found = false;
    Vertex *v = static_cast<Vertex *>(this->graphTable.getPointer(id, &found));
    if (!found)
    {
        v = new Vertex();
        v->id = id;
        this->graphTable.insert(id, v);
        this->vertex_ids.push_back(id);
    }
    return v;
}

int Graph::addEdge(std::string &src_id, std::string &dest_id, int weight)
{
    Vertex::Edge newEdge;
    Vertex *src = this->addVertex(src_id);
    newEdge.dest = this->addVertex(dest_id);
    newEdge.weight = weight;
    src->adjList.push_back(newEdge);

    return 0;
}

void Graph::printGraph(std::string filename)
{
    std::ofstream outfile(filename);
    for (std::string id : this->vertex_ids)
    {
        Vertex *src = static_cast<Vertex *>(this->graphTable.getPointer(id));
        outfile << src->id << ": ";
        for (Vertex::Edge edge : src->adjList)
            outfile << " --{ " << edge.weight << " }--> " << edge.dest->id;

        outfile << " [END]" << std::endl;
    }
}


int Graph::Djikstra(std::string &start_id)
{
    bool found = false;
    Vertex *v = nullptr;
    // check if start vertex is valid
    v = static_cast<Vertex *>(this->graphTable.getPointer(start_id, &found));
    if (!found)
        return 1;

    v->dist = 0;
    this->vertexSet.insert(start_id, v->dist, v);
    void *ppData;
    while (!(this->vertexSet.deleteMin(nullptr, nullptr, &ppData)))
    {
        v = static_cast<Vertex *>(ppData);
        if (v->known)
            continue;
        v->known = true;

        for (Vertex::Edge edge : v->adjList)
        {
            int new_dist = v->dist + edge.weight;
            Vertex *w = edge.dest;
            this->vertexSet.insert(w->id, w->dist, w);
            if (!w->known && new_dist < w->dist)
            {
                w->dist = new_dist;
                w->path.push_back(v);
                this->vertexSet.setKey(w->id, new_dist);
            }
        }
    }
    return 0;
}

void Graph::printDjikstra(std::ofstream &outfile, std::string &start_id, int index)
{
    if (index == this->vertex_ids.size())
        return;

    std::string vId = this->vertex_ids.at(index);
    Vertex *v = static_cast<Vertex *>(this->graphTable.getPointer(vId));
    outfile << vId << ": ";
    outfile << v->dist << " [" << start_id;
    for (Vertex *u : v->path)
    {
        outfile << u->id;
        outfile << ", ";
    }
    outfile << "]\n";
    this->printDjikstra(outfile, start_id, ++index);
    delete v;
}
