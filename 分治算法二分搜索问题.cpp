#include <stdio.h>

// �������������ĵݹ�ʵ��
int binary_search(int arr[], int low, int high, int target) {
    if (low > high) {
        return -1; // �����λ�������ڸ�λ������˵��û���ҵ�Ŀ��ֵ������ -1
    }
    int mid = (low + high) / 2; // �����м�λ��
    if (arr[mid] == target) {
        return mid; // ����м�Ԫ�ؾ���Ŀ��ֵ�������м�λ�õ�����
    } else if (arr[mid] > target) {
        return binary_search(arr, low, mid - 1, target); // ���Ŀ��ֵС���м�ֵ���ݹ�����벿�ֲ���
    } else {
        return binary_search(arr, mid + 1, high, target); // ���Ŀ��ֵ�����м�ֵ���ݹ����Ұ벿�ֲ���
    }
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13}; // ��ʼ��һ����������
    int target = 7; // Ҫ���ҵ�Ŀ��ֵ
    int n = sizeof(arr) / sizeof(arr[0]); // ��������ĳ���
    int result = binary_search(arr, 0, n - 1, target); // ���ö�����������
    if (result != -1) {
        printf("Ŀ�� %d ��������: %d\n", target, result); // ����ҵ�����ӡĿ��ֵ������
    } else {
        printf("Ŀ�� %d δ�ҵ�\n", target); // ���δ�ҵ�����ӡδ�ҵ�����Ϣ
    }
    return 0; 
}

