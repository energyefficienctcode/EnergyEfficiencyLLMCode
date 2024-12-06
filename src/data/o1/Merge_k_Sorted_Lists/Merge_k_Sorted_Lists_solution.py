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
            current.next = ListNode(val)
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
    # Test case 1: Merging three sorted lists
    lists = [
        list_to_linkedlist([1, 4, 5]),
        list_to_linkedlist([1, 3, 4]),
        list_to_linkedlist([2, 6])
    ]
    expected_result = [1, 1, 2, 3, 4, 4, 5, 6]
    result = solution.mergeKLists(lists)
    assert linkedlist_to_list(result) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Single empty list
    lists = [None]
    expected_result = []
    result = solution.mergeKLists(lists)
    assert linkedlist_to_list(result) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: All lists are empty
    lists = [None, None, None]
    expected_result = []
    result = solution.mergeKLists(lists)
    assert linkedlist_to_list(result) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Mixed empty and non-empty lists
    lists = [
        list_to_linkedlist([]),
        list_to_linkedlist([1, 3, 4]),
        None,
        list_to_linkedlist([2, 6, 7])
    ]
    expected_result = [1, 2, 3, 4, 6, 7]
    result = solution.mergeKLists(lists)
    assert linkedlist_to_list(result) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: All lists with single element
    lists = [
        list_to_linkedlist([1]),
        list_to_linkedlist([0]),
        list_to_linkedlist([5])
    ]
    expected_result = [0, 1, 5]
    result = solution.mergeKLists(lists)
    assert linkedlist_to_list(result) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: No lists provided
    lists = []
    expected_result = []
    result = solution.mergeKLists(lists)
    assert linkedlist_to_list(result) == expected_result, f"Test case 6 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(900000):
        testSolution(solution)
