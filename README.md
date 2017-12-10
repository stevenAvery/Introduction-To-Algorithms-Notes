---
title: Introduction to Algorithms
author: Steven Avery
---

<!--- ---------------------------------------------------------------------- -->
## Part I: Foundations
### Ch 1: The Roles of Algorithms in Computing
- **Algorithm**: specific computational procedure to take some set of values as input and produce some set of values as output.
	- An algorithm is **correct** if, for every input instance, it halts with the correct output.

### Ch 2: Getting Started
- Psuedocode in this book pass parameters to procedures by **value**.

#### 2.1 Insertion Sort (p 16)
- **Complexity**: *O(n<sup>2</sup>)* **Example In**: *src/sorting.cpp: insertionSort*
- Sorts the input numbers in place.
- Similar to how most people order playing cards.
- Start with sorted left side of hand empty (left of key).
- Compare the next card with each other sorted card from right to left to find final position.

- **Loop Invariant**: at each iteration the subarray A[0..j] consists of the elements originally in A[0..j], but in sorted order.

#### 2.2 Analyzing Algorithms (p 23)
- **Analyzing** an algorithm means predicting the resources the algorithm requires.
- Assumes **RAM model**, which contains instructions commonly found in real computers:
	- **Arithmetic**: add, subtract, multiple, divide, remainder, floor, ceiling, etc.
	- **Data Movement**: load, store, copy.
	- **Control**: conditional and unconditional branch, subroutine call and return.

#### 2.3 Designing Algorithms (p 29)
- **Merge Sort**: (p 30)
	- **Complexity**: *O(n lg(n))* **Example In**: *src/sorting.cpp: mergeSort*
	- **Divide**: Divide the n-element sequence to be sorted into two subsequences of n/2 elements each.
	- **Conquer**: Sort the two subsequences to produce a sorted answer.
	- **Combine**: Merge the two sorted subsequences to produce the sorted answer.
	- The recursion bottoms out when the subsequence length is one, since a list of one will always be sorted.

	- In the recursive section we break the array into two subarrays (complexity *O(lg(n))*).
	- In `merge` we combine the two sorted lists by comparing the top element in each list and adding the lower one next (complexity *O(n)*).
	- This makes the total complexity *O(n lg(n))*.

- **Bubble Sort**: (p 40)
	- **Complexity**: *O(n<sup>2</sup>)* **Example In**: *src/sorting.cpp: bubbleSort*

### Ch 3: Growth Functions
- **Asymptotic Notion**: Usually refers to run time of an algorithm (function), but can refer to the amount of space they use.
	- **ϴ notation**: bounds a function to within a constant factor.
	- **O notation**: gives an upper bound for a function to within a constant factor.
	- **Ω notation**: gives an lower bound for a function to within a constant factor.

### Ch 4: Divide-and-Conquer
- **Divide**: the problem into a number of subproblems that are smaller instances of the same problem.
- **Conquer**: the subproblems by solving them recursively.
- **Combine**: the solutions to the subproblems into the solution for the original problem.

- Reach the **base case** when the recursion bottoms out.
- Otherwise **recursive case**.

#### 4.1 Maximum-Subarray Problem (p 68)
- If you have an array of positive and negative numbers, what is the subarray that has the highest value?
- **Brute-Force Maximum-Subarray**:
	- **Complexity**: *O(n<sup>2</sup>)* **Example In**: *src/maximumSubarray*

- *TODO: skipped p71 - 146.*

### Ch 5: Probabilistic Analysis and Randomized Algorithms

<!--- ---------------------------------------------------------------------- -->
## Part II: Sorting and Order Statistics

| Algorithm      | Worst-Case Running Time | Average-Case/ Expected Running Time |
| -------------- | ----------------------- | ----------------------------------- |
| Insertion Sort | ϴ(n<sup>2</sup>)        | ϴ(n<sup>2</sup>)                    |
| Merge Sort     | ϴ(n lg(n))              | ϴ(n lg(n))                          |
| Heapsort       | O(n lg(n))              | -                                   |
| Quicksort      | ϴ(n<sup>2</sup>)        | ϴ(n lg(n))                          |
| Counting Sort  | ϴ(k+n)                  | ϴ(k+n)                              |
| Radix Sort     | ϴ(d(n+k))               | ϴ(d(n+k))                           |
| Bucket Sort    | ϴ(n<sup>2</sup>)        | ϴ(n)     *(average case)*           |


### Ch 6: Heapsort
#### 6.1 Heaps (p 151)
- **Insertion or Extraction Complexity**: *O(lg(n))*
- **Find Max Value Complexity**: *O(1)*
- **Sort Complexity**: *O(n lg(n))* **Example In**: *src/sorting.cpp: heapSort*

- A **binary heap** is a nearly complete binary tree.
- **Max Heap**: each parent is greater than or equal to both children.
- **Min Heap**: each parent is lesser  than or equal to both children.
- This allows us to easily find the max in max heap or min in min heap.

- **Algorithm**:
	- Uses `maxHeapify` which assumes left and right children are already max heaps, but A[i] might be smaller, allowing A[i] to "float down" to form max heap
	- First, uses `buildMaxHeap` to make the given array into a valid max heap.
		- This runs `maxHeapify` on all heaps with more than one element (since one element will always be a valid heap).
	- Then, takes off the next largest element (A[0]), and creates another valid heap with `maxHeapify`.

#### 6.5 Priority Queues (p 162)
- *TODO: skipped p162 - 168.*

### Ch 7: Quicksort
- **Worst-Case Running Time**: *O(n<sup>2</sup>)*
- **Expectd Running Time**: *O(n lg(n))* **Example In**: *src/sorting.cpp: heapSort*

- **Algorithm**:
	- Pick a pivot (in this case the last element).
	- Have a moving wall, such that every element left of the wall is < the pivot, and every element right of the wall is > the pivot.
	- Swap the pivot to the location of the wall.
	- repeat on two sub arrays (left of wall and right of wall).
	- At the end, every element will have all larger elements to the right, and all smaller elements to the left, making it sorted.

- The performance of quicksort depends on whether the partitioning is balanced.
	- If the partitioning is balanced the algorithm runs as fast as merge sort: O(n lg(n)).
	- If the partitioning is not balanced the algorithm runs as slow as insertion sort: O(n<sup>2</sup>).

#### A Randomized Version of Quicksort
- Instead of always using A[r] as the pivot, we swap a random element with A[r] before partitioning.

### Ch 8: Sorting in Linear Time

### Ch 9: Medians and Order Statistics

<!--- ---------------------------------------------------------------------- -->
## Part III: Data Structures
### Ch 10: Elementary Data Structures
#### Stacks and Queues


### Ch 11: Hash Tables

### Ch 12: Binary Search Trees

### Ch 13: Red-Black Trees

### Ch 14: Augmenting Data Structures

<!--- ---------------------------------------------------------------------- -->
## Part IV: Advanced Design and Analysis Techniques

<!--- ---------------------------------------------------------------------- -->
## Part V: Advanced Data Structures

<!--- ---------------------------------------------------------------------- -->
## Part VI: Graph Algorithms

<!--- ---------------------------------------------------------------------- -->
## Part VII: Selected Topics

<!--- ---------------------------------------------------------------------- -->
## Part VIII: Mathematical Background
