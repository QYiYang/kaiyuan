#include <stdio.h>  // 引入标准输入输出库
#include <stdlib.h> // 引入标准库
#include <limits.h> // 引入用于定义常量 INT_MAX 的头文件

#define MAX_NODES 100  // 定义图中最大节点数
#define INF INT_MAX    // 定义无限大为 INT_MAX，表示初始距离不可达

// 定义邻接表的链表节点结构体
typedef struct AdjListNode {
    int dest;                     // 目标节点
    int weight;                   // 边的权重
    struct AdjListNode* next;     // 指向下一个邻接节点的指针
} AdjListNode;

// 定义图结构体，包含邻接表数组
typedef struct Graph {
    int V;                        // 图的顶点数量
    AdjListNode* array[MAX_NODES]; // 邻接表数组
} Graph;

// 最小堆的节点结构体
typedef struct MinHeapNode {
    int v;                        // 节点索引
    int dist;                     // 当前节点的最短距离
} MinHeapNode;

// 最小堆结构体
typedef struct MinHeap {
    int size;                     // 堆的当前大小
    int capacity;                 // 堆的容量
    int pos[MAX_NODES];           // 记录每个节点在堆中的位置
    MinHeapNode* array[MAX_NODES];// 存储堆节点
} MinHeap;

// 创建一个新的邻接表节点
AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode)); // 为新节点分配内存
    newNode->dest = dest;            // 设置目标节点
    newNode->weight = weight;        // 设置边的权重
    newNode->next = NULL;            // 设置下一个节点为空
    return newNode;                  // 返回新创建的节点
}

// 创建一个新的图，顶点数为 V
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph)); // 为图分配内存
    graph->V = V;                                 // 设置图的顶点数量
    for (int i = 0; i < V; ++i) {                  // 初始化邻接表数组
        graph->array[i] = NULL;
    }
    return graph;                                  // 返回新创建的图
}

// 向图中添加一条边
void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* newNode = newAdjListNode(dest, weight); // 创建新节点表示边
    newNode->next = graph->array[src];                   // 将新节点插入邻接表
    graph->array[src] = newNode;
}

// 创建一个新的最小堆节点
MinHeapNode* newMinHeapNode(int v, int dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode)); // 为新堆节点分配内存
    minHeapNode->v = v;            // 设置节点索引
    minHeapNode->dist = dist;      // 设置距离
    return minHeapNode;            // 返回新堆节点
}

// 创建一个最小堆，容量为 capacity
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap)); // 为最小堆分配内存
    minHeap->size = 0;           // 初始化堆大小为 0
    minHeap->capacity = capacity; // 设置堆的容量
    for (int i = 0; i < capacity; ++i) { // 初始化堆的节点位置数组
        minHeap->pos[i] = i;
        minHeap->array[i] = NULL;
    }
    return minHeap;              // 返回新创建的最小堆
}

// 交换两个最小堆节点的值
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a; // 临时保存节点 a
    *a = *b;             // 交换节点 a 和 b
    *b = t;              // 将临时保存的值赋给 b
}

// 堆化操作，维护堆的最小性质
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;                 // 初始化最小值为当前节点
    left = 2 * idx + 1;             // 左子节点索引
    right = 2 * idx + 2;            // 右子节点索引

    // 如果左子节点更小，则更新最小节点索引
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist) {
        smallest = left;
    }

    // 如果右子节点更小，则更新最小节点索引
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist) {
        smallest = right;
    }

    // 如果最小节点不是当前节点，进行交换并递归堆化
    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        // 更新堆中节点位置
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // 交换两个节点
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        // 递归堆化
        minHeapify(minHeap, smallest);
    }
}

// 检查最小堆是否为空
int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0; // 当堆大小为 0 时返回 1，表示堆为空
}

// 从最小堆中提取具有最小距离的节点
MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return NULL; // 如果堆为空，返回 NULL
    }

    MinHeapNode* root = minHeap->array[0]; // 获取堆的根节点（最小值节点）

    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; // 获取堆的最后一个节点
    minHeap->array[0] = lastNode; // 将最后一个节点放到根节点的位置

    // 更新位置数组
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // 减小堆的大小并执行堆化操作
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root; // 返回提取的最小节点
}

// 减小最小堆中节点 v 的距离值
void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v]; // 获取节点 v 在堆中的位置
    minHeap->array[i]->dist = dist; // 更新距离值

    // 向上堆化，确保最小堆的性质
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2; // 更新当前节点索引
    }
}

// 检查节点是否在最小堆中
int isInMinHeap(MinHeap* minHeap, int v) {
    return minHeap->pos[v] < minHeap->size; // 返回节点 v 是否在堆中
}

// 使用 Dijkstra 算法计算单源最短路径
void dijkstra(Graph* graph, int src) {
    int V = graph->V; // 获取图的顶点数量
    int dist[MAX_NODES]; // 存储源节点到各个节点的最短距离

    MinHeap* minHeap = createMinHeap(V); // 创建最小堆

    // 初始化最小堆和距离数组
    for (int v = 0; v < V; ++v) {
        dist[v] = INF; // 设置所有节点的初始距离为无限大
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // 设置源节点的距离为 0，并将其插入堆中
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V; // 设置堆的初始大小为图的节点数量

    // 当最小堆不为空时，继续提取最小距离节点并更新相邻节点
    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        // 遍历所有与节点 u 相邻的节点
        AdjListNode* pCrawl = graph->array[u];
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            // 如果节点 v 在堆中，且找到更短路径，则更新距离
            if (isInMinHeap(minHeap, v) && dist[u] != INF && pCrawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight; // 更新节点 v 的最短距离
                decreaseKey(minHeap, v, dist[v]); // 更新最小堆中的距离值
            }
            pCrawl = pCrawl->next; // 继续遍历下一个邻接节点
        }
    }

    // 打印源节点到各个节点的最短距离
    printf("节点 %d 到各个节点的最短距离：\n", src);
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF) {
            printf("到节点 %d 的距离为：不可达\n", i); // 如果距离为 INF，表示不可达
        } else {
            printf("到节点 %d 的距离为：%d\n", i, dist[i]);
        }
    }
}

// 主函数，负责输入并调用 Dijkstra 算法
int main() {
    int T; // 测试用例数量
    printf("请输入测试案例数量：");
    scanf("%d", &T); // 输入测试用例的数量

    while (T--) {
        int V, E, src;
        printf("请输入节点数量 V 和边数量 E：");
        scanf("%d %d", &V, &E); // 输入节点和边的数量

        Graph* graph = createGraph(V); // 创建图

        printf("请输入每条边的起点、终点和权重：\n");
        for (int i = 0; i < E; ++i) {
            int src, dest, weight;
            scanf("%d %d %d", &src, &dest, &weight); // 输入每条边的信息
            addEdge(graph, src, dest, weight); // 向图中添加边
        }

        printf("请输入起始节点：");
        scanf("%d", &src); // 输入源节点

        dijkstra(graph, src); // 调用 Dijkstra 算法
    }

    return 0; // 结束程序
}

