#pragma once

#include <iostream>
#include <chrono>
#include <random>

// Aliases
using type = int;
using Matrix = type**;
using Size = std::size_t;


// Randomize matrix function
void randomize(Matrix& A, Size N) {	// O(n^2)
	std::uniform_int<int> dist(1, 5);
	std::mt19937 eng;
	for (unsigned int i = 0; i < N; i++) {
		for (unsigned int j = 0; j < N; j++) {
			eng.seed((double)std::chrono::system_clock::now().time_since_epoch().count());
			A[i][j] = dist(eng);
		}
	}
}


// Print function
void print(Matrix A, Size N) {	// O(n^2)
	for (unsigned int i = 0; i < N; i++) {
		for (unsigned int j = 0; j < N; j++) {
			std::cout << A[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}


// Returns a new NxN matrix
Matrix createMatrix(Size N) {
	Matrix newMatrix = new type * [N];
	for (unsigned int i = 0; i < N; i++) {
		newMatrix[i] = new type[N];
	}
	return newMatrix;
}


/***** Matrix Operations *******/


// Add two matrices
Matrix add(Matrix A, Matrix B, Size N) {

	Matrix C = createMatrix(N);

	for (unsigned int i = 0; i < N; i++)
		for (unsigned int j = 0; j < N; j++)
			C[i][j] = A[i][j] + B[i][j];

	return C;
}

// Subtract two matrices
Matrix subtract(Matrix A, Matrix B, Size N) {
	Matrix C = createMatrix(N);

	for (unsigned int i = 0; i < N; i++)
		for (unsigned int j = 0; j < N; j++)
			C[i][j] = A[i][j] - B[i][j];

	return C;
}
