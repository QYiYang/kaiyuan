#include <stdio.h>
#include <string.h>

#define MAX 100

// 使用动态规划实现 LCS
void lcs(char X[], char Y[]) {
    int m = strlen(X); // 计算字符串 X 的长度
    int n = strlen(Y); // 计算字符串 Y 的长度
    int dp[MAX][MAX]; // 用于存储 LCS 长度的二维数组

    // 初始化 dp 数组的边界
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0; // 如果任一字符串为空，则 LCS 长度为 0
            }
        }
    }

    // 填充 dp 数组，计算 LCS 长度
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                // 如果字符匹配，则从左上方继承并加 1
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                // 如果字符不匹配，则取上方或左侧的较大值
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    // 打印 LCS 的长度
    printf("最长公共子序列的长度为: %d\n", dp[m][n]);

    // 从 dp 数组中回溯，构造 LCS
    int index = dp[m][n]; // LCS 的长度
    char lcs[index + 1]; // 存储 LCS 字符串
    lcs[index] = '\0'; // 在末尾添加字符串结束符

    int i = m, j = n;
    while (i > 0 && j > 0) {
        // 如果当前字符相同，则是 LCS 的一部分
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1]; // 将字符添加到 LCS 中
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            // 如果上方的值大于左侧的值，则向上移动
            i--;
        } else {
            // 如果左侧的值大于或等于上方的值，则向左移动
            j--;
        }
    }

    // 打印 LCS
    printf("最长公共子序列为: %s\n", lcs);
}

// 主函数
int main() {
    char X[MAX], Y[MAX];

    // 输入两个字符串
    printf("请输入第一个字符串: ");
    scanf("%s", X);
    printf("请输入第二个字符串: ");
    scanf("%s", Y);

    // 调用 LCS 函数
    lcs(X, Y);

    return 0;
}

