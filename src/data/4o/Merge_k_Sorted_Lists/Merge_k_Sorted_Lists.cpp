#include <queue>
#include <vector>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Lambda comparator for the priority queue (min-heap)
        auto compare = [](ListNode* a, ListNode* b) {
            return a->val > b->val;
        };

        priority_queue<ListNode*, vector<ListNode*>, decltype(compare)> pq(compare);

        // Push the head of each list into the priority queue
        for (auto list : lists) {
            if (list) {
                pq.push(list);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;

        // Merge the lists by always taking the smallest element from the heap
        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();
            tail->next = node;
            tail = tail->next;

            if (node->next) {
                pq.push(node->next);
            }
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
    // Test case 1: Merging three sorted lists
    std::vector<ListNode*> lists = {
        list_to_linkedlist({1, 4, 5}),
        list_to_linkedlist({1, 3, 4}),
        list_to_linkedlist({2, 6})
    };
    std::vector<int> expected_result = {1, 1, 2, 3, 4, 4, 5, 6};
    ListNode* result = solution.mergeKLists(lists);
    assert(linkedlist_to_list(result) == expected_result && "Test case 1 failed.");

    // Test case 2: Single empty list
    lists = {nullptr};
    expected_result = {};
    result = solution.mergeKLists(lists);
    assert(linkedlist_to_list(result) == expected_result && "Test case 2 failed.");

    // Test case 3: All lists are empty
    lists = {nullptr, nullptr, nullptr};
    expected_result = {};
    result = solution.mergeKLists(lists);
    assert(linkedlist_to_list(result) == expected_result && "Test case 3 failed.");

    // Test case 4: Mixed empty and non-empty lists
    lists = {
        list_to_linkedlist({}),
        list_to_linkedlist({1, 3, 4}),
        nullptr,
        list_to_linkedlist({2, 6, 7})
    };
    expected_result = {1, 2, 3, 4, 6, 7};
    result = solution.mergeKLists(lists);
    assert(linkedlist_to_list(result) == expected_result && "Test case 4 failed.");

    // Test case 5: All lists with single element
    lists = {
        list_to_linkedlist({1}),
        list_to_linkedlist({0}),
        list_to_linkedlist({5})
    };
    expected_result = {0, 1, 5};
    result = solution.mergeKLists(lists);
    assert(linkedlist_to_list(result) == expected_result && "Test case 5 failed.");

    // Test case 6: No lists provided
    lists = {};
    expected_result = {};
    result = solution.mergeKLists(lists);
    assert(linkedlist_to_list(result) == expected_result && "Test case 6 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 655360; ++i) {
        testSolution(solution);  
    }
    return 0;
}
