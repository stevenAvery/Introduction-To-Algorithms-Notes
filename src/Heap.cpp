
#include <iostream>   // size_t
#include <math.h>     // floor
#include "Heap.hpp"

Heap::Heap(int A[], size_t ALength) {
	this->A = A;
	this->ALength = ALength;
}

int& Heap::operator[](int i) {
	return this->A[i];
}

unsigned int Heap::parent(unsigned int i) {
	// return itself if root node index provided
	return i==0 ? 0 : floor((i-1)/2);
}

unsigned int Heap::left  (unsigned int i) {
	return i*2 + 1;
}

unsigned int Heap::right (unsigned int i) {
	return (i+1) * 2;
}
