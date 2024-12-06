import heapq

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution(object):
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        heap = []
        # Initialize the heap with the head of each list
        for i, node in enumerate(lists):
            if node:
                heapq.heappush(heap, (node.val, i, node))
        
        dummy = ListNode(0)
        current = dummy
        
        while heap:
            val, i, node = heapq.heappop(heap)
            current.next = node
            current = current.next
            if node.next:
                heapq.heappush(heap, (node.next.val, i, node.next))
        
        return dummy.next

# Test cases for the Python solution
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def list_to_linkedlist(lst):
    dummy = ListNode()
    current = dummy
    for val in lst:
        current.next = ListNode(val)
        current = current.next
    return dummy.next

def linkedlist_to_list(node):
    result = []
    while node:
        result.append(node.val)
        node = node.next
    return result

def testSolution(solution):
    # Test case 1: List length is a multiple of k
    head = list_to_linkedlist([1, 2, 3, 4, 5])
    k = 2
    expected_result = [2, 1, 4, 3, 5]
    result = solution.reverseKGroup(head, k)
    assert linkedlist_to_list(result) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: List length is not a multiple of k, remaining nodes should stay the same
    head = list_to_linkedlist([1, 2, 3, 4, 5])
    k = 3
    expected_result = [3, 2, 1, 4, 5]
    result = solution.reverseKGroup(head, k)
    assert linkedlist_to_list(result) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: k is 1, list should remain unchanged
    head = list_to_linkedlist([1, 2, 3, 4, 5])
    k = 1
    expected_result = [1, 2, 3, 4, 5]
    result = solution.reverseKGroup(head, k)
    assert linkedlist_to_list(result) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: k equals the length of the list, entire list should be reversed
    head = list_to_linkedlist([1, 2, 3, 4, 5])
    k = 5
    expected_result = [5, 4, 3, 2, 1]
    result = solution.reverseKGroup(head, k)
    assert linkedlist_to_list(result) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Single node list
    head = list_to_linkedlist([1])
    k = 1
    expected_result = [1]
    result = solution.reverseKGroup(head, k)
    assert linkedlist_to_list(result) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: List length is less than k, list should remain unchanged
    head = list_to_linkedlist([1, 2, 3])
    k = 4
    expected_result = [1, 2, 3]
    result = solution.reverseKGroup(head, k)
    assert linkedlist_to_list(result) == expected_result, f"Test case 6 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    testSolution(solution)
