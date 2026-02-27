#include <stdio.h>

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int found = 0;

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i] == arr[j]) {
                found = 1;
                break;
            }
        }
        if(found) break;
    }

    if(found)
        printf("Duplicates found.\n");
    else
        printf("No duplicates.\n");

    return 0;
}
