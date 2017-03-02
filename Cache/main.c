#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 65536
#define OFFSET 1048576
#define N 4
#define NUMBER_OF_ITERATIONS 15

unsigned long long rdtsc();

int main(){

	char* array; 
	array = (char*)malloc(OFFSET * N * sizeof(char));

	int index = 0 , count = 0, block = 0;
	unsigned long long start,end;

	if(array){
		printf("Memory allocated\n");
	}else{
		printf("Can't allocate memory");
		return 0;
	}

	char begin = 8;
	char lastRow = 1;

	printf("Block size: %ld, Offset: %ld, N: %ld\n", BLOCK_SIZE, OFFSET, N);

	for(int i = 0; i < N; i++){
		for(int j = 0; j < BLOCK_SIZE/N; j++){
			if(i * OFFSET == (N-1) * OFFSET){
				if(j = BLOCK_SIZE/4 - 1){
					array[i * OFFSET + j] = 0;
				}else{
					array[i * OFFSET + j] = lastRow;
					lastRow++;
				}
			}else{
				array[i * OFFSET + j] = begin;
				begin++;
			}
		}
	} 

	for(int i = 0; i < N; i++){
		for(int j = 0; j < BLOCK_SIZE/N; j++){
			if(j == 0){
				printf("Block %d starting address: %X\n", i, &array[i * OFFSET + j]);
			}
		}
	}

	for(int i = 0; i < N; i++){
		for(int j = 0; j < BLOCK_SIZE/N; j++){
			printf("%d, ", array[i * OFFSET + j]);
		}
		printf("\t");
	}

	while(count < NUMBER_OF_ITERATIONS){
		start = rdtsc();
		do{
			printf("Index: %d\n", index);
			index = array[block * OFFSET + index];
			block++;
			if(block == N){
				block = 0;
			}
		}while(index != 0);
		end = rdtsc();
		printf("Number of cycles: %lld\n", end - start);
		count++;
	}

	return 0;
}

unsigned long long rdtsc(){
    unsigned int low,high;
    __asm__ __volatile__ ("rdtsc" : "=a" (low), "=d" (high));
    return ((unsigned long long)high << 32) | low;
}