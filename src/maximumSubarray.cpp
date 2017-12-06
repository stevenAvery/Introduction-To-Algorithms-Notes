/**
 * Solutions to maximum-subarray problem from Introduction to Algorithms
 * @author Steven Avery
 * @date 2017/11/23
 */


#include <iostream>   // std::cout

// object of start and end indices of subarray
struct Subarray {
	int start;
	int end;
};

// solve the maximum-subarray problem using brute force: O(n^2)
Subarray bruteForce(int A[], size_t ALength) {
	int maxSum = 0;
	Subarray maxSubarray;

	// go through every possible length of subarray
	for(int len = 1; len < ALength; ++len) {
		// go through each subarray of length: len
		for(int i = 0; i <= ALength-len; ++i) {

			// sum the subarray
			int sum = 0;
			for(int j = i; j < i+len; ++j)
				sum += A[j];

			// if this is the maxSum found, this is a maxSubarray found
			if(sum > maxSum) {
				maxSum = sum;
				maxSubarray.start = i;
				maxSubarray.end   = i+len;
			}
		}
	}

	return maxSubarray;
}

int main(int argc, char** argv) {
	int A[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

	// output the subarray from brute force solution
	Subarray sol = bruteForce(A, sizeof(A)/sizeof(A[0]));
	for(int i = sol.start; i < sol.end; ++i)
		std::cout << A[i] << " ";
	std::cout << std::endl;

	return 0;
}
