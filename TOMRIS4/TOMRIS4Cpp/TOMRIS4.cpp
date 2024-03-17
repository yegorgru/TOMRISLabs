#include <iostream>
#include <chrono>
#include <random>

#include "Strassen.h"
#include "Profile.h"


int main() {

	// Simple Test

	// Size
	Size N = 8;

	// Matrices
	Matrix A = createMatrix(N), B = createMatrix(N), C = createMatrix(N);

	// Initialize the matrices
	randomize(A, N);
	randomize(B, N);

	// Print their values
	std::cout << "Matrix A:\n";
	print(A, N);

	std::cout << "\n\nMatrix B:\n";
	print(B, N);

	// Compute A * B using Strassen's Algorithm
	{
		LOG_DURATION("Strassen time");
		C = strassen(A, B, N);
	}

	// Print result
	std::cout << "\n\nResult with Strassen method:\n";
	print(C, N);

	system("pause");

	return 0;
}