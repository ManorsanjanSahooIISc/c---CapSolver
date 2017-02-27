#ifndef MOMFILLER_H_
#define MOMFILLER_H_
#pragma once

#include<iostream>
#include<vector>
#include <string.h>
#include <fstream>

#include "../../mesh/mesh/node.h"
#include "../../mesh/mesh/patch.h"
#include "../../mesh/mesh/mesh.h"
#include "../../matrix/matrix/matrix.h"
#include "../../integration/integration/integration.h"
#include "../../rhsFiller/rhsFiller/rhsFiller.h"


#include "../../../10.3/include/mkl.h"
#include "../../../10.3/include/mkl_blas.h"
#include "../../../10.3/include/mkl_blacs.h"
#include "../../../10.3/include/mkl_lapack.h"
//#include "../../"
using namespace std;

class momFiller {

private:

	int numPatches;
	int numNodes;
	int numNets;

	std::vector <node> nodesList;
	std::vector <patch> patchesList;

	mesh m;

	matrix zMat;
	matrix zTempMat;

	node obsCent, srcCent;

	integration integrations;

	std::vector <node> srcSevenPt;
	std::vector <node> obsSevenPt;

	node obsNorm, srcNorm;

	int* ipiv;

	double eps0 = 8.854e-12;
	double epsr = 1;
	double eps = eps0*epsr;
	double pi = 3.141592653589793;
	double constant = 1 / (4 * pi*eps);

	rhsFiller fillRhs;
	std::vector<double> presentRhs;
	std::vector <double> sigma;

	matrix capMat;

public:
	momFiller();
	void readMesh();
	void setPatch();
	void fillMomMatrix();
	matrix& getMomMatrix();
	std::vector <double> solveMom(int&);
	void chargeDensityCalculation(std::vector<double>, int&);


};

#endif // !MOMFILLER_H_