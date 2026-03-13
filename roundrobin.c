#include <stdio.h>

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int pid[n], at[n], bt[n], rt[n];
    int ct[n], tat[n], wt[n], response[n];
    int visited[n];

    float total_wt = 0, total_tat = 0;

    printf("Enter arrival times:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &at[i]);

    printf("Enter burst times:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        pid[i] = i + 1;
        visited[i] = 0;
        response[i] = -1;
    }

    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;

    while(completed < n) {

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if(front == rear) {
            time++;
            continue;
        }

        int p = queue[front++];

        if(response[p] == -1)
            response[p] = time - at[p];

        if(rt[p] > tq) {
            time += tq;
            rt[p] -= tq;

            for(int i = 0; i < n; i++) {
                if(at[i] <= time && visited[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            queue[rear++] = p;
        }
        else {
            time += rt[p];
            ct[p] = time;

            tat[p] = ct[p] - at[p];
            wt[p] = tat[p] - bt[p];

            total_wt += wt[p];
            total_tat += tat[p];

            rt[p] = 0;
            completed++;
        }
    }

    printf("\nRRS Scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i], at[i], bt[i], ct[i], tat[i], wt[i], response[i]);
    }

    printf("\nAverage turnaround time = %.2f", total_tat/n);
    printf("\nAverage waiting time = %.2f\n", total_wt/n);

    return 0;
}
