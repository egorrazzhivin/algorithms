//prim's algorithm O(N^2)
#include <iostream>
#include <vector>
using namespace std;

// Number of vertices in the graph
#define V 5

//find min key value for vertices NOT in MST yet 
int minKey(int key[], bool mstSet[]){
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

//print MST
void printMST(int parent[], int graph[V][V])
{
    cout << "edge \tweight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t"
        << graph[i][parent[i]] << " \n";
}

void primMST(int graph[V][V])
{
    //array to store MST and key values for vertices not in MST
    int parent[V];
    int key[V];
    bool mstSet[V]; //set of vertices

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1; 

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        //get min key values for vertex not in MST
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        //update key value
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u, key[v] = graph[u][v];
            }
        }
    }
    printMST(parent, graph);
}

int main()
{
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };
    primMST(graph);
    return 0;
}