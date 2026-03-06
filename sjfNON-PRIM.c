#include <stdio.h>

int main() {
    int n, i;
    int at[20], bt[20], ct[20], tat[20], wt[20];
    int finished[20] = {0};
    int current_time = 0, completed = 0;
    float avg_tat = 0, avg_wt = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival times:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &at[i]);
    printf("Enter burst times:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &bt[i]);
    while(completed < n) {
        int min_bt = 9999;
        int index = -1;
        for(i = 0; i < n; i++) {
            if(at[i] <= current_time && finished[i] == 0) {
                if(bt[i] < min_bt) {
                    min_bt = bt[i];
                    index = i;
                }
            }
        }
        if(index == -1) {
            current_time++;
        } else {
            ct[index] = current_time + bt[index];
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];

            current_time = ct[index];
            finished[index] = 1;
            completed++;
        }
    }
    printf("\nSJF scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    avg_tat = avg_tat / n;
    avg_wt = avg_wt / n;
    printf("\nAverage turnaround time: %f ms\n", avg_tat);
    printf("Average waiting time: %f ms\n", avg_wt);
    return 0;
}
