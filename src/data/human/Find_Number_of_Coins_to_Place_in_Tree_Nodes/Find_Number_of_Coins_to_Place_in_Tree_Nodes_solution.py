from typing import List


class X:
    def __init__(self, val: int):
        '''constructor with one cost value (or one tree node)'''
        
        # number of nodes in subtree
        self.numNodes = 1
        
        # posMax: [maximum, second maximum, third maximum]
        # negMin: [minimum, second minimum]
        self.posMax, self.negMin = [], []
        self.posMax.append(val) if val > 0 else self.negMin.append(val)
    
    def update(self, x):
        '''update current node with child's information'''
        
        # add child's nodes
        self.numNodes += x.numNodes
        
        # add child's maximum(s) and minimum(s)
        # sort them and select top 3 maximum and top 2 minimum
        self.posMax = sorted(self.posMax + x.posMax, reverse=True)[:3]
        self.negMin = sorted(self.negMin + x.negMin)[:2]
    
    def product(self) -> int:
        '''maximum product of subtree'''
        
        # case 1
        if self.numNodes < 3:
            return 1
        # case 2
        result = 0
        # choice 1 (all positive)
        if len(self.posMax) == 3:
            result = self.posMax[0] * self.posMax[1] * self.posMax[2]
        # choice 2 (2 negative 1 positive)
        if len(self.negMin) == 2 and self.posMax:
            result = max(result, self.negMin[0] * self.negMin[1] * self.posMax[0])
        return result


class Solution:
    def fillCoins(self, graph: List[List[int]], cost: List[int], curr: int, prev: int, coins: List[int]) -> X:
        '''
        Depth-First Search on tree
        fills coins array
        '''
        
        # maintain information of current subtree
        x = X(cost[curr])
        for next in graph[curr]:
            # avoid calling function back to parent
            if next != prev:
                # fillCoins() returns information of child's subtree
                # update current subtree with child's information
                x.update(self.fillCoins(graph, cost, next, curr, coins))
        
        # once information of current subtree is completed
        # calculate maximum product
        coins[curr] = x.product()
        
        # return information to parent
        return x
    
    def placedCoins(self, edges: List[List[int]], cost: List[int]) -> List[int]:
        n = len(cost)
        # make tree in adjacency list form
        graph = [[] for _ in range(n)]
        for edge in edges:
            graph[edge[0]].append(edge[1])
            graph[edge[1]].append(edge[0])
        coins = [0] * n
        # call DFS and fill coins array
        self.fillCoins(graph, cost, 0, -1, coins)
        return coins

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with a balanced tree
    edges = [[0, 1], [0, 2], [0, 3], [0, 4], [0, 5]]
    cost = [1, 2, 3, 4, 5, 6]
    expected_result = [120, 1, 1, 1, 1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Tree with only two nodes
    edges = [[0, 1]]
    cost = [5, 3]
    expected_result = [1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Tree with three nodes, one subtree product
    edges = [[0, 1], [0, 2]]
    cost = [-1, -2, 4]
    expected_result = [8, 1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Linear tree (path) with multiple nodes
    edges = [[0, 1], [0, 2], [1, 3], [1, 4], [1, 5], [2, 6], [2, 7], [2, 8]]
    cost = [1, 4, 2, 3, 5, 7, 8, -4, 2]
    expected_result = [280, 140, 32, 1, 1, 1, 1, 1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Tree with all negative costs
    edges = [[0, 1], [0, 2], [2, 3]]
    cost = [-3, -2, -4, -1]
    expected_result = [0, 1, 1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Single node tree
    edges = []
    cost = [10]
    expected_result = [1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: More complex tree with mixed values
    edges = [[0, 1], [0, 2]]
    cost = [1, 2, -2]
    expected_result = [0, 1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(200000):
        testSolution(solution)
