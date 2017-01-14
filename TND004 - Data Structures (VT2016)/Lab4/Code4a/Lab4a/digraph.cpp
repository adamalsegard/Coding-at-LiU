/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
        cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
        return;
    }

    // init all result arrays
    for (int i = 0; i <= size; ++i)
    {
        dist[i] = INFINITY;
        path[i] = 0;
    }

    Queue<Node*> Q;
    dist[s] = 0;

    Node *node = new Node(s);
    Q.enqueue(node);

    while(!Q.isEmpty())
    {
        Node *node = Q.getFront();
        Q.dequeue();

        const int vertex = node->vertex;

        List &adjacent_vertices = array[vertex];
        node = adjacent_vertices.getFirst();

        while (node)
        {
            if (dist[node->vertex] == INFINITY)
            {
                dist[node->vertex] = dist[vertex] + 1;
                path[node->vertex] = vertex;
                Q.enqueue(node);
            }

            node = adjacent_vertices.getNext();
        }
    }

    delete node;
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
        cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
        return;
    }

    // init all result arrays
    for (int i = 0; i <= size; ++i)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }
    dist[s] = 0;
    done[s] = true;

    Node *node;
    int v = s;

    while (true)
    {
        List &adjacency_list = array[v];

        node = adjacency_list.getFirst();
        while (node)
        {
            const int u = node->vertex;
            if (!done[u] && dist[u] > dist[v] + node->weight)
            {
                dist[u] = dist[v] + node->weight;
                path[u] = v;
            }

            node = adjacency_list.getNext();
        }

        // Get the vertex with the smallest distance which is NOT done
        // Awesometacular to have a heap, this operation would be O(1)
        v = find_smallest_undone_distance_vertex();

        if(v == -1)
        {
            break;
        }

        done[v] = true;
    }
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

void Digraph::printPathRecursive(int t) const
{
    if (t < 1 || t > size)
    {
        cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
        return;
    }

    int prev = path[t];

    if(prev == 0)
    {
        return;
    }
    printPathRecursive(prev);
    cout << " " << prev;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
        cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
        return;
    }

    printPathRecursive(t);
    cout << " " << t << " (" << dist[t] << ")";


}

int Digraph::find_smallest_undone_distance_vertex() const
{
    int smallest_distance = INFINITY;
    int smallest_vertex = -1;

    for (int i = 0; i < size + 1; ++i)
    {
        if (!done[i] && dist[i] < smallest_distance)
        {
            smallest_distance = dist[i];
            smallest_vertex = i;
        }
    }

    return smallest_vertex;
}
