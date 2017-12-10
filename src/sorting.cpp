/**
 * sorting algorithms from Introduction to Algorithms
 * @author Steven Avery
 * @date 2017/11/27
 */


#include <iostream>   // std::cout, size_t
#include <functional> // std::function (used to pass function as argument)
#include <climits>    // INT_MAX for merge sentinal
#include <math.h>     // floor
#include <stdlib.h>   // srand, rand
#include <time.h>     // time (used to seed srand)

#define inf INT_MAX

// swap elements in an array by index
void swap(int A[], unsigned int i, unsigned int j) {
	int temp = A[j];
	A[j] = A[i];
	A[i] = temp;
}

// tests given sort function to given array
// basic format all sorting functions must follow
// pass the sort function, input list, and length of input list
void testSort(std::string sortName,
              std::function<void(int[], size_t)> sortFunction,
              int A[],
              size_t ALength) {
	// copy A so that we don't effect the original array
	int* ACopy = new int[ALength];
	for(int i = 0; i < ALength; ++i)
		ACopy[i] = A[i];

	// sort the array
	sortFunction(ACopy, ALength);

	// check that answer is valid
	bool correctOrder = true;
	for(int i = 0; i < ALength-1; ++i)
		if(ACopy[i] > ACopy[i+1])
		 	correctOrder = false;

	// output results
	// output if the answer is valid in green or red
	if(correctOrder) std::cout << "\033[32m" << sortName << "\033[0m\n";
	else             std::cout << "\033[31m" << sortName << "\033[0m\n";

	std::cout << "\tbefore sort: ";
	for(int i = 0; i < ALength; ++i)
		std::cout << A[i] << " ";
	std::cout << std::endl;

	std::cout << "\tafter  sort: ";
	for(int i = 0; i < ALength; ++i)
		std::cout << ACopy[i] << " ";
	std::cout << std::endl;

	// make the spacing look pretty
	std::cout << std::endl;

	// clear ACopy from stack
	delete[] ACopy;
}

