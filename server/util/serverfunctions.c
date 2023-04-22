/**
 * @file serverfunctions.c
 * @brief Contains functions that serve a client
 *
 * This contains functions that provide functionality to a client,
 * including sorting an array of integers.
 *
 * @author Braden Byrnes
 * @bug no known bugs
 */

#include <stdio.h>
#include <stdlib.h>
#include "serverfunctions.h"

/**
 * @brief Swaps two integers
 *
 * This function takes two integers and swaps them.
 *
 * @param a The first integer
 * @param b The second integer
 * @return void
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Partitions an array of integers
 *
 * This function takes an array of integers, a low index, and a high index
 * and partitions the array around the high index.
 *
 * @param arr The array of integers
 * @param low The low index
 * @param high The high index
 * @return int The partition index
 */
int partition(int *arr, int low, int high)
{
    // pivot (Element to be placed at high position)
    int pivot = arr[high];
    // Index of smaller element
    int i = low - 1;

    // Iterate through the array until reaching the high pivot
    for (int j = low; j < high; j++)
    {
        // If current element is smaller than or equal to pivot
        if (arr[j] < pivot)
        {
            // increment index of smaller element
            i++;
            // swap arr[i] and arr[j]
            swap(&arr[i], &arr[j]);
        }
    }
    // swap arr[i + 1] and arr[high] (or pivot)
    swap(&arr[i + 1], &arr[high]);
    // return the partition index
    return i + 1;
}

/**
 * @brief Sorts an array of integers
 *
 * This function takes an array of integers, a low index, and a high index
 * and sorts the array using quick sort.
 *
 * @param arr The array of integers
 * @param low The low index
 * @param high The high index
 * @return void
 */
void quickSort(int *arr, int low, int high)
{
    // If the low index is less than the high index
    if (low < high)
    {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, high);
        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
