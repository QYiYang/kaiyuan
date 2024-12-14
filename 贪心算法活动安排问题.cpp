#include <stdio.h>
#include <stdlib.h>

// 定义结构体来表示活动的开始和结束时间
typedef struct {
    int start;  // 活动的开始时间
    int end;    // 活动的结束时间
} Activity;

// 比较函数，用于按活动的结束时间进行排序
int compare(const void *a, const void *b) {
    Activity *activityA = (Activity *)a;
    Activity *activityB = (Activity *)b;
    return (activityA->end - activityB->end); // 升序排序结束时间
}

// 贪心算法实现活动选择问题
void activitySelection(Activity activities[], int n) {
    // 先对活动按照结束时间进行排序
    qsort(activities, n, sizeof(Activity), compare);

    printf("选中的活动为: \n");

    // 选择第一个活动作为开始
    int lastSelected = 0;  // 记录上一个被选中的活动索引
    printf("活动: 开始时间 = %d, 结束时间 = %d\n", activities[lastSelected].start, activities[lastSelected].end);

    // 遍历剩余的活动，选择不冲突的活动
    for (int i = 1; i < n; i++) {
        if (activities[i].start >= activities[lastSelected].end) {
            // 当前活动的开始时间不早于上一个活动的结束时间
            printf("活动: 开始时间 = %d, 结束时间 = %d\n", activities[i].start, activities[i].end);
            lastSelected = i;  // 更新上一个被选中的活动
        }
    }
}

int main() {
    int t; // 测试案例数量
    printf("请输入测试案例数量: ");
    scanf("%d", &t); // 输入测试案例数量

    while (t--) {
        int n; // 活动的数量
        printf("\n请输入活动数量: ");
        scanf("%d", &n);

        Activity activities[n]; // 定义存储活动的数组

        // 输入每个活动的开始时间和结束时间
        printf("请输入每个活动的开始时间和结束时间:\n");
        for (int i = 0; i < n; i++) {
            printf("活动 %d: ", i + 1);
            scanf("%d %d", &activities[i].start, &activities[i].end);
        }

        // 调用活动选择函数
        activitySelection(activities, n);
    }

    return 0;
}

