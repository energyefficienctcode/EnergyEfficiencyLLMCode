import java.util.*;

class Solution {
    public int maxPathLength(int[][] coordinates, int k) {
        int n = coordinates.length;
        if (n == 0) return 0;

        // Create a list of points with their original indices
        List<Point> points = new ArrayList<>();
        for(int i = 0; i < n; i++) {
            points.add(new Point(coordinates[i][0], coordinates[i][1], i));
        }

        // Sort points in increasing order of x, then y
        points.sort((a, b) -> {
            if(a.x != b.x) return Integer.compare(a.x, b.x);
            return Integer.compare(a.y, b.y);
        });

        // Compute LIS up to each point
        int[] lis = new int[n];
        Arrays.fill(lis, 1);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(points.get(j).x < points.get(i).x && points.get(j).y < points.get(i).y) {
                    lis[i] = Math.max(lis[i], lis[j] + 1);
                }
            }
        }

        // Sort points in decreasing order of x, then y
        List<Point> reversePoints = new ArrayList<>(points);
        reversePoints.sort((a, b) -> {
            if(b.x != a.x) return Integer.compare(b.x, a.x);
            return Integer.compare(b.y, a.y);
        });

        // Compute LIS from each point
        int[] lds = new int[n];
        Arrays.fill(lds, 1);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(reversePoints.get(j).x > reversePoints.get(i).x && reversePoints.get(j).y > reversePoints.get(i).y) {
                    lds[i] = Math.max(lds[i], lds[j] + 1);
                }
            }
        }

        // Map lds back to original order
        int[] ldsOriginal = new int[n];
        for(int i = 0; i < n; i++) {
            Point p = points.get(i);
            ldsOriginal[p.index] = lds.get(i);
        }

        // Find the maximum path length that includes coordinates[k]
        int targetIndex = k;
        int maxPath = 0;
        for(int i = 0; i < n; i++) {
            if(points.get(i).index == targetIndex) {
                maxPath = lis[i] + lds[i] -1;
                break;
            }
        }

        return maxPath;
    }

    class Point {
        int x;
        int y;
        int index;

        Point(int x, int y, int index){
            this.x = x;
            this.y = y;
            this.index = index;
        }
    }
}

public class Length_of_the_Longest_Increasing_Path {
public static void runTests(Solution solution) {
    // Test case 1: Simple increasing path
    int[][] coordinates1 = {{1, 2}, {2, 3}, {3, 4}};
    int k1 = 0;
    int expected_result1 = 3;  // Entire sequence is an increasing path starting from [1, 2]
    assert solution.maxPathLength(coordinates1, k1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Multiple increasing paths, choose longest one
    int[][] coordinates2 = {{1, 2}, {2, 1}, {2, 3}, {3, 2}, {4, 5}};
    int k2 = 1;
    int expected_result2 = 3;  // Increasing path from [2, 1] -> [3, 2] -> [4, 5]
    assert solution.maxPathLength(coordinates2, k2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: No valid increasing path
    int[][] coordinates3 = {{3, 1}, {2, 2}, {4, 1}, {0, 0}, {5, 3}};
    int k3 = 1;
    int expected_result3 = 3;  // No points form an increasing path starting from [3, 2]
    assert solution.maxPathLength(coordinates3, k3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Path with duplicate points
    int[][] coordinates4 = {{1, 1}, {2, 2}, {2, 2}, {3, 3}};
    int k4 = 0;
    int expected_result4 = 3;  // Increasing path through [1, 1] -> [2, 2] -> [3, 3]
    assert solution.maxPathLength(coordinates4, k4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: All points in one row
    int[][] coordinates5 = {{1, 1}, {2, 1}, {3, 1}, {4, 1}};
    int k5 = 0;
    int expected_result5 = 1;  // All points have the same y-coordinate; no increasing path possible
    assert solution.maxPathLength(coordinates5, k5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Starting point at the end of a long path
    int[][] coordinates6 = {{2, 1}, {7, 0}, {5, 6}};
    int k6 = 2;
    int expected_result6 = 2;  // Longest path starting from [3, 4] is [3, 4] -> [4, 5]
    assert solution.maxPathLength(coordinates6, k6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Points with negative coordinates
    int[][] coordinates7 = {{-1, -1}, {0, 0}, {1, 1}, {2, 2}};
    int k7 = 1;
    int expected_result7 = 4;  // Increasing path from [0, 0] -> [1, 1] -> [2, 2]
    assert solution.maxPathLength(coordinates7, k7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 20000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    