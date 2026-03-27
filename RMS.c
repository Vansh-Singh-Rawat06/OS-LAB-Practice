#include <stdio.h>
#include <math.h>
#define MAX 10


int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}


int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}


void sort(int n, int burst[], int period[], int pid[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (period[i] > period[j]) {
                int t;
                t = period[i]; period[i] = period[j]; period[j] = t;
                t = burst[i]; burst[i] = burst[j]; burst[j] = t;
                t = pid[i]; pid[i] = pid[j]; pid[j] = t;
            }
        }
    }
}

int main() {
    int n, burst[MAX], period[MAX], pid[MAX];
printf("usn:1BF24CS330\n");
    printf("Enter the number of processes:");
    scanf("%d", &n);

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst[i]);
        pid[i] = i + 1;
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &period[i]);
    }


    sort(n, burst, period, pid);


    int hyper = period[0];
    for (int i = 1; i < n; i++) {
        hyper = lcm(hyper, period[i]);
    }

    printf("LCM=%d\n\n", hyper);


    printf("Rate Monotone Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", pid[i], burst[i], period[i]);
    }


    float U = 0;
    for (int i = 0; i < n; i++) {
        U += (float)burst[i] / period[i];
    }


    float bound = n * (pow(2, (float)1/n) - 1);

    printf("\n%f <= %f => %s\n", U, bound, (U <= bound) ? "true" : "false");

    if (U <= bound)
        printf("Scheduling occurs for %d ms\n\n", hyper);
    else
        printf("Scheduling may not be guaranteed, still simulating...\n\n");


    int remaining[MAX] = {0};

    for (int t = 0; t < hyper; t++) {


        for (int i = 0; i < n; i++) {
            if (t % period[i] == 0) {
                remaining[i] = burst[i];
            }
        }


        int sel = -1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                sel = i;
                break;
            }
        }


        static int last = -2;
        if (sel != last) {
            if (sel == -1)
                printf("%dms onwards: CPU is idle\n", t);
            else
                printf("%dms onwards: Process %d running\n", t, pid[sel]);
            last = sel;
        }


        if (sel != -1) {
            remaining[sel]--;
        }
    }

    return 0;
}
