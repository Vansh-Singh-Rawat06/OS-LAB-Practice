#include <stdio.h>

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

int hyperperiod(int p[], int n) {
    int hp = p[0];
    for (int i = 1; i < n; i++)
        hp = lcm(hp, p[i]);
    return hp;
}

typedef struct {
    int id;
    int Ci;
    int Pi;
    int Di;
    int remaining;
    int abs_deadline;
} Task;

int main() {
    int n;
    Task t[MAX];
    int periods[MAX];
    printf("usn:1BF24CS330\n");

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        t[i].id = i + 1;

        printf("Enter computation time (C%d): ", i + 1);
        scanf("%d", &t[i].Ci);

        printf("Enter period (P%d): ", i + 1);
        scanf("%d", &t[i].Pi);

        printf("Enter deadline (D%d): ", i + 1);
        scanf("%d", &t[i].Di);

        t[i].remaining = 0;
        t[i].abs_deadline = t[i].Di;

        periods[i] = t[i].Pi;
    }

    int hp = hyperperiod(periods, n);

    printf("\nPID   Burst   Deadline   Period\n");
    for (int i = 0; i < n; i++) {
        printf("%d     %d        %d         %d\n",
               t[i].id, t[i].Ci, t[i].Di, t[i].Pi);
    }

    printf("\nScheduling occurs for %d ms\n\n", hp);

    for (int time = 0; time < hp; time++) {

        for (int i = 0; i < n; i++) {
            if (time % t[i].Pi == 0) {
                t[i].remaining = t[i].Ci;
                t[i].abs_deadline = time + t[i].Di;
            }
        }

        int selected = -1;
        int earliest_deadline = 100000;

        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0) {
                if (t[i].abs_deadline < earliest_deadline) {
                    earliest_deadline = t[i].abs_deadline;
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            printf("%dms : CPU is idle.\n", time);
        } else {
            printf("%dms : Task %d is running.\n", time, t[selected].id);
            t[selected].remaining--;
        }
    }

    return 0;
}
