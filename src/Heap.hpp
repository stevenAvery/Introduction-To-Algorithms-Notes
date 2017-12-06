/*
 * An array based heap data structure class (restricted to int only)
 * @author Steven Avery
 * @date 2017/11/27
 */

#ifndef HEAP_HPP
#define HEAP_HPP

class Heap {
	private:
		int *A;
		size_t ALength;

	public:
		Heap(int[], size_t);
		int& operator[](int i);
		unsigned int parent(unsigned int i);
		unsigned int left  (unsigned int i);
		unsigned int right (unsigned int i);
};

#endif
