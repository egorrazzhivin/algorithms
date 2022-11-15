class binomial_tree:
    '''
    create binomial tree
    '''
    def __init__(self, key: int) -> None:
        self.key = key 
        self.children = []
        self.order = 0 #tree's rank

class binomial_heap:
    '''
    insert O(logN))
    remove_min O(logN)
    get_min O(logN)
    merge() O(logN)
    decrease_key O(logN)
    '''

    def __init__(self) -> None:
        self.trees = [] #contain set of binomial trees

    def remove_min(self) -> None:
        #remove min
        min_node = self.trees[0]
        for tree in self.trees:
            if tree.key < min_node.key:
                min_node = tree
        self.trees.remove(min_node)
        #after that we decompose our min_node on its children
        #and merge them with out heap
        new_heap = binomial_heap()
        new_heap.trees = min_node.children
        self.merge(new_heap)
        return min_node.key

    def get_min(self) -> int:
        #return minimum value of heap   
        min_val = self.trees[0].key
        for tree in self.trees:
            if tree.key < min_val:
                min_val = tree.key
        return min_val

    def merge(self, new_heap: list) -> None:
        #merge current heap and new_heap
        self.trees.extend(new_heap.trees)
        self.trees.sort(key = lambda tree: tree.order) #sort in increasing tree's order

        if not self.trees: return
        i = 0
        while i < len(self.trees) - 1:
            current_tree = self.trees[i]
            next_tree = self.trees[i+1]
            if current_tree.order == next_tree.order:
                if (i < len(self.trees) - 2) and self.trees[i+2].order == next_tree.order:
                    next_next_tree = self.trees[i+2]
                    if next_tree.key < next_next_tree.key:
                        next_tree.children.append(next_next_tree)
                        next_tree.order += 1
                        del self.trees[i+2]  
                    else:
                        next_next_tree.children.append(next_tree)
                        next_next_tree.order += 1
                        del self.trees[i+1] 
                else:
                    if next_tree.key < current_tree.key:
                        next_tree.children.append(current_tree)
                        next_tree.order += 1
                        del self.trees[i]
                        
                    else:
                        current_tree.children.append(next_tree)
                        current_tree.order += 1
                        del self.trees[i+1]
            i+=1
    
    def insert(self, key: int) -> None:
        #insert key in heap
        bin_heap = binomial_heap()
        tree = binomial_tree(key)
        bin_heap.trees.append(tree)
        self.merge(bin_heap)

if __name__ == '__main__':
    heap_1 = binomial_heap()
    heap_2 = binomial_heap()
    for i in range(10):
        heap_1.insert(i)
    for i in range(10, 1, -1):
        heap_2.insert(i)
    heap_1.merge(heap_2)
    heap_1.get_min()
    mins = []
    for i in range(15):
        mins.append(heap_1.remove_min())
    print(mins)
