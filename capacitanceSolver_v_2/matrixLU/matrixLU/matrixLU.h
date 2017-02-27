#ifndef MATRIXLU_H_
#define MATRIXLU_H_
#pragma once
#include <iostream>
#include <math.h>
#include<vector>
#include <stdio.h>


using namespace std;
class matrixLU {
private:
	std::vector<double> mat;
	int numRow;
	int numCol;

public:
	matrixLU();
	matrixLU(int, int);
	void generateMatrixLU(int, int);
	void setMatrixLU(int, int, double);
	matrixLU& getMatrixLU();
	double getMatrixLUElement(int , int);
};

































#endif // !MATRIXLU_H_