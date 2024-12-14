
#include <stdio.h>
#define MAX_ITEMS 100

int n;                 // ��Ʒ����
int W;                 // ��������
int weights[MAX_ITEMS]; // ��Ʒ��������
int values[MAX_ITEMS];  // ��Ʒ��ֵ����
int max_value = 0;      // �洢����ֵ

void knapsack(int index, int current_weight, int current_value) {
    if (index == n) { // �ݹ���ֹ�������ѿ���������Ʒ
        if (current_value > max_value) {
            max_value = current_value;
        }
        return;
    }

    // ��ѡ��ǰ��Ʒ
    knapsack(index + 1, current_weight, current_value);

    // ѡ��ǰ��Ʒ��ǰ������������������������
    if (current_weight + weights[index] <= W) {
        knapsack(index + 1, current_weight + weights[index], current_value + values[index]);
    }
}

int main() {
    int test_cases;
    printf("������԰�������: ");
    scanf("%d", &test_cases);

    while (test_cases--) {
        max_value = 0;
        printf("\n������Ʒ�����ͱ�������: ");
        scanf("%d %d", &n, &W);

        printf("������Ʒ�������ͼ�ֵ: \n");
        for (int i = 0; i < n; i++) 1{
            scanf("%d %d", &weights[i], &values[i]);
        }

        knapsack(0, 0, 0);

        printf("����������ֵΪ: %d\n", max_value);
    }

    return 0;
}

