# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution(object):
    def reverseKGroup(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """
        def reverseLinkedList(head, k):
            prev, curr = None, head
            while k:
                next_node = curr.next
                curr.next = prev
                prev = curr
                curr = next_node
                k -= 1
            return prev

        count = 0
        ptr = head
        while ptr and count < k:
            ptr = ptr.next
            count += 1

        if count == k:
            reversed_head = reverseLinkedList(head, k)
            head.next = self.reverseKGroup(ptr, k)
            return reversed_head

        return head

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
    for i in range(1000000):
        testSolution(solution)
