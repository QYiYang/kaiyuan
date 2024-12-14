#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// 定义哈夫曼树的节点
typedef struct HuffmanNode {
    char data;               // 节点存储的字符
    int freq;                // 节点的频率
    struct HuffmanNode *left, *right; // 左右子节点
} HuffmanNode;

// 定义最小堆
typedef struct MinHeap {
    int size;                // 当前堆的大小
    int capacity;            // 堆的容量
    HuffmanNode** array;     // 节点数组指针
} MinHeap;

// 创建一个新的哈夫曼节点
HuffmanNode* createNode(char data, int freq) {
    HuffmanNode* newNode = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    newNode->data = data;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 创建一个最小堆
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HuffmanNode**)malloc(minHeap->capacity * sizeof(HuffmanNode*));
    return minHeap;
}

// 交换两个最小堆节点
void swapNode(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* t = *a;
    *a = *b;
    *b = t;
}

// 堆化，保证最小堆的性质
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 提取堆顶的最小节点
HuffmanNode* extractMin(MinHeap* minHeap) {
    HuffmanNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

// 插入一个新的节点到最小堆中
void insertMinHeap(MinHeap* minHeap, HuffmanNode* node) {
    minHeap->size++;
    int i = minHeap->size - 1;

    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// 构建最小堆
MinHeap* buildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], freq[i]);
    minHeap->size = size;

    for (int i = (minHeap->size - 2) / 2; i >= 0; --i)
        minHeapify(minHeap, i);

    return minHeap;
}

// 构建哈夫曼树
HuffmanNode* buildHuffmanTree(char data[], int freq[], int size) {
    HuffmanNode *left, *right, *top;
    MinHeap* minHeap = buildMinHeap(data, freq, size);

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = createNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// 打印哈夫曼编码
void printCodes(HuffmanNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// 哈夫曼编码函数，输入字符和频率
void HuffmanCodes(char data[], int freq[], int size) {
    HuffmanNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_SIZE], top = 0;
    printCodes(root, arr, top);
}

// 主函数
int main() {
    int t;  // 测试案例数量
    printf("请输入测试案例数量: ");
    scanf("%d", &t);

    while (t--) {
        int n;  // 字符数量
        printf("\n请输入字符的数量: ");
        scanf("%d", &n);

        char data[n];
        int freq[n];

        printf("请输入每个字符及其频率:\n");
        for (int i = 0; i < n; i++) {
            printf("字符: ");
            scanf(" %c", &data[i]);
            printf("频率: ");
            scanf("%d", &freq[i]);
        }

        printf("哈夫曼编码为:\n");
        HuffmanCodes(data, freq, n);
    }

    return 0;
}

