#include <iostream>
#include <list>

using namespace std;

//depth first search algorithm

class graph {
	//structure for storing elements
	int V;
	list<int> *a;
	void dfs_(int v, bool visited[]);
public:
	graph(int V);
	void add_edge(int v, int w);
	void dfs(int v);
};

graph::graph(int V) {
	this->V = V;
	a = new list<int>[V];
}

void graph::add_edge(int u, int v) {
	//add edge from vertex u to vertex v
	a[u].push_back(v);
}

void graph::dfs_(int v, bool visited[]) {
	visited[v] = true;
	cout << v << " ";
	list<int>::iterator i;
	for (i = a[v].begin(); i != a[v].end(); i++) {
		//if this vertex is not visited -> visit
		if (!visited[*i]) {
			//call dfs recursively
			dfs_(*i, visited);
		}
	}
}

void graph::dfs(int v) {
	//depth - first - search function
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++) {
		visited[i] = false;
	}
	dfs_(v, visited);
}

int main()
{
	graph g(7);
	g.add_edge(0, 1);
	g.add_edge(0, 2);
	g.add_edge(0, 3);
	g.add_edge(3, 4);
	g.add_edge(2, 5);
	g.add_edge(2, 3);
	g.add_edge(1, 6);
	cout << "dfs starting from 0" << endl;
	g.dfs(0);
	cout << endl << "dfs starting from 1" << endl;
	g.dfs(1);
	int n;

	return 0;
}
