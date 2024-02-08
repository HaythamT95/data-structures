#include <stdio.h> /*printf*/
#include <stdlib.h> /*srand, rand*/
#include <time.h> /*clock, time, CLOCKS_PER_SEC*/

#include "sorts.h"

#define ARRAY_SIZE 5000

static void generateRandomArray(int *array, size_t len);
static int compareIntegers(const void *a, const void *b);

static void RunSortingAlgorithms();
static void RunBubbleSort();
static void RunOptimizedBubbleSort();
static void RunSelectionSort();
static void RunInsertionSort();
static void RunQSort();
static void RunBinarySearchIterative();
static void RunBinarySearchRecursive();
static void RunMergeSort();
static void RunQuickSort();

int array[ARRAY_SIZE];

void printArrayToFile(int *array, size_t len, const char *filename) 
{
	size_t i = 0;
    FILE *file = fopen(filename, "w");

    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for ( i = 0; i < len; ++i) 
    {
        fprintf(file, "%d\n", array[i]);
    }

    fclose(file);
}

void readArrayFromFile(int *array, size_t len, const char *filename) 
{
	size_t i = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for ( i = 0; i < len; ++i) 
    {
        if (fscanf(file, "%d", &array[i]) != 1) 
        {
            fprintf(stderr, "Error reading from file\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}

int main() 
{
    srand((unsigned int)time(NULL));

    RunSortingAlgorithms();

    return 0;
}

void RunSortingAlgorithms() 
{
    generateRandomArray(array, ARRAY_SIZE);

    printf("Running Bubble Sort:\n");
    readArrayFromFile(array, ARRAY_SIZE, "random_array.txt");
    RunBubbleSort();

    printf("\nRunning Optimized Bubble Sort:\n");
    readArrayFromFile(array, ARRAY_SIZE, "random_array.txt");
    RunOptimizedBubbleSort();

    printf("\nRunning Selection Sort:\n");
    readArrayFromFile(array, ARRAY_SIZE, "random_array.txt");
    RunSelectionSort();

    printf("\nRunning Insertion Sort:\n");
    readArrayFromFile(array, ARRAY_SIZE, "random_array.txt");
    RunInsertionSort();

    printf("\nRunning QSort:\n");
    readArrayFromFile(array, ARRAY_SIZE, "random_array.txt");
    RunQSort();

   /* printf("\nRunning Binary Search Iterative:\n");
    RunBinarySearchIterative();

    printf("\nRunning Binary Search Recursive:\n");
    RunBinarySearchRecursive();*/

    printf("\nRunning MergeSort:\n");
    readArrayFromFile(array, ARRAY_SIZE, "random_array.txt");
    RunMergeSort();

    printf("\nRunning QuickSort:\n");
    readArrayFromFile(array, ARRAY_SIZE, "random_array.txt");
    RunQuickSort();
}

void RunQuickSort()
{
    clock_t start;
    clock_t end;
    double time;

    start = clock();
    QSort(array, ARRAY_SIZE, sizeof(int), compareIntegers);
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("My quicksort took %f seconds\n", time);
}

void RunMergeSort()
{
    clock_t start;
    clock_t end;
    double time;

    start = clock();
    MergeSort(array, ARRAY_SIZE);
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("My MergeSort took %f seconds\n", time);
}

void RunBinarySearchIterative()
{
    int array[10] = {1,2,3,4,5,6,7,8,9,10};
    int index = 0;

    index = BinarySearchIterative(array, 10, 2);
    printf("\nArray: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}\n");
    printf("\nindex of 2 is = %d\n", index);
    index = BinarySearchIterative(array, 10, 0);
    printf("\nindex of 0 is = %d\n", index);
}

void RunBinarySearchRecursive()
{
    int array[10] = {1,2,3,4,5,6,7,8,9,10}; 
    int index = 0;

    index = BinarySearchRecursive(array, 2, 0, 9);
    printf("\nArray: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}\n");
    printf("\nindex of 2 is = %d\n", index);
    index = BinarySearchRecursive(array, 0, 0, 9);
    printf("\nindex of 0 is = %d\n", index);
}

void RunQSort() 
{
    clock_t start;
    clock_t end;
    double time;

    start = clock();
    qsort(array, ARRAY_SIZE, sizeof(int), compareIntegers);
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("qsort took %f seconds\n", time);
}

void RunBubbleSort() 
{
    clock_t start;
    clock_t end;
    double time;

    start = clock();
    BubbleSort(array, ARRAY_SIZE);
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Bubble Sort took %f seconds\n", time);
}

void RunOptimizedBubbleSort() 
{
    clock_t start;
    clock_t end;
    double time;

    start = clock();
    OptimizedBubbleSort(array, ARRAY_SIZE);
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Bubble Sort took %f seconds\n", time);
}

void RunSelectionSort() 
{
    clock_t start;
    clock_t end;
    double time;

    start = clock();
    SelectionSort(array, ARRAY_SIZE);
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Selection Sort took %f seconds\n", time);
}

void RunInsertionSort() 
{
    clock_t start;
    clock_t end;
    double time;

    start = clock();
    InsertionSort(array, ARRAY_SIZE);
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Insertion Sort took %f seconds\n", time);
}

void generateRandomArray(int *array, size_t len) 
{
	size_t i = 0;

    for (i = 0; i < len; ++i) 
    {
        array[i] = rand() % 1000;  
    }
}

int compareIntegers(const void *a, const void *b) 
{
    return (*(int *)a - *(int *)b);
}