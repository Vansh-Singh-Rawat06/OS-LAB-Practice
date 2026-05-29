#include <stdio.h>

int main()
{
    int n, m;
    int alloc[10][10], request[10][10];
    int avail[10];
    int finish[10];
    int sequence[10];
    printf("1bf24cs330\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");
    for(int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Initialize finish[]
    for(int i = 0; i < n; i++)
    {
        int flag = 0;

        for(int j = 0; j < m; j++)
        {
            if(alloc[i][j] != 0)
            {
                flag = 1;
                break;
            }
        }

        if(flag)
            finish[i] = 0;
        else
            finish[i] = 1;
    }

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(int i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int j;

                for(j = 0; j < m; j++)
                {
                    if(request[i][j] > avail[j])
                        break;
                }

                if(j == m)
                {
                    for(int k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    finish[i] = 1;
                    sequence[count++] = i;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    int deadlock = 0;

    for(int i = 0; i < n; i++)
    {
        if(finish[i] == 0)
        {
            deadlock = 1;
            break;
        }
    }

    if(deadlock)
    {
        printf("\nDeadlock Detected.\nProcesses involved: ");

        for(int i = 0; i < n; i++)
        {
            if(finish[i] == 0)
                printf("P%d ", i);
        }
    }
    else
    {
        printf("\nNo Deadlock Detected.\n");
        printf("Execution Sequence: ");

        for(int i = 0; i < count; i++)
            printf("P%d ", sequence[i]);
    }

    printf("\n");

    return 0;
}
