#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t fork_sem[N];

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        printf("Philosopher %d is hungry\n", id);

        
        sem_wait(&fork_sem[id]);
        printf("Philosopher %d picked up left fork %d\n", id, id);

        
        sem_wait(&fork_sem[(id + 1) % N]);
        printf("Philosopher %d picked up right fork %d\n",
               id, (id + 1) % N);

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        
        sem_post(&fork_sem[(id + 1) % N]);

        
        sem_post(&fork_sem[id]);

        printf("Philosopher %d released both forks\n", id);
    }
}

int main()
{
    pthread_t phil[N];
    int id[N];
    printf("1bf24cs330\n");
    for (int i = 0; i < N; i++)
        sem_init(&fork_sem[i], 0, 1);

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(phil[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&fork_sem[i]);

    return 0;
}
