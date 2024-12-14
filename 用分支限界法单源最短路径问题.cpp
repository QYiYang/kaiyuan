#include <stdio.h>  // �����׼���������
#include <stdlib.h> // �����׼��
#include <limits.h> // �������ڶ��峣�� INT_MAX ��ͷ�ļ�

#define MAX_NODES 100  // ����ͼ�����ڵ���
#define INF INT_MAX    // �������޴�Ϊ INT_MAX����ʾ��ʼ���벻�ɴ�

// �����ڽӱ������ڵ�ṹ��
typedef struct AdjListNode {
    int dest;                     // Ŀ��ڵ�
    int weight;                   // �ߵ�Ȩ��
    struct AdjListNode* next;     // ָ����һ���ڽӽڵ��ָ��
} AdjListNode;

// ����ͼ�ṹ�壬�����ڽӱ�����
typedef struct Graph {
    int V;                        // ͼ�Ķ�������
    AdjListNode* array[MAX_NODES]; // �ڽӱ�����
} Graph;

// ��С�ѵĽڵ�ṹ��
typedef struct MinHeapNode {
    int v;                        // �ڵ�����
    int dist;                     // ��ǰ�ڵ����̾���
} MinHeapNode;

// ��С�ѽṹ��
typedef struct MinHeap {
    int size;                     // �ѵĵ�ǰ��С
    int capacity;                 // �ѵ�����
    int pos[MAX_NODES];           // ��¼ÿ���ڵ��ڶ��е�λ��
    MinHeapNode* array[MAX_NODES];// �洢�ѽڵ�
} MinHeap;

// ����һ���µ��ڽӱ�ڵ�
AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode)); // Ϊ�½ڵ�����ڴ�
    newNode->dest = dest;            // ����Ŀ��ڵ�
    newNode->weight = weight;        // ���ñߵ�Ȩ��
    newNode->next = NULL;            // ������һ���ڵ�Ϊ��
    return newNode;                  // �����´����Ľڵ�
}

// ����һ���µ�ͼ��������Ϊ V
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph)); // Ϊͼ�����ڴ�
    graph->V = V;                                 // ����ͼ�Ķ�������
    for (int i = 0; i < V; ++i) {                  // ��ʼ���ڽӱ�����
        graph->array[i] = NULL;
    }
    return graph;                                  // �����´�����ͼ
}

// ��ͼ�����һ����
void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* newNode = newAdjListNode(dest, weight); // �����½ڵ��ʾ��
    newNode->next = graph->array[src];                   // ���½ڵ�����ڽӱ�
    graph->array[src] = newNode;
}

// ����һ���µ���С�ѽڵ�
MinHeapNode* newMinHeapNode(int v, int dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode)); // Ϊ�¶ѽڵ�����ڴ�
    minHeapNode->v = v;            // ���ýڵ�����
    minHeapNode->dist = dist;      // ���þ���
    return minHeapNode;            // �����¶ѽڵ�
}

// ����һ����С�ѣ�����Ϊ capacity
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap)); // Ϊ��С�ѷ����ڴ�
    minHeap->size = 0;           // ��ʼ���Ѵ�СΪ 0
    minHeap->capacity = capacity; // ���öѵ�����
    for (int i = 0; i < capacity; ++i) { // ��ʼ���ѵĽڵ�λ������
        minHeap->pos[i] = i;
        minHeap->array[i] = NULL;
    }
    return minHeap;              // �����´�������С��
}

// ����������С�ѽڵ��ֵ
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a; // ��ʱ����ڵ� a
    *a = *b;             // �����ڵ� a �� b
    *b = t;              // ����ʱ�����ֵ���� b
}

// �ѻ�������ά���ѵ���С����
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;                 // ��ʼ����СֵΪ��ǰ�ڵ�
    left = 2 * idx + 1;             // ���ӽڵ�����
    right = 2 * idx + 2;            // ���ӽڵ�����

    // ������ӽڵ��С���������С�ڵ�����
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist) {
        smallest = left;
    }

    // ������ӽڵ��С���������С�ڵ�����
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist) {
        smallest = right;
    }

    // �����С�ڵ㲻�ǵ�ǰ�ڵ㣬���н������ݹ�ѻ�
    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        // ���¶��нڵ�λ��
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // ���������ڵ�
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        // �ݹ�ѻ�
        minHeapify(minHeap, smallest);
    }
}

