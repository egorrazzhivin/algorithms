class queue_with_two_stacks:
    '''
    O(1) push
    amortized get_peak, pop
    overall n operations will take O(n) time complexity
    '''
    def __init__(self) -> None:
        self.stack1 = []
        self.stack2 = []
        self.pointer = None #points on first elem in queue

    def push(self, val: int) -> None:
        #pushs val in queue
        if not self.stack1:
            self.pointer = val 
        self.stack1.append(val)

    def pop(self) -> int:
        #deletes first elem in queue (from the front)
        if not self.stack2: #if it's empty
            while self.stack1:
                self.stack2.append(self.stack1.pop())
        return self.stack2.pop()
        
    
    def get_peak(self) -> int:
        #returns first elem in queue (from the front)
        if self.stack2: #if it's not empty than [-1] elem is peak
            return self.stack2[-1]
        return self.pointer #if stack2 is empty

    def is_empty(self) -> bool:
        return (not self.stack1) and (not self.stack2)

if __name__ == '__main__':
    queue = queue_with_two_stacks()
    print(queue.is_empty())
    queue.push(5)
    queue.push(10)
    queue.push(8)
    print('pop = ' + str(queue.pop()))
    print('peak = ' + str(queue.get_peak()))
    print('pop = ' + str(queue.pop()))
    print('peak = ' + str(queue.get_peak()))
    print('is empty? ' + str(queue.is_empty()))