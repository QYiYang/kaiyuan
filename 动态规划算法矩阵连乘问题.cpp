#include <stdio.h>
#include <limits.h>

// �������������ڴ�ӡ���ŵ����Ż�˳��
void printOptimalParens(int s[][10], int i, int j);

// �������˷��Ķ�̬�滮ʵ��
void matrixChainOrder(int p[], int n) {
    int m[10][10]; // �洢��С�˷������ľ��󣬼������֧��10������
    int s[10][10]; // �洢���ŷָ��ľ��󣬼������֧��10������

    // ��ʼ�����Խ���Ԫ��Ϊ0����Ϊ����������Ҫ�˷�
    for (int i = 1; i < n; i++) {
        m[i][i] = 0; // ��������ĳ˷�����Ϊ0
    }

    // l ��ʾ�������ĳ��ȣ���2��n������
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1; // �����ұ߽����� j
            m[i][j] = INT_MAX; // ��ʼ��Ϊ���ֵ����ʾ��ǰ��δ��������Ž�

            // Ѱ�����ŵĻ��ֵ� k��������������Ϊ A[i..k] �� A[k+1..j]
            for (int k = i; k <= j - 1; k++) {
                // ���㵱ǰ���ֵĴ���
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q; // ������Сֵ
                    s[i][j] = k; // ��¼���Ż��ֵ�
                }
            }
        }
    }

    // ��ӡ��С�ĳ˷�����
    printf("\n��С�ľ������˴���Ϊ: %d\n", m[1][n - 1]);

    // ��ӡ�������Ż�˳��
    printf("���ŵ����Ż�˳��Ϊ: ");
    printOptimalParens(s, 1, n - 1);
    printf("\n");
}

// �������������ڴ�ӡ���ŵ����Ż�˳��
void printOptimalParens(int s[][10], int i, int j) {
    if (i == j) {
        printf("A%d", i); // ֻ��һ�����󣬲���Ҫ����
    } else {
        printf("(");
        printOptimalParens(s, i, s[i][j]); // ��ӡ�󲿷�
        printOptimalParens(s, s[i][j] + 1, j); // ��ӡ�Ҳ���
        printf(")");
    }
}

// ������
int main() {
    int arr[] = {10, 20, 30, 40, 30}; // ��������ά������
    int size = sizeof(arr) / sizeof(arr[0]); // ��������Ĵ�С

    // ���ú����������ŵľ�������˳��
    matrixChainOrder(arr, size);

    return 0;
}



