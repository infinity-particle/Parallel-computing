#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>

#define ALIGMENT 64
#define BLOCKSIZE 131072
#define OFFSET 1048576
#define N 15
#define ITERATIONS BLOCKSIZE / sizeof(int)


void fillArray(int* array, int number_of_fragments, int fragment_size, int offset){
	for (int i = 0; i < number_of_fragments; i++) {
		for (int j = 0; j < fragment_size; j++) {
			if (i < number_of_fragments - 1) {
				array[i * offset + j] = offset * (i + 1) + j;
			}
			else {
				if (j < fragment_size - 1) {
					array[i * offset + j] = j + 1;
				}
				else {
					array[i * offset + j] = 0;
				}
			}
		}
	}
}

unsigned long long rdtsc(){
    unsigned int low,high;
    __asm__ __volatile__ ("rdtsc" : "=a" (low), "=d" (high));
    return ((unsigned long long)high << 32) | low;
}



unsigned long long* getResult(int array[], int offsetInBytes, int maxWayNumber, int blockSizeInBytes){
	unsigned long long* results =(unsigned long long*)malloc(sizeof(unsigned long long) * N);

	unsigned long long beginTime, endTime;

	int offset = offsetInBytes / sizeof(int);

	for (int i = 0; i < maxWayNumber; i++){
		int fragmentSize = blockSizeInBytes / (sizeof(int) * (i+1));

		fillArray(array, i+1, fragmentSize, offset);

		int index;
		index = 0;

		beginTime = rdtsc();

		for (int j = 0; j < ITERATIONS; j++){
			index = array[index];
		}

		results[i] = rdtsc() - beginTime;
	}

	return results;
}

int main(){
	system("clear");

	int* array = (int*)aligned_alloc((size_t)ALIGMENT, (size_t)(OFFSET * N));
	unsigned long long *results = (unsigned long long *)aligned_alloc((size_t)ALIGMENT, (size_t)(N * sizeof(unsigned long long)));

	int retries = 5;

	for (int j = 0; j < N; j++){
		results[j] = 0;
	}

	for (int i = 0; i < retries; i++){
		unsigned long long *result = getResult(array, OFFSET, N, BLOCKSIZE);

		for (int j = 0; j < N; j++){
			results[j] += result[j];
		}
	}

	for (int j = 0; j < N; j++){
		results[j] /= (retries);
	}

	for (int i = 0; i < N; i++){
		printf("%d %llu\r\n", i, results[i]);
	}

	return 0;
}
