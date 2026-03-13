#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], pr[n];
    int ct[n], tat[n], wt[n];
    int completed[n];

    float total_wt = 0, total_tat = 0;

    for(int i = 0; i < n; i++)
        completed[i] = 0;

    // Input
    for(int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d\n", i+1);

        printf("Process ID: ");
        scanf("%d", &pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority: ");
        scanf("%d", &pr[i]);
    }

    int current_time = 0;
    int completed_count = 0;

    while(completed_count < n) {

        int highest_priority = 9999;
        int selected_process = -1;

        for(int i = 0; i < n; i++) {

            if(at[i] <= current_time && completed[i] == 0) {

                if(pr[i] < highest_priority) {
                    highest_priority = pr[i];
                    selected_process = i;
                }
            }
        }

        if(selected_process == -1) {
            current_time++;
        }
        else {

            int start_time = current_time;

            ct[selected_process] = start_time + bt[selected_process];

            tat[selected_process] =
                ct[selected_process] - at[selected_process];

            wt[selected_process] =
                tat[selected_process] - bt[selected_process];

            current_time = ct[selected_process];

            completed[selected_process] = 1;
            completed_count++;
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tWT\tTAT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               pid[i], at[i], bt[i], pr[i], wt[i], tat[i]);

        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
