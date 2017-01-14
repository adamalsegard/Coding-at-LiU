/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    int dist[size + 1];
    int path[size + 1];
    bool done[size + 1];

    for(int i = 1; i<=size; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }
    const int start = 1;

    dist[start] = 0;
    done[start] = true;

    Node const *node;
    int v = start;

    int closest_vertex_distance, closest_vertex;

    while (true)
    {
        List &adjacency_list = array[v];

        // reset these
        closest_vertex_distance = INFINITY;
        closest_vertex = 0;

        node = adjacency_list.getFirst();
        while (node)
        {
            const int u = node->vertex;
            if (!done[u] && dist[u] > node->weight)
            {
                dist[u] = node->weight;
                path[u] = v;
            }

            node = adjacency_list.getNext();
        }

        for (int i = 1; i <= size; ++i)
        {
            if (done[i]) continue;

            if (dist[i] < closest_vertex_distance)
            {
                closest_vertex_distance = dist[i];
                closest_vertex = i;
            }
        }

        v = closest_vertex;

        if(v == 0)
        {
            break;
        }

        done[v] = true;
    }

    int total_weight = 0;
    for(int i = 1; i<=size; i++)
    {
        if(i == start) continue;

        cout << Edge(path[i], i, dist[i]) << endl;
        total_weight += dist[i];

    }
    cout << "Total weight = " << total_weight << endl;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    Edge edges[size - 1];

    Heap<Edge> myHeap;
    DSets disjoints(size);

    const Node *node;
    for(int i = 1; i <= size; i++)
    {
        List &adjacency_list = array[i];

        node = adjacency_list.getFirst();
        while (node)
        {
            myHeap.insert(Edge(i, node->vertex, node->weight));

            node = adjacency_list.getNext();
        }
    }

    int counter = 0;

    while (counter < size - 1)
    {
        const Edge edge = myHeap.deleteMin();

        const int head_root = disjoints.find(edge.head);
        const int tail_root = disjoints.find(edge.tail);

        if (head_root != tail_root)
        {
            disjoints.join(head_root, tail_root);
            edges[counter] = edge;
            //disjoints.print();

            ++counter;
        }
    }

    int total_weight = 0;
    for (int i = 0; i < size - 1; ++i)
    {
        cout << edges[i] << endl;
        total_weight += edges[i].weight;
    }
    cout << "Total weight = " << total_weight << endl;
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

