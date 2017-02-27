//Capacitance Solver Main V_2//
#include<iostream>
#include <fstream>
#include <time.h>
//#include <stdio.h>

#include "../../mesh/mesh/node.h"
#include "../../mesh/mesh/patch.h"
#include "../../mesh/mesh/node.h"
#include "../../matrix/matrix/matrix.h"
#include "../../momFilr/momFilr/momFiller.h"
#include "../../rhsFiller/rhsFiller/rhsFiller.h"
#include "../../integration/integration/integration.h"

#include "../../../10.3/include/mkl.h"
#include "../../../10.3/include/mkl_blacs.h"
#include "../../../10.3/include/mkl_blas.h"
#include "../../../10.3/include/mkl_lapack.h"

using namespace std;

int main() {
	clock_t startTime, endTime, beginTime, finishTime,momMatStart, momMatEnd;
	beginTime = clock();
	startTime = clock();
	
	mesh m;
	int numNets, numPatches;
	m.findNumNets();
	m.patchListSize();
	numNets = m.getNumNets();
	numPatches = m.getNumPatches();
	
	endTime = clock();
	double mesrReadtime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	cout << "Read time" << mesrReadtime << endl;
	
	//cout << "Number of nets are \t" << numNets << " and Number of Patches are \t" << numPatches << endl;
	
	startTime = clock();
	momFiller mfill;
	mfill.readMesh();
	mfill.setPatch();
	momMatStart = clock();
	mfill.fillMomMatrix();
	momMatEnd = clock();
	double momFillTime = (double)(momMatEnd - momMatStart) / CLOCKS_PER_SEC;
	cout << "mom Matrix Filling Time" << momFillTime << endl;
	
	//endTime = clock();
	//double setUpTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	//cout << "Set up Time o(n3)" << setUpTime << endl;
	
	
	startTime = clock();

	matrix chargeDensity;
	chargeDensity.generateMatrix(numPatches,numNets);

	std::vector <double> sigma;
	FILE *(cppRhs);
	cppRhs = fopen("cppRhs.txt", "w");
	for (int i = 0; i < numNets; i++) {
		sigma = mfill.solveMom(i);
		
		for (int row = 0; row<numPatches; row++) {
			chargeDensity.setMatrix(row,i, sigma[row]);
			fprintf(cppRhs, "%f", sigma[row]);
		}
		
		mfill.chargeDensityCalculation(sigma, i);
		fprintf(cppRhs, "\n");
	}



endTime = clock();
double solveTime = (double)(startTime - endTime) / CLOCKS_PER_SEC;
//cout << "SOlve time" << solveTime << endl;

finishTime = clock();
double totalExecutionTime = (double)(finishTime - beginTime) / CLOCKS_PER_SEC;
cout << "Total Time Take for Capacitance Solver " << totalExecutionTime << endl;
return 0;
}