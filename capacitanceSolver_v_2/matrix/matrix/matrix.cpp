#include "matrix.h"

using namespace std;

matrix::matrix() {

	numRows = 0;
	numCols = 0;
	mat.resize(numRows*numCols);
	//mat.clear();
}

matrix::matrix(int row, int col) {
	numRows = row;
	numCols = col;
	mat.resize(row*col);
}

void matrix::generateMatrix(int row, int col) {
	numRows = row;
	numCols = col;
	mat.resize(row*col);
}

void matrix::setMatrix(int row, int col, double value) {
	if (row < numRows && col < numCols) {
		mat[col*numRows + row] = value;
		//cout << mat[row*numRows + col] << endl;/**/
	}
	else
		cout << "Matrix Dimension Exceeds" << endl;
}

int* matrix::matrixLU()
{
	int dim; int* ipiv; int info = 10;
	int lda = numRows;
	dim = std::max(1, std::min(numRows, numCols));

	ipiv = (int*)malloc(dim * sizeof(int));
	dgetrf(&numRows, &numCols, &mat[0], &lda, &ipiv[0], &info);
	/*cout << endl << endl;
	cout << dim << endl;
	for (int i = 0; i < sqrt(dim); i++)
	cout << ipiv[i] << "\t";*/
	return(&ipiv[0]);
}


void matrix::matrixSolve(std::vector<double>& m1, int* ipiv) {
	char trans = 'N';
	int nrhs = 1;
	//FILE* fa;
	//fa = fopen("rhsbefore.txt","w");
	//for (int i = 0; i < 1744; i++) {
	//	fprintf(fa, "%f", m1[i]);
	//	fprintf(fa, "\n");
	//}

	int lda = std::max(1, numRows);
	int ldb = std::max(1, numRows);
	int info;
	dgetrs(&trans, &numRows, &nrhs, &mat[0], &lda, ipiv, &m1[0], &ldb, &info);

	//FILE* fb;
	//fb = fopen("rhsafter.txt", "w");
	//for (int i = 0; i < 1744; i++) {
	//	fprintf(fb, "%f", mat[i]);
	//	fprintf(fb, "\n");
	//}
}

matrix& matrix::getMatrix() { return *this; }

double matrix::getMatrixElement(int row, int col) {
	if ((row >= numRows) || (col >= numCols))
		cout << "Accessing out of Range Element" << endl;
	double matElement;
	matElement = mat[row*numRows + col];
	return matElement;
}

double matrix::getInvMatrixElement(int row, int col) {
	if ((row >= numRows) || (col >= numCols))
		cout << "Accessing out of Range Element" << endl;
	double invElement;
	invElement = invMat[row*numRows + col];
	return invElement;
}