#include <stdio.h>

// 二分搜索函数的递归实现
int binary_search(int arr[], int low, int high, int target) {
    if (low > high) {
        return -1; // 如果低位索引大于高位索引，说明没有找到目标值，返回 -1
    }
    int mid = (low + high) / 2; // 计算中间位置
    if (arr[mid] == target) {
        return mid; // 如果中间元素就是目标值，返回中间位置的索引
    } else if (arr[mid] > target) {
        return binary_search(arr, low, mid - 1, target); // 如果目标值小于中间值，递归在左半部分查找
    } else {
        return binary_search(arr, mid + 1, high, target); // 如果目标值大于中间值，递归在右半部分查找
    }
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13}; // 初始化一个有序数组
    int target = 7; // 要查找的目标值
    int n = sizeof(arr) / sizeof(arr[0]); // 计算数组的长度
    int result = binary_search(arr, 0, n - 1, target); // 调用二分搜索函数
    if (result != -1) {
        printf("目标 %d 的索引是: %d\n", target, result); // 如果找到，打印目标值的索引
    } else {
        printf("目标 %d 未找到\n", target); // 如果未找到，打印未找到的信息
    }
    return 0; 
}

