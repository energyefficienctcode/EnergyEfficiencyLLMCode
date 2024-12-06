#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if(lists.empty()){
            return nullptr;
        }
        while(lists.size() > 1){
            lists.push_back(mergeTwoLists(lists[0], lists[1]));
            lists.erase(lists.begin());
            lists.erase(lists.begin());
        }
        return lists.front();
    }
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if(l1 == nullptr){
            return l2;
        }
        if(l2 == nullptr){
            return l1;
        }
        if(l1->val <= l2->val){
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else{
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
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
