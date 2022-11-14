class binary_heap:
    '''
    min heap!!!
    sift_up O(logN)
    get_min O(1)
    extract O(logN)
    '''
    def __init__(self) -> None:
        self.heap = []
        self.size = 0

    def sift_up(self, val: int) -> None:
        #insert val in self.heap (with maintaining heap property)
        self.heap.append(val)
        print(self.heap)
        self.size += 1
        i = self.size-1
        while self.heap[i] < self.heap[i//2]:
            self.heap[i], self.heap[i//2] = self.heap[i//2], self.heap[i]
            i = i//2
        print(self.heap)
    
    def get_min(self) -> int:
        #get minimum elem in self.heap
        print(self.heap[0])

    def extract(self) -> None:
        #delete root from self.heap (with maintaining heap property)
        if self.heap:
            self.heap[0] = self.heap[-1]
            self.heap.pop()
            self.size -= 1
        i = 0
        while 2*i < self.size:
            if 2*i+2 < self.size:
                if self.heap[i] > min(self.heap[2*i+1], self.heap[2*i+2]):
                    if self.heap[2*i+1] == min(self.heap[2*i+1], self.heap[2*i+2]):
                        self.heap[i], self.heap[2*i+1] = self.heap[2*i+1], self.heap[i]
                        i = 2*i + 1
                    else:
                        self.heap[i], self.heap[2*i+2] = self.heap[2*i+2], self.heap[i]
                        i = 2*i + 2
            elif 2*i+1 < self.size and 2*i+2 >= self.size:
                if self.heap[i] > self.heap[2*i+1]:
                    self.heap[i], self.heap[2*i+1] = self.heap[2*i+1], self.heap[i]
                    i = 2*i + 1
        
    def get_heap(self) -> list:
        print(self.heap)

if __name__ == '__main__':
    heap = binary_heap()
    heap.sift_up(6)
    heap.sift_up(5)
    heap.sift_up(1)
    heap.sift_up(0)
    heap.sift_up(3)
    heap.get_heap()
    heap.extract()
    heap.get_heap()
    heap.extract()
    heap.get_min()
    heap.get_heap()
        

    

    

    