// �����С���Ƿ�Ϊ��
int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0; // ���Ѵ�СΪ 0 ʱ���� 1����ʾ��Ϊ��
}

// ����С������ȡ������С����Ľڵ�
MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return NULL; // �����Ϊ�գ����� NULL
    }

    MinHeapNode* root = minHeap->array[0]; // ��ȡ�ѵĸ��ڵ㣨��Сֵ�ڵ㣩

    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; // ��ȡ�ѵ����һ���ڵ�
    minHeap->array[0] = lastNode; // �����һ���ڵ�ŵ����ڵ��λ��

    // ����λ������
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // ��С�ѵĴ�С��ִ�жѻ�����
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root; // ������ȡ����С�ڵ�
}

// ��С��С���нڵ� v �ľ���ֵ
void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v]; // ��ȡ�ڵ� v �ڶ��е�λ��
    minHeap->array[i]->dist = dist; // ���¾���ֵ

    // ���϶ѻ���ȷ����С�ѵ�����
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2; // ���µ�ǰ�ڵ�����
    }
}

// ���ڵ��Ƿ�����С����
int isInMinHeap(MinHeap* minHeap, int v) {
    return minHeap->pos[v] < minHeap->size; // ���ؽڵ� v �Ƿ��ڶ���
}

// ʹ�� Dijkstra �㷨���㵥Դ���·��
void dijkstra(Graph* graph, int src) {
    int V = graph->V; // ��ȡͼ�Ķ�������
    int dist[MAX_NODES]; // �洢Դ�ڵ㵽�����ڵ����̾���

    MinHeap* minHeap = createMinHeap(V); // ������С��

    // ��ʼ����С�Ѻ;�������
    for (int v = 0; v < V; ++v) {
        dist[v] = INF; // �������нڵ�ĳ�ʼ����Ϊ���޴�
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // ����Դ�ڵ�ľ���Ϊ 0��������������
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V; // ���öѵĳ�ʼ��СΪͼ�Ľڵ�����

    // ����С�Ѳ�Ϊ��ʱ��������ȡ��С����ڵ㲢�������ڽڵ�
    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        // ����������ڵ� u ���ڵĽڵ�
        AdjListNode* pCrawl = graph->array[u];
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            // ����ڵ� v �ڶ��У����ҵ�����·��������¾���
            if (isInMinHeap(minHeap, v) && dist[u] != INF && pCrawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight; // ���½ڵ� v ����̾���
                decreaseKey(minHeap, v, dist[v]); // ������С���еľ���ֵ
            }
            pCrawl = pCrawl->next; // ����������һ���ڽӽڵ�
        }
    }

    // ��ӡԴ�ڵ㵽�����ڵ����̾���
    printf("�ڵ� %d �������ڵ����̾��룺\n", src);
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF) {
            printf("���ڵ� %d �ľ���Ϊ�����ɴ�\n", i); // �������Ϊ INF����ʾ���ɴ�
        } else {
            printf("���ڵ� %d �ľ���Ϊ��%d\n", i, dist[i]);
        }
    }
}

// ���������������벢���� Dijkstra �㷨
int main() {
    int T; // ������������
    printf("��������԰���������");
    scanf("%d", &T); // �����������������

    while (T--) {
        int V, E, src;
        printf("������ڵ����� V �ͱ����� E��");
        scanf("%d %d", &V, &E); // ����ڵ�ͱߵ�����

        Graph* graph = createGraph(V); // ����ͼ

        printf("������ÿ���ߵ���㡢�յ��Ȩ�أ�\n");
        for (int i = 0; i < E; ++i) {
            int src, dest, weight;
            scanf("%d %d %d", &src, &dest, &weight); // ����ÿ���ߵ���Ϣ
            addEdge(graph, src, dest, weight); // ��ͼ����ӱ�
        }

        printf("��������ʼ�ڵ㣺");
        scanf("%d", &src); // ����Դ�ڵ�

        dijkstra(graph, src); // ���� Dijkstra �㷨
    }

    return 0; // ��������
}

