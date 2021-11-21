#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include "graph.h"

std::pair<std::string, int> toBuff(std::string);
Graph *loadGraph(std::pair<std::string, int>);
void debug(std::string);

int main(void)
{
    std::string filename = "";
    std::string outname = "";
    std::string startID = "";

    std::cout << "Enter name of graph file: ";
    std::cin >> filename;
    auto contents = toBuff(filename);
    Graph *G = loadGraph(contents);
    // === PRINT GRAPH ADJACENCY LISTS TO FILE ===
    G->printGraph("graph_adjLists.txt");

    std::cout << "Enter name of starting vertex: ";
    std::cin >> startID;
    while (G->Djikstra(startID))
    {
        std::cerr << "Enter name of starting vertex: ";
        std::cin >> startID;
    }
    std::cerr << "Enter name of output file: ";
    std::cin >> outname;
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
    std::string buff = contents.first;
    int capacity = contents.second;
    std::regex delim("\\s+");
    std::sregex_token_iterator itr(buff.begin(), buff.end(), delim, -1);
    std::sregex_token_iterator end;

    Graph *G = new Graph(capacity);
    for (; itr != end; ++itr)
    {
        std::string src_id = *itr;
        ++itr;
        std::string dest_id = *itr;
        ++itr;
        int weight = std::stoi(*itr);
        G->addEdge(src_id, dest_id, weight);
    }

    return G;
}

void debug(std::string mssg)
{
    std::cout << "[DEBUG]: " << mssg << std::endl;
}