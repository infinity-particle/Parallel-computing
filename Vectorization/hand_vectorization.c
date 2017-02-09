#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xmmintrin.h>

#define SIZE 1024*1024

void init_Arrays(float *A, float *B, float *C);
void print_Array(float *A);
void multiplication_without_vectorization(float *A, float *B, float *C)
{ 
  for(int i=0;i<SIZE;i++)
	  C[i]=A[i]*B[i];
}

void multiplication_with_vectorization(float *A, float *B, float *C)
{ 
	__m128 *X, *Y, *Z;

	X=(__m128 *)A;
	Y=(__m128 *)B;
	Z=(__m128 *)C;



	for(int i=0;i<SIZE/4;i++)
	{
		Z[i] = _mm_mul_ps(X[i], Y[i]);
	}
	
	_mm_store_ss(C, *Z);
}
int main()
{ 
	float *A,*B, *C, s;
	int start_time, end_time;
	
	A = (float *)_mm_malloc(SIZE*sizeof(float),16);
	B = (float *)_mm_malloc(SIZE*sizeof(float),16);
	C = (float *)_mm_malloc(SIZE*sizeof(float),16);

	init_Arrays (A, B, C);

	/*print_Array(A);
	print_Array(B);
	print_Array(C);*/

	start_time = clock();
	multiplication_without_vectorization(A, B, C);
	end_time = clock();

	/*printf ("result Array\n");
	print_Array(C);*/

	printf("time usual calculate: %f\n", (float)(end_time-start_time)/CLOCKS_PER_SEC);

	init_Arrays(A, B, C);

	start_time = clock();
	multiplication_with_vectorization(A, B, C);
	end_time = clock();

	/*printf ("result Array\n");
	print_Array(C);*/

	printf("time vectorization calculate: %f\n", (float)(end_time-start_time)/CLOCKS_PER_SEC);


	_mm_free(x); _mm_free(y);

  system("pause");
  return 0;
}

void init_Arrays(float *A, float *B, float *C)
{
	for(int i=0;i<SIZE;i++)
	{
		A[i] = 2;
		B[i] = 3;
		C[i] = 0;
	}
	return;
}

void print_Array(float *array)
{
	printf ("\n");
	for(int i=0;i<SIZE;i++)
		printf ("%f\t", array[i]);
	printf ("\n");
	return;
}