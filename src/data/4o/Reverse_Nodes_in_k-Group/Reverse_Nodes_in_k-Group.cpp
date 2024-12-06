#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) return head;

        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* curr = dummy, *prev = dummy, *next = dummy;
        int count = 0;

        // Count the number of nodes in the list
        while (curr->next) {
            curr = curr->next;
            count++;
        }

        // Reverse every k-group
        while (count >= k) {
            curr = prev->next;
            next = curr->next;
            for (int i = 1; i < k; ++i) {
                curr->next = next->next;
                next->next = prev->next;
                prev->next = next;
                next = curr->next;
            }
            prev = curr;
            count -= k;
        }

        return dummy->next;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Helper function to convert vector to linked list
ListNode* list_to_linkedlist(const std::vector<int>& lst) {
    ListNode* dummy = new ListNode();
    ListNode* current = dummy;
    for (int val : lst) {
        current->next = new ListNode(val);
        current = current->next;
    }
    return dummy->next;
}

// Helper function to convert linked list to vector
std::vector<int> linkedlist_to_list(ListNode* node) {
    std::vector<int> result;
    while (node) {
        result.push_back(node->val);
        node = node->next;
    }
    return result;
}

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: List length is a multiple of k
    ListNode* head = list_to_linkedlist({1, 2, 3, 4, 5});
    int k = 2;
    std::vector<int> expected_result = {2, 1, 4, 3, 5};
    ListNode* result = solution.reverseKGroup(head, k);
    assert(linkedlist_to_list(result) == expected_result && "Test case 1 failed.");

    // Test case 2: List length is not a multiple of k, remaining nodes should stay the same
    head = list_to_linkedlist({1, 2, 3, 4, 5});
    k = 3;
    expected_result = {3, 2, 1, 4, 5};
    result = solution.reverseKGroup(head, k);
    assert(linkedlist_to_list(result) == expected_result && "Test case 2 failed.");

    // Test case 3: k is 1, list should remain unchanged
    head = list_to_linkedlist({1, 2, 3, 4, 5});
    k = 1;
    expected_result = {1, 2, 3, 4, 5};
    result = solution.reverseKGroup(head, k);
    assert(linkedlist_to_list(result) == expected_result && "Test case 3 failed.");

    // Test case 4: k equals the length of the list, entire list should be reversed
    head = list_to_linkedlist({1, 2, 3, 4, 5});
    k = 5;
    expected_result = {5, 4, 3, 2, 1};
    result = solution.reverseKGroup(head, k);
    assert(linkedlist_to_list(result) == expected_result && "Test case 4 failed.");

    // Test case 5: Single node list
    head = list_to_linkedlist({1});
    k = 1;
    expected_result = {1};
    result = solution.reverseKGroup(head, k);
    assert(linkedlist_to_list(result) == expected_result && "Test case 5 failed.");

    // Test case 6: List length is less than k, list should remain unchanged
    head = list_to_linkedlist({1, 2, 3});
    k = 4;
    expected_result = {1, 2, 3};
    result = solution.reverseKGroup(head, k);
    assert(linkedlist_to_list(result) == expected_result && "Test case 6 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 655360; ++i) {
        testSolution(solution);  
    }
    return 0;
}
