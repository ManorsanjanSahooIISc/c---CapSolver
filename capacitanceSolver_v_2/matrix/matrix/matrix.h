#ifndef  MATRIX_H_
#define MATRIX_H_
#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include <math.h>
#include <stdio.h>

#include "../../mesh/mesh/node.h"
#include "../../mesh/mesh/patch.h"
#include "../../mesh/mesh/mesh.h"
#include "matrix.h"
//#include <mkl.h>
//#include <mkl_blacs.h>
//#include <mkl_lapack.h>
#include "../../../10.3/include/mkl_blas.h"
#include "../../../10.3/include/mkl_blacs.h"
#include "../../../10.3/include/mkl_blas.h"
#include "../../../10.3/include/mkl_lapack.h"

class matrix {

private:
	std::vector<double> mat;
	std::vector<double> invMat;
	std::vector<double> temp;
	int numRows;
	int numCols;
	int varMatSize;
	// double temp[numRows][numCols];
public:
	matrix();
	matrix(int, int);
	void generateMatrix(int, int);
	void setMatrix(int, int, double);
	int* matrixLU();
	//void matrixInvers();
	void matrixSolve(std::vector<double>&, int*);

	matrix& getMatrix();
	double getMatrixElement(int, int);
	double getInvMatrixElement(int, int);

};

#endif // ! MATRIX_H_