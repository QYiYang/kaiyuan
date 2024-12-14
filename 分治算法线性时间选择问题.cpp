#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int left, int right);
int quickSelect(int arr[], int left, int right, int k);
void swap(int *a, int *b);

// ��������֧�ֶ��������������
int main() {
    int t;
    printf("������������ݵ�����: ");
    scanf("%d", &t);
    while (t--) {
        int n, k;
        printf("\n�����������Ԫ�ظ���: ");
        scanf("%d", &n);
        int *arr = (int *)malloc(n * sizeof(int));
        printf("����������Ԫ��: ");
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        printf("������ k ��ֵ(Ҫ�ҵ� k С��Ԫ��): ");
        scanf("%d", &k);

        int result = quickSelect(arr, 0, n - 1, k);
        printf("�����е� %d С��Ԫ����: %d\n", k, result);
        free(arr);
    }
    return 0;
}

// ����ѡ���㷨��ʵ��
int quickSelect(int arr[], int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }

    // ʹ�û��ֺ���ѡ��һ����Ԫλ��
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

// ��������л���
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

// ������������ֵ
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
