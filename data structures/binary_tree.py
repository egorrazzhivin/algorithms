#insert O(N)
class tree_node:
    #every node of tree is instance of tree_node()
    def __init__(self, value: int) -> None:
        self.right = None
        self.left = None
        self.value = value


class binary_tree:
    #main class
    def __init__(self):
        self.root = None
    
    def insert(self, value: int) -> None:
        #insert element in tree
        node = tree_node(value)
        if not self.root:
            self.root = node
        else:
            queue = []
            queue.append(self.root)
            while True:
                elem = queue.pop(0)
                if elem.left and elem.right:
                    queue.append(elem.left)
                    queue.append(elem.right)
                else:
                    if not elem.left:
                        elem.left = node
                    else:
                        elem.right = node
                    break
        
    def in_order_traverse(self, node):
        #in-order-traversal
        if not self.root:
            print('empty!')
        else:
            if node.left:
                self.in_order_traverse(node.left)
            print(node.value)
            if node.right:
                self.in_order_traverse(node.right)

    def pre_order_traverse(self, node):
        #pre-order-traversal
        if not self.root:
            print('empty!')
        else:
            print(node.value)
            if node.left:
                self.pre_order_traverse(node.left)
            if node.right:
                self.pre_order_traverse(node.right)

    def post_order_traverse(self, node):
        #post-order-traversal
        if not self.root:
            print('empty!')
        else:
            if node.left:
                self.post_order_traverse(node.left)
            if node.right:
                self.post_order_traverse(node.right)
            print(node.value)

if __name__ == '__main__':
    tree = binary_tree()
    tree.insert(2)
    tree.insert(3)
    tree.insert(5)
    tree.insert(7)
    tree.insert(8)
    tree.insert(10)
    print('pre-order traverse:')
    tree.pre_order_traverse(tree.root)
    print('post-order traverse:')
    tree.post_order_traverse(tree.root)
    print('in-order traverse:')
    tree.in_order_traverse(tree.root)

   
    