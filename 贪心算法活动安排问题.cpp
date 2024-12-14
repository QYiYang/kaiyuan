#include <stdio.h>
#include <stdlib.h>

// ����ṹ������ʾ��Ŀ�ʼ�ͽ���ʱ��
typedef struct {
    int start;  // ��Ŀ�ʼʱ��
    int end;    // ��Ľ���ʱ��
} Activity;

// �ȽϺ��������ڰ���Ľ���ʱ���������
int compare(const void *a, const void *b) {
    Activity *activityA = (Activity *)a;
    Activity *activityB = (Activity *)b;
    return (activityA->end - activityB->end); // �����������ʱ��
}

// ̰���㷨ʵ�ֻѡ������
void activitySelection(Activity activities[], int n) {
    // �ȶԻ���ս���ʱ���������
    qsort(activities, n, sizeof(Activity), compare);

    printf("ѡ�еĻΪ: \n");

    // ѡ���һ�����Ϊ��ʼ
    int lastSelected = 0;  // ��¼��һ����ѡ�еĻ����
    printf("�: ��ʼʱ�� = %d, ����ʱ�� = %d\n", activities[lastSelected].start, activities[lastSelected].end);

    // ����ʣ��Ļ��ѡ�񲻳�ͻ�Ļ
    for (int i = 1; i < n; i++) {
        if (activities[i].start >= activities[lastSelected].end) {
            // ��ǰ��Ŀ�ʼʱ�䲻������һ����Ľ���ʱ��
            printf("�: ��ʼʱ�� = %d, ����ʱ�� = %d\n", activities[i].start, activities[i].end);
            lastSelected = i;  // ������һ����ѡ�еĻ
        }
    }
}

int main() {
    int t; // ���԰�������
    printf("��������԰�������: ");
    scanf("%d", &t); // ������԰�������

    while (t--) {
        int n; // �������
        printf("\n����������: ");
        scanf("%d", &n);

        Activity activities[n]; // ����洢�������

        // ����ÿ����Ŀ�ʼʱ��ͽ���ʱ��
        printf("������ÿ����Ŀ�ʼʱ��ͽ���ʱ��:\n");
        for (int i = 0; i < n; i++) {
            printf("� %d: ", i + 1);
            scanf("%d %d", &activities[i].start, &activities[i].end);
        }

        // ���ûѡ����
        activitySelection(activities, n);
    }

    return 0;
}

