#include <stdio.h>
#include "util/serverfunctions.h"

int main(int argc, char *argv[])
{
    int arr[] = {11, 2, 2, 9, 1, 5, 3, 4, 7, 6, -1};
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
