import java.util.PriorityQueue;
import java.util.Comparator;

class Solution {
    public ListNode mergeKLists(ListNode[] lists) {
        if (lists == null || lists.length == 0) return null;
        
        PriorityQueue<ListNode> heap = new PriorityQueue<>(new Comparator<ListNode>() {
            public int compare(ListNode a, ListNode b) {
                return a.val - b.val;
            }
        });
        
        for (ListNode node : lists) {
            if (node != null) {
                heap.offer(node);
            }
        }
        
        ListNode dummy = new ListNode(0);
        ListNode current = dummy;
        
        while (!heap.isEmpty()) {
            ListNode minNode = heap.poll();
            current.next = minNode;
            current = current.next;
            if (minNode.next != null) {
                heap.offer(minNode.next);
            }
        }
        
        return dummy.next;
    }
}

public class Merge_k_Sorted_Lists {
// Definition for singly-linked list.
class ListNode {
    int val;
    ListNode next;

    ListNode() {}
    ListNode(int val) { this.val = val; }
    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
}

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
    // Test case 1: Merging three sorted lists
    ListNode[] lists1 = {
        listToLinkedList(new int[]{1, 4, 5}),
        listToLinkedList(new int[]{1, 3, 4}),
        listToLinkedList(new int[]{2, 6})
    };
    int[] expected_result1 = {1, 1, 2, 3, 4, 4, 5, 6};
    ListNode result1 = solution.mergeKLists(lists1);
    assert Arrays.equals(linkedListToList(result1), expected_result1) : "Test case 1 failed. Expected " + Arrays.toString(expected_result1);

    // Test case 2: Single empty list
    ListNode[] lists2 = {null};
    int[] expected_result2 = {};
    ListNode result2 = solution.mergeKLists(lists2);
    assert Arrays.equals(linkedListToList(result2), expected_result2) : "Test case 2 failed. Expected " + Arrays.toString(expected_result2);

    // Test case 3: All lists are empty
    ListNode[] lists3 = {null, null, null};
    int[] expected_result3 = {};
    ListNode result3 = solution.mergeKLists(lists3);
    assert Arrays.equals(linkedListToList(result3), expected_result3) : "Test case 3 failed. Expected " + Arrays.toString(expected_result3);

    // Test case 4: Mixed empty and non-empty lists
    ListNode[] lists4 = {
        listToLinkedList(new int[]{}),
        listToLinkedList(new int[]{1, 3, 4}),
        null,
        listToLinkedList(new int[]{2, 6, 7})
    };
    int[] expected_result4 = {1, 2, 3, 4, 6, 7};
    ListNode result4 = solution.mergeKLists(lists4);
    assert Arrays.equals(linkedListToList(result4), expected_result4) : "Test case 4 failed. Expected " + Arrays.toString(expected_result4);

    // Test case 5: All lists with single element
    ListNode[] lists5 = {
        listToLinkedList(new int[]{1}),
        listToLinkedList(new int[]{0}),
        listToLinkedList(new int[]{5})
    };
    int[] expected_result5 = {0, 1, 5};
    ListNode result5 = solution.mergeKLists(lists5);
    assert Arrays.equals(linkedListToList(result5), expected_result5) : "Test case 5 failed. Expected " + Arrays.toString(expected_result5);

    // Test case 6: No lists provided
    ListNode[] lists6 = {};
    int[] expected_result6 = {};
    ListNode result6 = solution.mergeKLists(lists6);
    assert Arrays.equals(linkedListToList(result6), expected_result6) : "Test case 6 failed. Expected " + Arrays.toString(expected_result6);
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        runTests(solution);   // Ensure your test cases are implemented inside runTests
    }
}

    