//v_2//
#include<iostream>
#include<vector>
#include <string.h>
#include <fstream>
#include <time.h>

#include "../../mesh/mesh/node.h"
#include "../../mesh/mesh/patch.h"
#include "../../mesh/mesh/mesh.h"
#include "../../../10.3/include/mkl.h"
#include "../../../10.3/include/mkl_blas.h"
#include "../../../10.3/include/mkl_blacs.h"
#include "../../../10.3/include/mkl_lapack.h"
//#include "../../matrix/matrix/matrix.h"
//#include "../../integration/integration/integration.h"
#include "../../momFiller/momFiller/momFiller.h"
#include "../../rhsFiller/rhsFiller/rhsFiller.h"

using namespace std;
int main() {

	clock_t startTime, endTime;
	mesh m;
	m.findNumNets();
	int numNets = m.getNumNets();
	m.patchListSize();
	int numPatches = m.getNumPatches();
	momFiller momfill;
	momfill.readMesh();
	momfill.setPatch();

	cout << "MOM filling Start" << endl;
	startTime = clock();
	momfill.fillMomMatrix();
	int i = 0;
	endTime = clock();
	cout << "MOM filling Done" << endl;
	double timeTakenMomMatrixFilling = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	cout << "Time Taken for MOM Matrix Filling " << timeTakenMomMatrixFilling << endl;
	
	std::vector<double> sigma;
	sigma.resize(numPatches);

	matrix lhs;
	lhs.generateMatrix(numPatches, numNets);

	for (int i = 0; i < numNets; i++) {
		sigma = momfill.solveMom(i);
		for (int j = 0; j < numPatches; j++) {
			lhs.setMatrix(j, i, sigma[j]);
		}
		momfill.chargeDensityCalculation(sigma, i);
	}

	system("pause");
	return 0;
}