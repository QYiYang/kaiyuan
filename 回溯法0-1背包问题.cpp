
#include <stdio.h>
#define MAX_ITEMS 100

int n;                 // 物品数量
int W;                 // 背包容量
int weights[MAX_ITEMS]; // 物品重量数组
int values[MAX_ITEMS];  // 物品价值数组
int max_value = 0;      // 存储最大价值

void knapsack(int index, int current_weight, int current_value) {
    if (index == n) { // 递归终止条件：已考虑所有物品
        if (current_value > max_value) {
            max_value = current_value;
        }
        return;
    }

    // 不选择当前物品
    knapsack(index + 1, current_weight, current_value);

    // 选择当前物品（前提是重量不超过背包容量）
    if (current_weight + weights[index] <= W) {
        knapsack(index + 1, current_weight + weights[index], current_value + values[index]);
    }
}

int main() {
    int test_cases;
    printf("输入测试案例数量: ");
    scanf("%d", &test_cases);

    while (test_cases--) {
        max_value = 0;
        printf("\n输入物品数量和背包容量: ");
        scanf("%d %d", &n, &W);

        printf("输入物品的重量和价值: \n");
        for (int i = 0; i < n; i++) 1{
            scanf("%d %d", &weights[i], &values[i]);
        }

        knapsack(0, 0, 0);

        printf("背包的最大价值为: %d\n", max_value);
    }

    return 0;
}

