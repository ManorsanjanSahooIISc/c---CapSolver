#include "matrixLU.h"


matrixLU::matrixLU() {
	numRow = 0;
	numCol = 0;
	mat.resize(numRow*numCol);
}

matrixLU::matrixLU(int row, int col) {
	mat.resize(row*col);
	numRow = row;
	numCol = col;
}

void matrixLU::generateMatrixLU(int row, int col) {
	mat.resize(row*col);
	numRow = row;
	numCol = col;
}

void matrixLU::setMatrixLU(int irow,int jcol,double value) {
	if (irow < numRow && jcol < numCol)
		mat[jcol*numRow + irow] = value;
	else
		cout << "Matrix Indices accessing undefined data" << endl;
}

matrixLU& matrixLU::getMatrixLU() {
	return *this;
}

double matrixLU::getMatrixLUElement(int row, int col) {
	if (row >= numRow || col >= numCol)
		cout << "Accessing a number out of range" << endl;
	double matElement;
	matElement = mat[col*numRow + row];
	return matElement;
}