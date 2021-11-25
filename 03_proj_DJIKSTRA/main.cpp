#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include "graph.h"

std::pair<std::string, int> toBuff(std::string);
Graph *loadGraph(std::pair<std::string, int>);

int main(void)
{
    std::string filename = "";
    std::string outname = "";
    std::string startID = "";

    std::cerr << "Enter name of graph file: ";
    std::cin >> filename;
    auto contents = toBuff(filename);
    Graph *G = loadGraph(contents);

    // === PRINT GRAPH ADJACENCY LISTS TO FILE ===
    G->printGraph("graph_adjLists.txt");
    std::clock_t start = std::clock();
    while (G->Djikstra(startID))
    {
        std::cerr << "Enter name of starting vertex: ";
        std::cin >> startID;
    }
    std::clock_t end = std::clock();
    float time = (end - start) / ((float)CLOCKS_PER_SEC);
    std::cerr << "Total time (in seconds) to apply Dijkstra's algorithm: " << time << "\n";

    std::cerr << "Enter name of output file: ";
    std::cin >> outname;
    std::ofstream outfile(outname);
    G->printDjikstra(outfile, startID, 0);
    delete G;
    return 0;
}

std::pair<std::string, int> toBuff(std::string filename)
{
    std::stringstream buff;
    std::ifstream file(filename);
    buff << file.rdbuf();
    std::string buff_str = buff.str();
    int capacity = std::count(buff_str.cbegin(),
                              buff_str.cend(), '\n');
    file.close();
    std::pair<std::string, int> contents(buff_str, capacity);
    return contents;
}

Graph *loadGraph(std::pair<std::string, int> contents)
{
    int weight = 0, capacity = contents.second;
    std::string line = "", src_id = "", dest_id = "";
    std::stringstream buff(contents.first);

    Graph *G = new Graph(capacity);
    while (getline(buff, line))
    {
        std::stringstream container(line);
        container >> src_id >> dest_id >> weight;
        G->addEdge(src_id, dest_id, weight);
    }

    return G;
}
