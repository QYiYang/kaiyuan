#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// ������������Ľڵ�
typedef struct HuffmanNode {
    char data;               // �ڵ�洢���ַ�
    int freq;                // �ڵ��Ƶ��
    struct HuffmanNode *left, *right; // �����ӽڵ�
} HuffmanNode;

// ������С��
typedef struct MinHeap {
    int size;                // ��ǰ�ѵĴ�С
    int capacity;            // �ѵ�����
    HuffmanNode** array;     // �ڵ�����ָ��
} MinHeap;

// ����һ���µĹ������ڵ�
HuffmanNode* createNode(char data, int freq) {
    HuffmanNode* newNode = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    newNode->data = data;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// ����һ����С��
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HuffmanNode**)malloc(minHeap->capacity * sizeof(HuffmanNode*));
    return minHeap;
}

// ����������С�ѽڵ�
void swapNode(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* t = *a;
    *a = *b;
    *b = t;
}

// �ѻ�����֤��С�ѵ�����
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

// ��ȡ�Ѷ�����С�ڵ�
HuffmanNode* extractMin(MinHeap* minHeap) {
    HuffmanNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

// ����һ���µĽڵ㵽��С����
void insertMinHeap(MinHeap* minHeap, HuffmanNode* node) {
    minHeap->size++;
    int i = minHeap->size - 1;

    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// ������С��
MinHeap* buildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], freq[i]);
    minHeap->size = size;

    for (int i = (minHeap->size - 2) / 2; i >= 0; --i)
        minHeapify(minHeap, i);

    return minHeap;
}

// ������������
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

// ��ӡ����������
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

// ���������뺯���������ַ���Ƶ��
void HuffmanCodes(char data[], int freq[], int size) {
    HuffmanNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_SIZE], top = 0;
    printCodes(root, arr, top);
}

// ������
int main() {
    int t;  // ���԰�������
    printf("��������԰�������: ");
    scanf("%d", &t);

    while (t--) {
        int n;  // �ַ�����
        printf("\n�������ַ�������: ");
        scanf("%d", &n);

        char data[n];
        int freq[n];

        printf("������ÿ���ַ�����Ƶ��:\n");
        for (int i = 0; i < n; i++) {
            printf("�ַ�: ");
            scanf(" %c", &data[i]);
            printf("Ƶ��: ");
            scanf("%d", &freq[i]);
        }

        printf("����������Ϊ:\n");
        HuffmanCodes(data, freq, n);
    }

    return 0;
}

