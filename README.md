# Data Structures and Sorting Algorithms
This repository contains a collection of fundamental data structures and sorting algorithms implemented in C programming language. Each source file corresponds to a specific data structure or algorithm, providing clear implementation.

## Data Structures
### Trie
A trie (pronounced "try") is a tree-like data structure that stores a dynamic set of strings where each node represents a single character of the string.

### Binary Search Tree (BST)
A binary search tree is a hierarchical data structure that allows for fast lookup, insertion, and deletion of items.

### Circular Buffer (CBuffer)
A circular buffer, also known as a ring buffer or cyclic buffer, is a fixed-size data structure that efficiently manages a sequence of items in a circular manner.

### Singly Linked List
A singly linked list is a linear data structure consisting of a sequence of elements where each element points to the next element in the sequence.

### Doubly Linked List
A doubly linked list is a linear data structure similar to a singly linked list, but each node contains a reference to both the next and previous nodes in the sequence.

### Priority Queue
A priority queue is an abstract data type that operates similar to a regular queue or stack, but where each element has an associated priority and items are dequeued based on their priority.

### Hash
A hash table is a data structure that implements an associative array abstract data type, a structure that can map keys to values. It uses a hash function to compute an index into an array of buckets or slots, from which the desired value can be found.

### Heap
A heap is a specialized tree-based data structure that satisfies the heap property: if A is a parent node of B, then the key of node A is ordered with respect to the key of node B. It allows for efficient retrieval and removal of the maximum (or minimum) element.

### Vector
A vector, also known as a dynamic array, is a resizable array data structure that allows for efficient insertion, deletion, and access to elements. It dynamically allocates memory to accommodate for a varying number of elements.

### Queue
A queue is a linear data structure that follows the First In, First Out (FIFO) principle, where elements are inserted at the rear and removed from the front. It supports operations such as enqueue (inserting an element) and dequeue (removing an element).

### Stack
A stack is a linear data structure that follows the Last In, First Out (LIFO) principle, where elements are inserted and removed from the same end, called the top. It supports operations such as push (adding an element) and pop (removing an element).

### Sorted List
A sorted list is a data structure that maintains its elements in sorted order. It typically supports operations such as insertion, deletion, and search, while ensuring that elements remain sorted according to a specified order.

### AVL Tree
An AVL tree is a self-balancing binary search tree where the heights of the two child subtrees of any node differ by at most one.

## Algorithms
### Bubble Sort
Bubble sort is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order. The pass through the list is repeated until the list is sorted.

### Insertion Sort
Insertion sort is a simple sorting algorithm that builds the final sorted list one item at a time by repeatedly picking the next element and inserting it into the correct position. It iterates through the list, shifting elements as necessary to accommodate each new item.

### Selection Sort
Selection sort is a simple sorting algorithm that divides the input list into two parts: a sorted sublist and an unsorted sublist. It repeatedly selects the smallest (or largest) element from the unsorted sublist and moves it to the end of the sorted sublist.

### Merge Sort
Merge sort is a divide-and-conquer algorithm that divides the input list into smaller sublists, sorts each sublist recursively, and then merges the sorted sublists to produce the final sorted list. It is efficient for sorting large lists.

### Quicksort
Quicksort is another divide-and-conquer algorithm that picks a "pivot" element from the list and partitions the other elements into two sublists according to whether they are less than or greater than the pivot. It then recursively sorts the sublists.

### Count Sort
Counting sort is an integer sorting algorithm that operates by counting the number of occurrences of each unique element in the input list and using arithmetic to determine the position of each element in the output sequence.

### Radix Sort
Radix sort is a non-comparative sorting algorithm that sorts elements by processing individual digits or groups of digits representing the significant places of the values. It can be used with integer or string keys.

### Binary Search
Binary search is a search algorithm that finds the position of a target value within a sorted array. It compares the target value to the middle element of the array and repeatedly halves the search space until the target value is found or the search space is empty.
