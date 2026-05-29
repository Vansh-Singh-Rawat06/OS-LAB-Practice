#include <stdio.h>

#define MAX 50


int isPresent(int frames[], int num_frames, int page)
{
    for (int i = 0; i < num_frames; i++)
    {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}


void printFrames(int frames[], int num_frames)
{
    printf("[");
    for (int i = 0; i < num_frames; i++)
    {
        if (frames[i] != -1)
            printf("%d", frames[i]);
        else
            printf(" ");

        if (i != num_frames - 1)
            printf(" ");
    }
    printf("]\n");
}


void FIFO(int pages[], int n, int num_frames)
{
    int frames[MAX];
    int page_faults = 0;
    int next = 0;

    for (int i = 0; i < num_frames; i++)
        frames[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];

        if (!isPresent(frames, num_frames, page))
        {
            frames[next] = page;
            next = (next + 1) % num_frames;
            page_faults++;
        }

        printf("Page %d -> ", page);
        printFrames(frames, num_frames);
    }

    printf("\nTotal Page Faults (FIFO): %d\n", page_faults);
}


void LRU(int pages[], int n, int num_frames)
{
    int frames[MAX];
    int last_used[MAX];
    int page_faults = 0;

    for (int i = 0; i < num_frames; i++)
    {
        frames[i] = -1;
        last_used[i] = -1;
    }

    printf("\n--- LRU Page Replacement ---\n\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;

        
        for (int j = 0; j < num_frames; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                last_used[j] = i;
                break;
            }
        }

        
        if (!found)
        {
            int pos = -1;

            
            for (int j = 0; j < num_frames; j++)
            {
                if (frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            
            if (pos == -1)
            {
                int min = last_used[0];
                pos = 0;

                for (int j = 1; j < num_frames; j++)
                {
                    if (last_used[j] < min)
                    {
                        min = last_used[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = page;
            last_used[pos] = i;
            page_faults++;
        }

        printf("Page %d -> ", page);
        printFrames(frames, num_frames);
    }

    printf("\nTotal Page Faults (LRU): %d\n", page_faults);
}


void Optimal(int pages[], int n, int num_frames)
{
    int frames[MAX];
    int page_faults = 0;

    for (int i = 0; i < num_frames; i++)
        frames[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];

        if (!isPresent(frames, num_frames, page))
        {
            int pos = -1;

            
            for (int j = 0; j < num_frames; j++)
            {
                if (frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            
            if (pos == -1)
            {
                int farthest = -1;

                for (int j = 0; j < num_frames; j++)
                {
                    int k;
                    for (k = i + 1; k < n; k++)
                    {
                        if (frames[j] == pages[k])
                            break;
                    }

                    
                    if (k == n)
                    {
                        pos = j;
                        break;
                    }

                    
                    if (k > farthest)
                    {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            frames[pos] = page;
            page_faults++;
        }

        printf("Page %d -> ", page);
        printFrames(frames, num_frames);
    }

    printf("\nTotal Page Faults (Optimal): %d\n", page_faults);
}


int main()
{
    int n, num_frames;
    int pages[MAX];
    printf("1BF24CS330\n");

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    FIFO(pages, n, num_frames);
    LRU(pages, n, num_frames);
    Optimal(pages, n, num_frames);

    return 0;
}
