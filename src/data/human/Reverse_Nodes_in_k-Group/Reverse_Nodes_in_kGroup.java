import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode curr = head;
        int count = 0;
        while (curr != null && count != k) { // find the k+1 node
            curr = curr.next;
            count++;
        }
        if (count == k) { // if k+1 node is found
            curr = reverseKGroup(curr, k); // reverse list with k+1 node as head
            // head - head-pointer to direct part,
            // curr - head-pointer to reversed part;
            while (count-- > 0) { // reverse current k-group:
                ListNode tmp = head.next; // tmp - next head in direct part
                head.next = curr; // preappending "direct" head to the reversed list
                curr = head; // move head of reversed part to a new node
                head = tmp; // move "direct" head to the next node in direct part
            }
            head = curr;
        }
        return head;
    }
}
class ListNode {
    int val;
    ListNode next;

    ListNode() {}
    ListNode(int val) { this.val = val; }
    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
}

public class Reverse_Nodes_in_kGroup {
// Definition for singly-linked list.

// Utility function to convert a list to a linked list
public static ListNode listToLinkedList(int[] lst) {
    ListNode dummy = new ListNode();
    ListNode current = dummy;
    for (int val : lst) {
        current.next = new ListNode(val);
        current = current.next;
    }
    return dummy.next;
}

// Utility function to convert a linked list to a list
public static int[] linkedListToList(ListNode node) {
    List<Integer> result = new ArrayList<>();
    while (node != null) {
        result.add(node.val);
        node = node.next;
    }
    return result.stream().mapToInt(i -> i).toArray();
}

// Method to run all test cases
public static void runTests(Solution solution) {
    // Test case 1: List length is a multiple of k
    ListNode head1 = listToLinkedList(new int[]{1, 2, 3, 4, 5});
    int k1 = 2;
    int[] expected_result1 = {2, 1, 4, 3, 5};
    ListNode result1 = solution.reverseKGroup(head1, k1);
    assert Arrays.equals(linkedListToList(result1), expected_result1) : "Test case 1 failed. Expected " + Arrays.toString(expected_result1);

    // Test case 2: List length is not a multiple of k, remaining nodes should stay the same
    ListNode head2 = listToLinkedList(new int[]{1, 2, 3, 4, 5});
    int k2 = 3;
    int[] expected_result2 = {3, 2, 1, 4, 5};
    ListNode result2 = solution.reverseKGroup(head2, k2);
    assert Arrays.equals(linkedListToList(result2), expected_result2) : "Test case 2 failed. Expected " + Arrays.toString(expected_result2);

    // Test case 3: k is 1, list should remain unchanged
    ListNode head3 = listToLinkedList(new int[]{1, 2, 3, 4, 5});
    int k3 = 1;
    int[] expected_result3 = {1, 2, 3, 4, 5};
    ListNode result3 = solution.reverseKGroup(head3, k3);
    assert Arrays.equals(linkedListToList(result3), expected_result3) : "Test case 3 failed. Expected " + Arrays.toString(expected_result3);

    // Test case 4: k equals the length of the list, entire list should be reversed
    ListNode head4 = listToLinkedList(new int[]{1, 2, 3, 4, 5});
    int k4 = 5;
    int[] expected_result4 = {5, 4, 3, 2, 1};
    ListNode result4 = solution.reverseKGroup(head4, k4);
    assert Arrays.equals(linkedListToList(result4), expected_result4) : "Test case 4 failed. Expected " + Arrays.toString(expected_result4);

    // Test case 5: Single node list
    ListNode head5 = listToLinkedList(new int[]{1});
    int k5 = 1;
    int[] expected_result5 = {1};
    ListNode result5 = solution.reverseKGroup(head5, k5);
    assert Arrays.equals(linkedListToList(result5), expected_result5) : "Test case 5 failed. Expected " + Arrays.toString(expected_result5);

    // Test case 6: List length is less than k, list should remain unchanged
    ListNode head6 = listToLinkedList(new int[]{1, 2, 3});
    int k6 = 4;
    int[] expected_result6 = {1, 2, 3};
    ListNode result6 = solution.reverseKGroup(head6, k6);
    assert Arrays.equals(linkedListToList(result6), expected_result6) : "Test case 6 failed. Expected " + Arrays.toString(expected_result6);
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 20000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    