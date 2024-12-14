#include <stdio.h>
#include <limits.h>

// 函数声明，用于打印最优的括号化顺序
void printOptimalParens(int s[][10], int i, int j);

// 矩阵链乘法的动态规划实现
void matrixChainOrder(int p[], int n) {
    int m[10][10]; // 存储最小乘法次数的矩阵，假设最多支持10个矩阵
    int s[10][10]; // 存储最优分割点的矩阵，假设最多支持10个矩阵

    // 初始化主对角线元素为0，因为单个矩阵不需要乘法
    for (int i = 1; i < n; i++) {
        m[i][i] = 0; // 单个矩阵的乘法次数为0
    }

    // l 表示连乘链的长度，从2到n逐渐增加
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1; // 计算右边界索引 j
            m[i][j] = INT_MAX; // 初始化为最大值，表示当前尚未计算出最优解

            // 寻找最优的划分点 k，将矩阵链划分为 A[i..k] 和 A[k+1..j]
            for (int k = i; k <= j - 1; k++) {
                // 计算当前划分的代价
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q; // 更新最小值
                    s[i][j] = k; // 记录最优划分点
                }
            }
        }
    }

    // 打印最小的乘法次数
    printf("\n最小的矩阵连乘次数为: %d\n", m[1][n - 1]);

    // 打印最优括号化顺序
    printf("最优的括号化顺序为: ");
    printOptimalParens(s, 1, n - 1);
    printf("\n");
}

// 辅助函数，用于打印最优的括号化顺序
void printOptimalParens(int s[][10], int i, int j) {
    if (i == j) {
        printf("A%d", i); // 只有一个矩阵，不需要括号
    } else {
        printf("(");
        printOptimalParens(s, i, s[i][j]); // 打印左部分
        printOptimalParens(s, s[i][j] + 1, j); // 打印右部分
        printf(")");
    }
}

// 主函数
int main() {
    int arr[] = {10, 20, 30, 40, 30}; // 矩阵链的维度数组
    int size = sizeof(arr) / sizeof(arr[0]); // 计算数组的大小

    // 调用函数计算最优的矩阵连乘顺序
    matrixChainOrder(arr, size);

    return 0;
}



