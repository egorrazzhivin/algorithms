import random

class fenwick_tree:

    def __init__(self, arr: list) -> None:
        self.arr = arr
        self.t = [0]*len(arr) #auxiliary array
        for i in range(len(arr)):
            self.t[i] = self.fill_t(i)

    def get_sum(self, left: int, right: int) -> int:
        #returns prefix sum on arr[left:right] (inclusive)
        assert (min(left, right) >= 0) and (max(left,right) < len(self.arr)), 'dude.'
        if left > right:
            left, right = right, left
        if left != 0:
            return self.sum(right) - self.sum(left-1)
        else:
            return self.sum(right)
        
    def sum(self, ind: int) -> int:
        #calculates prefix sum on arr[0:ind] (inclusive)
        res = 0
        if ind == 0:
            res = self.t[ind]
        while ind > 0:
            res += self.t[ind]
            ind = self.bitwise_and(ind) - 1
        return res

    def bitwise_and(self, ind: int) -> int:
        #does bitwise AND
        return ind & (ind+1)

    def bitwise_or(self, ind: int) -> int:
        #does bitwise OR
        return ind | (ind+1)    

    def fill_t(self, ind: int) -> int:
        #fills auxiliary array
        #by definition t[i] = sum arr[j] from f(i) to i, where f(i) = i&(i+1)
        l_bound = self.bitwise_and(ind)
        r_bound = ind
        val = 0
        for i in range(l_bound, r_bound+1):
            val += self.arr[i]
        return val

    def update_value(self, ind: int, val: int):
        #updates value in self.arr and in self.t
        prev_val = self.arr[ind]
        self.arr[ind] = val
        delta = val - prev_val
        while ind < len(self.arr):
            self.t[ind] += delta
            ind = self.bitwise_or(ind)

if __name__ == '__main__':
    n = random.randint(5, 20)
    arr = [0]*n
    for i in range(n):
        arr[i] = random.randint(0, 10)
    tree = fenwick_tree(arr)
    print(arr)
    l = random.randint(0, n-2)
    r = random.randint(l+1, n-1)
    print('sum from ' + str(l) + ' to ' + str(r) + ' = ' + str(tree.get_sum(l, r)))
    m = random.randint(l, r)
    tree.update_value(m, 100)
    print(arr)
    print('sum from ' + str(l) + ' to ' + str(r) + ' = ' + str(tree.get_sum(l, r)))
    tree.get_sum(l, r)
