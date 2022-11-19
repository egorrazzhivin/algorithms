'''
insert O(logN)
remove O(logN)
find element O(logN)
'''
class binary_search_tree:

    def __init__(self, value: int) -> None:
        self.right = None
        self.left = None
        self.value = value
    
    def insert(self, value: int) -> None:
        #insert element in tree
        if value <= self.value and self.left:
            self.left.insert(value)
        elif value <= self.value:
            self.left = binary_search_tree(value)
        elif value > self.value and self.right:
            self.right.insert(value)
        else:
            self.right = binary_search_tree(value)
    
    def find(self, value: int) -> int:
        #find element in tree
        if value < self.value and self.left:
            return self.left.find(value)
        if value > self.value and self.right:
            return self.right.find(value)
        print(value == self.value) 
    
    def get_min(self, node: int) -> int:
        #find min element in tree
        current = node
        while current.left:
            current = current.left
    
        return current
    
    def in_order_traverse(self, root: "binary_search_tree") -> list:
        #in-order-traversal
        if root is not None:
            self.in_order_traverse(root.left)
            print (root.value, end = ' ')
            self.in_order_traverse(root.right)
  
    def remove(self, root: "binary_search_tree", value: int) -> None:
        #remove element from tree
        if not root:
            print('tree is empty!')

        if value < root.value:
            root.left = self.remove(root.left, value)
        elif value > root.value:
            root.right = self.remove(root.right, value)
        else:
            if not root.left:
                return root.right
            elif not root.right:
                return root.left
            else:
                temp = self.get_min(root.right)
                root.value = temp.value
                root.right = self.remove(root.right, temp.value)


if __name__ == '__main__':
    tree = binary_search_tree(5)
    #root.insert(root, 50)
    tree.insert(3)
    tree.insert(8)
    tree.insert(7)
    tree.insert(2)
    tree.insert(1)
    tree.insert(4) 
    print('does tree have 0?')
    tree.find(0)
    print('does tree have 1?')
    tree.find(1)
    print('min element in tree:')
    print(tree.get_min(tree).value)
    print('tree:')
    tree.in_order_traverse(tree)
    tree.remove(tree, 5)
    print('\ntree:')
    tree.in_order_traverse(tree)
