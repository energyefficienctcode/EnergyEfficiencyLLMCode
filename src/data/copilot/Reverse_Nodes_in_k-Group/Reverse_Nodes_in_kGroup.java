import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class ListNode {
    int val;
    ListNode next;

    ListNode() {}
    ListNode(int val) { this.val = val; }
    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
}


class Solution {
    public ListNode reverseKGroup(ListNode head, int k) {
        if (head == null || k == 1) {
            return head;
        }
        
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode curr = dummy, nex = dummy, pre = dummy;
        int count = 0;
        
        while (curr.next != null) {
            curr = curr.next;
            count++;
        }
        
        while (count >= k) {
            curr = pre.next;
            nex = curr.next;
            for (int i = 1; i < k; i++) {
                curr.next = nex.next;
                nex.next = pre.next;
                pre.next = nex;
                nex = curr.next;
            }
            pre = curr;
            count -= k;
        }
        
        return dummy.next;
    }
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

    