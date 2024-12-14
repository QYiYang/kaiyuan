#include <stdio.h>

// 交换两个元素的值
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 分区函数，选择一个基准元素，并对数组进行分区
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为基准
    int i = low - 1; // 初始化较小元素的索引

    // 遍历数组并将小于基准的元素放到数组的左侧
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) { // 如果当前元素小于基准
            i++;
            swap(&arr[i], &arr[j]); // 交换位置
        }
    }
    swap(&arr[i + 1], &arr[high]); // 将基准元素放到正确的位置
    return i + 1; // 返回基准元素的位置
}

// 快速排序函数，递归地对数组进行排序
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // 对数组进行分区并获取基准的位置
        quick_sort(arr, low, pi - 1);  // 对基准左边的子数组递归排序
        quick_sort(arr, pi + 1, high); // 对基准右边的子数组递归排序
    }
}

int main() {
    int n;

    while (1) {
        printf("请输入数组的大小（输入 0 或负数以结束程序）：");
        scanf("%d", &n);

        if (n <= 0) {
            break; // 如果用户输入 0 或负数，则退出循环
        }

        int arr[n]; // 根据用户输入的大小创建数组

        printf("请输入数组的元素（共 %d 个）：\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]); // 读取用户输入的数组元素
        }

        // 调用快速排序函数
        quick_sort(arr, 0, n - 1);

        // 输出排序后的数组
        printf("排序后的数组: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    printf("程序结束。\n");
    return 0; // 返回 0 表示程序正常结束
}

