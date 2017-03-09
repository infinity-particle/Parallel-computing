#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdlib.h>
#include <stdint.h>

struct element;

class Array{
	public:
		Array();
		Array(int blockSize, int numberOfBlocks, int offset);
		void fillWithZigzagIndex();
		int length();
		friend std::ostream& operator << (std::ostream& output, const Array& array);
		//unsigned char operator [](int);
	private:
		int blockSize;
		int N;
		int offset;
		struct element* head;
		struct element* tail;
};

#endif