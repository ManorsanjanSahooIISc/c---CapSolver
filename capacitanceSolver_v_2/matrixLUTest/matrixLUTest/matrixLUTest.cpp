#include <iostream>
#include "../../matrixLU/matrixLU/matrixLU.h"
#include "../../mesh/mesh/node.h"
#include "../../mesh/mesh/patch.h"
#include "../../mesh/mesh/mesh.h"


using namespace std;
int main() {
	int row, col;
	mesh m;
	m.getNumPatches();
	//row = m
	matrixLU mLU;
	mLU.generateMatrixLU(row, col);
	return 0;
}