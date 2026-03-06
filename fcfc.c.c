#include <stdio.h>

int main() {
    int n, i, j;
    int pid[20], at[20], bt[20];
    int ct[20], tat[20], wt[20];
    int temp;
    int current_time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(at[i] > at[j]) {

                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }
    for(i = 0; i < n; i++) {
        if(current_time < at[i]) {
            current_time = at[i];
        }
        ct[i] = current_time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        current_time = ct[i];
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    int avgtat = 0, avgwt = 0;
    for(i = 0; i < n; i++){
        avgtat += tat[i];
        avgwt += wt[i];
    }
    double AVGTAT = (double)avgtat / n;
    double AVGWT = (double)avgwt / n;
    printf("\nAverage Turnaround Time : %.2f", AVGTAT);
    printf("\nAverage Waiting Time : %.2f", AVGWT);
    return 0;
}
