#include <stdio.h>

int main()
{
    int n,i,j;
    int pid[20],at[20],bt[20],type[20];
    int ct[20],tat[20],wt[20];
    
    float avg_tat=0, avg_wt=0;
    int current_time = 0;
    printf("usn:1bf24cs330\n");

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("\nProcess %d ID: ",i+1);
        scanf("%d",&pid[i]);

        printf("Arrival Time: ");
        scanf("%d",&at[i]);

        printf("Burst Time: ");
        scanf("%d",&bt[i]);

        printf("Type (1-System 2-User): ");
        scanf("%d",&type[i]);
    }

    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(at[i] > at[j])
            {
                int temp;

                temp=at[i]; at[i]=at[j]; at[j]=temp;
                temp=bt[i]; bt[i]=bt[j]; bt[j]=temp;
                temp=pid[i]; pid[i]=pid[j]; pid[j]=temp;
                temp=type[i]; type[i]=type[j]; type[j]=temp;
            }
        }
    }

    for(i=0;i<n;i++)
    {
        if(type[i]==1)
        {
            if(current_time < at[i])
                current_time = at[i];

            ct[i] = current_time + bt[i];
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];

            current_time = ct[i];
        }
    }

    
    for(i=0;i<n;i++)
    {
        if(type[i]==2)
        {
            if(current_time < at[i])
                current_time = at[i];

            ct[i] = current_time + bt[i];
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];

            current_time = ct[i];
        }
    }

    printf("\nPID\tAT\tBT\tType\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i],at[i],bt[i],type[i],ct[i],tat[i],wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);

    return 0;
}
