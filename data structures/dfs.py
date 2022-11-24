'''
depth first search algorithm
'''

from collections import defaultdict

class graph:

    def __init__(self) -> None:
        #structure for storing elements
        self.graph = defaultdict(list)
    
    def add_edge(self, u: int, v: int) -> None:
        #add edge from vertex u to vertex v
        self.graph[u].append(v)
    
    def dfs(self, vertex: int) -> int:
        #depth-first-search function
        visited = set()
        self.dfs_(vertex, visited)

    def dfs_(self, vertex: int, visited: int) -> int:
        visited.add(vertex)
        print(vertex, end = ' ')
        for v in self.graph[vertex]:
            if v not in visited:
                #call dfs recursively
                self.dfs_(v, visited)

if __name__ == '__main__':
    g = graph()
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(0, 3)
    g.add_edge(3, 4)
    g.add_edge(2, 6)
    g.add_edge(2, 3)
    g.add_edge(1, 8)
    print('dfs starting from 0')
    g.dfs(0)
    print('\ndfs starting from 1')
    g.dfs(1)

    
