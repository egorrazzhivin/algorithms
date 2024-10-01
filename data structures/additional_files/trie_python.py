# link: https://leetcode.com/problems/k-divisible-elements-subarrays/description/

class TrieNode(object):
    def __init__(self):
        self.children = dict()

class Trie(object):
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, segment):
        if len(segment) == 0:
            return
        current_node = self.root
        for i in range(len(segment)):
            current_number = segment[i]
            if current_number not in current_node.children.keys():
                current_node.children[current_number] = TrieNode()
            current_node = current_node.children[current_number]
            
    def find_unique(self, segment):
        if len(segment) == 0:
            return 0
        current_node = self.root
        for i in range(len(segment)):
            current_number = segment[i]
            if current_number not in current_node.children.keys():
                return len(segment) - i
            current_node = current_node.children[current_number]
        return 0
            

class Solution(object):
    def countDistinct(self, nums, k, p):
        """
        :type nums: List[int]
        :type k: int
        :type p: int
        :rtype: int
        """
        is_divisible = []
        for x in nums:
            value = 0 if x % p else 1
            is_divisible.append(value)
        # print(is_divisible)
        r, cnt = 0, 0
        trie = Trie()
        answer = 0
        for l in range(len(nums)):
            # print(r, cnt)
            while r < len(nums) and cnt <= k:
                if is_divisible[r] == 1 and cnt == k:
                    break
                elif is_divisible[r] == 1:
                    cnt += 1
                r += 1
            # r -= 1
            # do trie
            subarray = nums[l:r]
            # print(subarray)
            answer += trie.find_unique(subarray)
            # print("answer = " + str(answer))
            trie.insert(subarray)
            if is_divisible[l] == 1:
                cnt -= 1
        return answer
                
        
