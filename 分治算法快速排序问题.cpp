#include <stdio.h>

// ��������Ԫ�ص�ֵ
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ����������ѡ��һ����׼Ԫ�أ�����������з���
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // ѡ�����һ��Ԫ����Ϊ��׼
    int i = low - 1; // ��ʼ����СԪ�ص�����

    // �������鲢��С�ڻ�׼��Ԫ�طŵ���������
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) { // �����ǰԪ��С�ڻ�׼
            i++;
            swap(&arr[i], &arr[j]); // ����λ��
        }
    }
    swap(&arr[i + 1], &arr[high]); // ����׼Ԫ�طŵ���ȷ��λ��
    return i + 1; // ���ػ�׼Ԫ�ص�λ��
}

// �������������ݹ�ض������������
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // ��������з�������ȡ��׼��λ��
        quick_sort(arr, low, pi - 1);  // �Ի�׼��ߵ�������ݹ�����
        quick_sort(arr, pi + 1, high); // �Ի�׼�ұߵ�������ݹ�����
    }
}

int main() {
    int n;

    while (1) {
        printf("����������Ĵ�С������ 0 �����Խ������򣩣�");
        scanf("%d", &n);

        if (n <= 0) {
            break; // ����û����� 0 ���������˳�ѭ��
        }

        int arr[n]; // �����û�����Ĵ�С��������

        printf("�����������Ԫ�أ��� %d ������\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]); // ��ȡ�û����������Ԫ��
        }

        // ���ÿ���������
        quick_sort(arr, 0, n - 1);

        // �������������
        printf("����������: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    printf("���������\n");
    return 0; // ���� 0 ��ʾ������������
}

