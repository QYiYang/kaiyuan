#include <stdio.h>
#include <string.h>

#define MAX 100

// ʹ�ö�̬�滮ʵ�� LCS
void lcs(char X[], char Y[]) {
    int m = strlen(X); // �����ַ��� X �ĳ���
    int n = strlen(Y); // �����ַ��� Y �ĳ���
    int dp[MAX][MAX]; // ���ڴ洢 LCS ���ȵĶ�ά����

    // ��ʼ�� dp ����ı߽�
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0; // �����һ�ַ���Ϊ�գ��� LCS ����Ϊ 0
            }
        }
    }

    // ��� dp ���飬���� LCS ����
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                // ����ַ�ƥ�䣬������Ϸ��̳в��� 1
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                // ����ַ���ƥ�䣬��ȡ�Ϸ������Ľϴ�ֵ
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    // ��ӡ LCS �ĳ���
    printf("����������еĳ���Ϊ: %d\n", dp[m][n]);

    // �� dp �����л��ݣ����� LCS
    int index = dp[m][n]; // LCS �ĳ���
    char lcs[index + 1]; // �洢 LCS �ַ���
    lcs[index] = '\0'; // ��ĩβ����ַ���������

    int i = m, j = n;
    while (i > 0 && j > 0) {
        // �����ǰ�ַ���ͬ������ LCS ��һ����
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1]; // ���ַ���ӵ� LCS ��
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            // ����Ϸ���ֵ��������ֵ���������ƶ�
            i--;
        } else {
            // �������ֵ���ڻ�����Ϸ���ֵ���������ƶ�
            j--;
        }
    }

    // ��ӡ LCS
    printf("�����������Ϊ: %s\n", lcs);
}

// ������
int main() {
    char X[MAX], Y[MAX];

    // ���������ַ���
    printf("�������һ���ַ���: ");
    scanf("%s", X);
    printf("������ڶ����ַ���: ");
    scanf("%s", Y);

    // ���� LCS ����
    lcs(X, Y);

    return 0;
}

