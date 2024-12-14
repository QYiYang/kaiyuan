#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int left, int right);
int quickSelect(int arr[], int left, int right, int k);
void swap(int *a, int *b);

// 主函数，支持多组输入测试数据
int main() {
    int t;
    printf("请输入测试数据的组数: ");
    scanf("%d", &t);
    while (t--) {
        int n, k;
        printf("\n请输入数组的元素个数: ");
        scanf("%d", &n);
        int *arr = (int *)malloc(n * sizeof(int));
        printf("请输入数组元素: ");
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        printf("请输入 k 的值(要找第 k 小的元素): ");
        scanf("%d", &k);

        int result = quickSelect(arr, 0, n - 1, k);
        printf("数组中第 %d 小的元素是: %d\n", k, result);
        free(arr);
    }
    return 0;
}

// 分治选择算法的实现
int quickSelect(int arr[], int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }

    // 使用划分函数选择一个主元位置
    int pivotIndex = partition(arr, left, right);
    int rank = pivotIndex - left + 1;

    if (k == rank) {
        return arr[pivotIndex];
    } else if (k < rank) {
        return quickSelect(arr, left, pivotIndex - 1, k);
    } else {
        return quickSelect(arr, pivotIndex + 1, right, k - rank);
    }
}

// 对数组进行划分
int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivot) {
            swap(&arr[i], &arr[storeIndex]);
            storeIndex++;
        }
    }
    swap(&arr[storeIndex], &arr[right]);
    return storeIndex;
}

// 交换两个数的值
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
