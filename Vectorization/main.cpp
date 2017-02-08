#include "matrix.h"

using namespace std;

int main(){
	Matrix A(3,2);
	Matrix B(2,3), result;

	system("clear");
	cout << "Input matrix A:" << endl;
	cin >> A;
	cout << "Input matrix B:" << endl;
	cin >> B;

	result = (A * B);

	cout << "Result of A * B:" << endl;
	cout << result << endl;

	/*Matrix A(3,3);

	A.fill(128);

	cout << "Matrix A: " << endl << A << endl;*/


	return 0;
}
