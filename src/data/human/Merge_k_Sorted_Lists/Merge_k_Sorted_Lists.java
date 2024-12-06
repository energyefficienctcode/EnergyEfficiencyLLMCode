import java.util.*;

public class Solution {
    public ListNode mergeKLists(List<ListNode> lists) {
        if (lists==null||lists.size()==0) return null;
        
        PriorityQueue<ListNode> queue= new PriorityQueue<ListNode>(lists.size(),new Comparator<ListNode>(){
            @Override
            public int compare(ListNode o1,ListNode o2){
                if (o1.val<o2.val)
                    return -1;
                else if (o1.val==o2.val)
                    return 0;
                else 
                    return 1;
            }
        });
        
        ListNode dummy = new ListNode(0);
        ListNode tail=dummy;
        
        for (ListNode node:lists)
            if (node!=null)
                queue.add(node);
            
        while (!queue.isEmpty()){
            tail.next=queue.poll();
            tail=tail.next;
            
            if (tail.next!=null)
                queue.add(tail.next);
        }
        return dummy.next;
    }
}

class ListNode {
    int val;
    ListNode next;

    ListNode() {}
    ListNode(int val) { this.val = val; }
    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
}

public class Merge_k_Sorted_Lists {
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
    // Test case 1: Merging three sorted lists
    List<ListNode> lists1 = List.of(new ListNode[]{
            listToLinkedList(new int[]{1, 4, 5}),
            listToLinkedList(new int[]{1, 3, 4}),
            listToLinkedList(new int[]{2, 6})
    });
    int[] expected_result1 = {1, 1, 2, 3, 4, 4, 5, 6};
    ListNode result1 = solution.mergeKLists(lists1);
    assert Arrays.equals(linkedListToList(result1), expected_result1) : "Test case 1 failed. Expected " + Arrays.toString(expected_result1);

    // Test case 2: Single empty list
    List<ListNode> lists2 = List.of(new ListNode[]{});
    int[] expected_result2 = {};
    ListNode result2 = solution.mergeKLists(lists2);
    assert Arrays.equals(linkedListToList(result2), expected_result2) : "Test case 2 failed. Expected " + Arrays.toString(expected_result2);

    // Test case 3: All lists are empty
    List<ListNode> lists3 = List.of(new ListNode[]{});
    int[] expected_result3 = {};
    ListNode result3 = solution.mergeKLists(lists3);
    assert Arrays.equals(linkedListToList(result3), expected_result3) : "Test case 3 failed. Expected " + Arrays.toString(expected_result3);

    // Test case 4: Mixed empty and non-empty lists
    List<ListNode> lists4 = List.of(new ListNode[]{
        listToLinkedList(new int[]{}),
        listToLinkedList(new int[]{1, 3, 4}),
        listToLinkedList(new int[]{2, 6, 7})
    });
    int[] expected_result4 = {1, 2, 3, 4, 6, 7};
    ListNode result4 = solution.mergeKLists(lists4);
    assert Arrays.equals(linkedListToList(result4), expected_result4) : "Test case 4 failed. Expected " + Arrays.toString(expected_result4);

    // Test case 5: All lists with single element
    List<ListNode>  lists5 = List.of(new ListNode[]{
        listToLinkedList(new int[]{1}),
        listToLinkedList(new int[]{0}),
        listToLinkedList(new int[]{5})
    });
    int[] expected_result5 = {0, 1, 5};
    ListNode result5 = solution.mergeKLists(lists5);
    assert Arrays.equals(linkedListToList(result5), expected_result5) : "Test case 5 failed. Expected " + Arrays.toString(expected_result5);

    // Test case 6: No lists provided
    List<ListNode> lists6 = List.of(new ListNode[]{});
    int[] expected_result6 = {};
    ListNode result6 = solution.mergeKLists(lists6);
    assert Arrays.equals(linkedListToList(result6), expected_result6) : "Test case 6 failed. Expected " + Arrays.toString(expected_result6);
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        runTests(solution);   // Ensure your test cases are implemented inside runTests
    }
}

    