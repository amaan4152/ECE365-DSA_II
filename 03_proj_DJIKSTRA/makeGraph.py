'''
Amaan Rahman
Random Graph Generator
Project 3: Djikstra
DSA II
'''

import matplotlib.pyplot as plt
import networkx as nx
from networkx.generators.random_graphs import erdos_renyi_graph
from numpy import log
from random import randint, choices

START = 10
END = 100

'''
    Utilize Erdos Renyi algorithm to generate random graphs. 
    Graph, G, is ALMOST surely to be connected iff p > [(1 + eps)*ln(n)]/n,
    where 'eps' << 1. 

    n = # of verticies
    p = weight of connectedness
    source: https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model
'''
def makeGraph():
    n = randint(START, END)
    threshold = log(n) / n
    p = 10 * threshold
    G = erdos_renyi_graph(n, p)
    return G

'''
    Randomly apply weights to each edge of graph, G
'''
def applyWeights(G, filename):
    num_edges = len(G.edges)
    weights = choices(range(1, END), k=num_edges)
    with open(filename, 'w') as f:
        for e, w in zip(G.edges(), weights):
            G[e[0]][e[1]]['weights'] = w
            row_str = f'v{e[0] + 1} v{e[1] + 1} {w}\n'
            f.write(row_str)


def main():
    # regenerate graph if it is not connected
    while(True):
        G = makeGraph()
        if(nx.is_connected(G)):
            print('[status: SUCESS]: Graph is connected!')
            break
        print('[status: FAILED]: Graph not connected! Retrying...')

    # apply random weights and write graph to file
    applyWeights(G, 'graph.txt')

    # draw and save graph
    nx.draw(G, with_labels=True, font_weight="bold")
    plt.savefig('graph.png')

if __name__ == "__main__":
    main()