// insertion sort is similar to how most people order playing cards
// start with sorted left side of hand empty (left of key)
// compare the next card with each other sorted card from right to left to find
//     final position
// the index j represents the current "card" being inserted into the hand
void insertionSort(int A[], size_t ALength) {
	// start at the second element (the first element is already sorted)
	for(int j = 1; j < ALength; ++j) {
		int key = A[j];

		// i is the location to move it to (start with one space)
		int i = j-1;
		while(i >= 0 && A[i] > key) {
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}
}

// have the next element rise to the top like a bubble
void bubbleSort(int A[], size_t ALength) {
	for(int i = 0; i < ALength; ++i) {
		for(int j = ALength-1; j > i; --j) {
			if(A[j] < A[j-1]) {
				swap(A, j-1, j); // swap elements
			}
		}
	}
}

// repeatedly divide A into two subsequences of n/2 elements each, until length
//     of subbarray is 1, since a list of one element will always be sorted.
// merge the two sorted subsequences, by taking the next element in order
//     (will always be on the top on one of the two subsequences)
void mergeSort(int A[], size_t ALength) {
	// combine the two sorted lists for mergeSort by comparing the top element
	//     in each list and adding the lower one next
	// p, q, and r are indices into the array such that p <= q < r
	//          procedure assumes subarrays: A[p..q] and A[q+1..r]
	auto merge = [&](int p, int q, int r) {
		int n1 = q - p + 1; // length of subarray A[p..q]
		int n2 = r - q;     // length of subarray A[q+1..r]

		// define L for "left" subarray, and R for "right" subarray
		//     one additional space for sentinal
		int* L = new int[n1+1];
		int* R = new int[n2+1];

		// copy elements of A to respective subarrays (L and R)
		for(int i = 0; i < n1; ++i)
			L[i] = A[p+i];
		for(int i = 0; i < n2; ++i)
			R[i] = A[q+1+i];

		// set sentinal elements
		L[n1] = inf;
		R[n2] = inf;

		// put the next lowest element from L and R into next position in A
		int i = 0, j = 0;
		for(int k = p; k <= r; ++k) {
			if(L[i] <= R[j]) {
				A[k] = L[i];
				++i;
			} else {
				A[k] = R[j];
				++j;
			}
		}

		// clear L and R from the stack
		delete[] L;
		delete[] R;
	};

	// recursively divide and merge array A
	std::function<void(int, int)> mergeSortRecur;
	mergeSortRecur = [&](int p, int r) {
		if(p < r) {
			int q = floor((p+r)/2);
			mergeSortRecur(p, q);
			mergeSortRecur(q+1, r);
			merge(p, q, r);
		}
	};

	mergeSortRecur(0, ALength-1);
}

// turn the given array into a valid max heap
//     this runs `maxHeapify` on all heaps with more than one element
//     (since one element will always be a valid heap)
// takes off the next largest element (A[0]) for sorted list
// creates another valid heap with maxHeapify to repeat
void heapSort(int A[], size_t ALength) {
	int heapSize = ALength-1;

	// return the index of the parent of the given index
	auto parent = [](unsigned int i) -> unsigned int {
		// return itself if root node index provided
		return i==0 ? 0 : floor((i-1)/2);
	};
	// return the index of the left child of the given index
	auto left   = [](unsigned int i) -> unsigned int {
		return i*2 + 1;
	};
	// return the index of the right child of the given index
	auto right  = [](unsigned int i) -> unsigned int {
		return (i+1) * 2;
	};

	// assumes left and right children are already max heaps, but A[i] might be
	//     smaller allowing A[i] to "float down" to form max heap
	std::function<void (unsigned int)> maxHeapify;
	maxHeapify = [&](unsigned int i) {
		int l = left(i), r = right(i);
		int largest;

		// find largest of A[i], A[l], and A[r] to be head
		if(l <= heapSize && A[l] > A[i])
			largest = l;
		else
			largest = i;
		if(r <= heapSize && A[r] > A[largest])
		 	largest = r;

		if(largest != i) {
			// swap A[i] with A[largest]
			swap(A, i, largest);
			// since swap occured run recursively on children
			maxHeapify(largest);
		}
	};

	// bottom up manner to convert an array into a max heap
	auto buildMaxHeap = [&]() {
		for(int i = floor(heapSize/2); i >= 0; --i)
		 	maxHeapify(i);
	};

	// before beginning sort A must be a max heap
	buildMaxHeap();

	// go through the entire array taking the head (max element), and then
	//     maxHeapify to turn back into heap
	for(int i = heapSize; i > 0; --i) {
		swap(A, 0, i);
		--heapSize;
		maxHeapify(0);
	}
}

// pick a pivot (in this case the last element).
// have a moving wall, such that every element left of the wall is < the pivot,
//     and every element right of the wall is > the pivot.
// swap the pivot to the location of the wall.
// repeat on two sub arrays (left of wall and right of wall).
// at the end, every element will have all larger elements to the right, and all
//     smaller elements to the left, making it sorted.
void quickSort(int A[], size_t ALength) {
	auto partition = [&](int p, int r) -> int {
		int pivotIndex = r-1;
		int pivotValue = A[pivotIndex]; // select last element to be pivot
		int wall = p-1; // set the "wall" to the left of the first element

		// go from the first element to just before the pivot
		for(int j = p; j < pivotIndex; ++j) {
			if(A[j] <= pivotValue) {
				++wall; // move the wall one element to the right
				swap(A, wall, j);
			}
		}

		// move the pivot element to the wall so that all elements to the left
		//     are less and all elements to the right are more
		++wall;
		swap(A, wall, pivotIndex);

		return wall; // return the final pivot point
	};

	std::function<void (int, int)> quickSortRecur;
	quickSortRecur = [&](int p, int r) {
		if(p < r) { // a list of one element will always be sorted
			int q = partition(p, r);
			quickSortRecur(p, q);   // sort the left side of the pivot point
			quickSortRecur(q+1, r); // sort the right side of the pivot point
		}
	};

	// sort the entire array
	quickSortRecur(0, ALength);
}

void randomizedQuickSort(int A[], size_t ALength) {
	auto partition = [&](int p, int r) -> int {
		int pivotIndex = r-1;
		int pivotValue = A[pivotIndex]; // select last element to be pivot
		int wall = p-1; // set the "wall" to the left of the first element

		// go from the first element to just before the pivot
		for(int j = p; j < pivotIndex; ++j) {
			if(A[j] <= pivotValue) {
				++wall; // move the wall one element to the right
				swap(A, wall, j);
			}
		}

		// move the pivot element to the wall so that all elements to the left
		//     are less and all elements to the right are more
		++wall;
		swap(A, wall, pivotIndex);

		return wall; // return the final pivot point
	};

	auto randomizedPartition = [&](int p, int r) -> int {
		// instead of always using A[r] as the pivot
		//     swap a random element with A[r] before partitioning
		int i = rand() % (r-p) + p;
		swap(A, r-1, i);
		return partition(p, r);
	};

	std::function<void (int, int)> quickSortRecur;
	quickSortRecur = [&](int p, int r) {
		if(p < r) { // a list of one element will always be sorted
			int q = randomizedPartition(p, r);
			quickSortRecur(p, q);   // sort the left side of the pivot point
			quickSortRecur(q+1, r); // sort the right side of the pivot point
		}
	};

	// sort the entire array
	quickSortRecur(0, ALength);
}

int main(int argc, char** argv) {
	srand(time(NULL));
	// int A[] = {8, 7, 6, 5, 4, 3, 2, 1};
	int A[] = {8, 5, 2, 7, 2, 4, 6, 1, 3};
	size_t ALength = sizeof(A)/sizeof(A[0]);

	testSort("INSERTION SORT",        insertionSort,       A, ALength);
	testSort("BUBBLE SORT",           bubbleSort,          A, ALength);
	testSort("MERGE SORT",            mergeSort,           A, ALength);
	testSort("HEAP SORT",             heapSort,            A, ALength);
	testSort("QUICK SORT",            quickSort,           A, ALength);
	testSort("RANDOMIZED QUICK SORT", randomizedQuickSort, A, ALength);

	return 0;
}
