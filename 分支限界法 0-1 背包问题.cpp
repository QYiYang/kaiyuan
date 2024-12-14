#include <stdio.h>

#define MAX_ITEMS 100
#define MAX_CAPACITY 1000

typedef struct {
    int index;      // 当前物品索引
    int totalWeight; // 当前背包重量
    int totalValue;  // 当前背包价值
    float bound;     // 上界
} Node;

int n, W;  // 物品数目，背包容量
int weights[MAX_ITEMS], values[MAX_ITEMS];  // 物品的重量和价值

// 计算上界（贪心上界）
float calculateBound(Node node) {
    int totalWeight = node.totalWeight;
    int totalValue = node.totalValue;
    int index = node.index;
    if (totalWeight > W) return 0;  // 超过背包容量，不合法
    
    // 计算上界
    float bound = totalValue;
    while (index < n && totalWeight + weights[index] <= W) {
        totalWeight += weights[index];
        bound += values[index];
        index++;
    }
    // 如果还有剩余空间但没有更多物品，按价值/重量的比例计算
    if (index < n) {
        bound += (W - totalWeight) * values[index] / (float)weights[index];
    }
    return bound;
}

// 分支限界法
int knapsackBranchBound() {
    Node heap[MAX_ITEMS * 2];  // 使用堆来存储节点
    int heapSize = 0;
    
    // 初始化第一个节点
    heap[heapSize].index = 0;
    heap[heapSize].totalWeight = 0;
    heap[heapSize].totalValue = 0;
    heap[heapSize].bound = calculateBound(heap[heapSize]);
    
    int bestValue = 0;  // 记录当前最优解
    
    while (heapSize >= 0) {
        Node currentNode = heap[heapSize];
        heapSize--;
        
        // 如果当前节点的上界小于等于当前最优解，剪枝
        if (currentNode.bound <= bestValue) {
            continue;
        }
        
        // 如果所有物品都被考察过，更新最优解
        if (currentNode.index == n) {
            if (currentNode.totalValue > bestValue) {
                bestValue = currentNode.totalValue;
            }
            continue;
        }
        
        // 选择不放入当前物品
        Node nextNode = currentNode;
        nextNode.index++;
        nextNode.bound = calculateBound(nextNode);
        if (nextNode.bound > bestValue) {
            heap[++heapSize] = nextNode;  // 放入堆中
        }

        // 选择放入当前物品
        if (currentNode.totalWeight + weights[currentNode.index] <= W) {
            nextNode = currentNode;
            nextNode.index++;
            nextNode.totalWeight += weights[currentNode.index];
            nextNode.totalValue += values[currentNode.index];
            nextNode.bound = calculateBound(nextNode);
            if (nextNode.bound > bestValue) {
                heap[++heapSize] = nextNode;  // 放入堆中
            }
        }
    }
    
    return bestValue;
}

// 主程序
int main() {
    int T;
    printf("请输入测试用例的数量：");
    scanf("%d", &T);
    
    while (T--) {
        printf("请输入物品的数量和背包容量：\n");
        scanf("%d %d", &n, &W);
        
        printf("请输入每个物品的重量和价值：\n");
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &weights[i], &values[i]);
        }
        
        int result = knapsackBranchBound();
        printf("最大总价值是：%d\n", result);
    }
    
    return 0;
}

