'''
breadth first search algorithm
'''

from collections import defaultdict

class graph:

    def __init__(self) -> None:
        #structure for storing elements
        self.graph = defaultdict(list)
    
    def add_edge(self, u: int, v: int) -> None:
        #add way from vertex u to vertex v
        self.graph[u].append(v)
    
    def bfs(self, vertex: int) -> int:
        #create bool array with len(visited) = max elem in graph
        visited = [False]*(max(max(self.graph.keys()), max(max(self.graph.values())))+1)
        queue = []
        queue.append(vertex)
        visited[vertex] = True
        #while we can move from current vertex to its children, we move
        while queue:
            #get all vertex's children and do bfs from them
            up_vertex = queue.pop(0)
            print(up_vertex, end=' ')
            for v in self.graph[up_vertex]:
                if visited[v] == False:
                    queue.append(v)
                    visited[v] = True

if __name__ == '__main__':
    g = graph()
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(0, 3)
    g.add_edge(3, 4)
    g.add_edge(2, 6)
    g.add_edge(2, 3)
    g.add_edge(1, 8)
    print('bfs starting from 0')
    g.bfs(0)
    print('\nbfs starting from 1')
    g.bfs(1)

    
