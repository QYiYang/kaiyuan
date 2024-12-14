#include <stdio.h>

#define MAX_ITEMS 100
#define MAX_CAPACITY 1000

typedef struct {
    int index;      // ��ǰ��Ʒ����
    int totalWeight; // ��ǰ��������
    int totalValue;  // ��ǰ������ֵ
    float bound;     // �Ͻ�
} Node;

int n, W;  // ��Ʒ��Ŀ����������
int weights[MAX_ITEMS], values[MAX_ITEMS];  // ��Ʒ�������ͼ�ֵ

// �����Ͻ磨̰���Ͻ磩
float calculateBound(Node node) {
    int totalWeight = node.totalWeight;
    int totalValue = node.totalValue;
    int index = node.index;
    if (totalWeight > W) return 0;  // �����������������Ϸ�
    
    // �����Ͻ�
    float bound = totalValue;
    while (index < n && totalWeight + weights[index] <= W) {
        totalWeight += weights[index];
        bound += values[index];
        index++;
    }
    // �������ʣ��ռ䵫û�и�����Ʒ������ֵ/�����ı�������
    if (index < n) {
        bound += (W - totalWeight) * values[index] / (float)weights[index];
    }
    return bound;
}

// ��֧�޽編
int knapsackBranchBound() {
    Node heap[MAX_ITEMS * 2];  // ʹ�ö����洢�ڵ�
    int heapSize = 0;
    
    // ��ʼ����һ���ڵ�
    heap[heapSize].index = 0;
    heap[heapSize].totalWeight = 0;
    heap[heapSize].totalValue = 0;
    heap[heapSize].bound = calculateBound(heap[heapSize]);
    
    int bestValue = 0;  // ��¼��ǰ���Ž�
    
    while (heapSize >= 0) {
        Node currentNode = heap[heapSize];
        heapSize--;
        
        // �����ǰ�ڵ���Ͻ�С�ڵ��ڵ�ǰ���Ž⣬��֦
        if (currentNode.bound <= bestValue) {
            continue;
        }
        
        // ���������Ʒ������������������Ž�
        if (currentNode.index == n) {
            if (currentNode.totalValue > bestValue) {
                bestValue = currentNode.totalValue;
            }
            continue;
        }
        
        // ѡ�񲻷��뵱ǰ��Ʒ
        Node nextNode = currentNode;
        nextNode.index++;
        nextNode.bound = calculateBound(nextNode);
        if (nextNode.bound > bestValue) {
            heap[++heapSize] = nextNode;  // �������
        }

        // ѡ����뵱ǰ��Ʒ
        if (currentNode.totalWeight + weights[currentNode.index] <= W) {
            nextNode = currentNode;
            nextNode.index++;
            nextNode.totalWeight += weights[currentNode.index];
            nextNode.totalValue += values[currentNode.index];
            nextNode.bound = calculateBound(nextNode);
            if (nextNode.bound > bestValue) {
                heap[++heapSize] = nextNode;  // �������
            }
        }
    }
    
    return bestValue;
}

// ������
int main() {
    int T;
    printf("���������������������");
    scanf("%d", &T);
    
    while (T--) {
        printf("��������Ʒ�������ͱ���������\n");
        scanf("%d %d", &n, &W);
        
        printf("������ÿ����Ʒ�������ͼ�ֵ��\n");
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &weights[i], &values[i]);
        }
        
        int result = knapsackBranchBound();
        printf("����ܼ�ֵ�ǣ�%d\n", result);
    }
    
    return 0;
}

