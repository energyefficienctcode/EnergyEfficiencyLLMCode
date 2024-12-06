import java.util.PriorityQueue;

class Solution {
    public long minDamage(int power, int[] damage, int[] health) {
        int n = damage.length;
        long totalDamage = 0;

        // Priority queue to process enemies with the highest damage first
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> b[0] - a[0]);
        for (int i = 0; i < n; i++) {
            pq.offer(new int[]{damage[i], health[i]});
        }

        while (!pq.isEmpty()) {
            int[] enemy = pq.poll();
            int enemyDamage = enemy[0];
            int enemyHealth = enemy[1];

            // Calculate the number of seconds this enemy will be alive
            int secondsAlive = (int) Math.ceil((double) enemyHealth / power);

            // Add the damage dealt by this enemy to the total damage
            totalDamage += (long) enemyDamage * secondsAlive;

            // Reduce the health of the enemy by the total damage dealt by Bob
            enemyHealth -= power * secondsAlive;

            // If the enemy is still alive, add it back to the queue
            if (enemyHealth > 0) {
                pq.offer(new int[]{enemyDamage, enemyHealth});
            }
        }

        return totalDamage;
    }
}

public class Minimum_Amount_of_Damage_Dealt_to_Bob {
public static void runTests(Solution solution) {
    // Test case 1: One enemy with minimal damage
    int power1 = 10;
    int[] damage1 = {5};
    int[] health1 = {10};
    int expected_result1 = 5;  // Only one enemy, Bob takes 5 damage per second for 1 second
    assert solution.minDamage(power1, damage1, health1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Multiple enemies with the same health and damage
    int power2 = 4;
    int[] damage2 = {1, 2, 3, 4};
    int[] health2 = {4, 5, 6, 8};
    int expected_result2 = 39;  // Bob takes 9 seconds of damage with 3 damage per second
    assert solution.minDamage(power2, damage2, health2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Varying health and damage, higher power
    int power3 = 1;
    int[] damage3 = {1, 1, 1, 1};
    int[] health3 = {1, 2, 3, 4};
    int expected_result3 = 20;  // Optimal order: kill 3rd enemy first
    assert solution.minDamage(power3, damage3, health3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Power equal to the maximum health, minimal damage
    int power4 = 8;
    int[] damage4 = {40};
    int[] health4 = {59};
    int expected_result4 = 320;  // Bob takes maximum damage for the first second
    assert solution.minDamage(power4, damage4, health4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: High damage but low power, requiring strategic elimination
    int power5 = 2;
    int[] damage5 = {10, 1, 5};
    int[] health5 = {6, 10, 4};
    int expected_result5 = 65;  // Strategic kill order needed
    assert solution.minDamage(power5, damage5, health5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Power greater than all health, instant kills
    int power6 = 50;
    int[] damage6 = {3, 4, 2};
    int[] health6 = {5, 8, 6};
    int expected_result6 = 16;  // All enemies killed immediately
    assert solution.minDamage(power6, damage6, health6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Different damage, minimal power, and high health
    int power7 = 1;
    int[] damage7 = {3, 8, 2};
    int[] health7 = {5, 4, 7};
    int expected_result7 = 91;  // Complex kill order needed for minimum damage
    assert solution.minDamage(power7, damage7, health7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 10000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    