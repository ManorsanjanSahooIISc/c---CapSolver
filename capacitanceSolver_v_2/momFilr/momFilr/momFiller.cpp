//v_2//
#include "momFiller.h"

using namespace std;

momFiller::momFiller() { }

void momFiller::readMesh() {
	m.nodeListSize();
	numNodes = m.getNumNodes();

	m.patchListSize();
	numPatches = m.getNumPatches();

	m.findNumNets();
	numNets = m.getNumNets();

	m.readNodeList();
	nodesList = m.getNodeList();

	m.readPatchList();
	patchesList = m.getPatchList();

	zMat.generateMatrix(numPatches, numPatches);
}

void momFiller::setPatch() {
	for (int pat = 0; pat < numPatches; pat++) {
		//cout << "numpatches in setpatch" << numPatches << endl;
		patchesList[pat].setPatchNodes(nodesList);
		patchesList[pat].fillArea(nodesList);
		patchesList[pat].fillCentroid(nodesList);
		patchesList[pat].setNormal(nodesList);
		patchesList[pat].fillSevenPoints(nodesList);
		patchesList[pat].fillMaxLength(nodesList);
	}
}

void momFiller::fillMomMatrix() {

	double obsArea;
	double srcArea;
	double distanceCentToCent;
	double obsMaxLen;
	double srcMaxLen;
	int count = 0;
	double momEntry = 0;
	//cout << "numPatches in fill Matrix" << numPatches << endl;

	for (int row = 0; row < numPatches; row++) {
		obsCent = patchesList[row].getCentroid();
		obsSevenPt = patchesList[row].getSevenPoints();
		obsNorm = patchesList[row].getNormal();
		obsArea = patchesList[row].getPatchArea();
		obsMaxLen = patchesList[row].getMaxLength();
		//cout << count << "Done" << endl;
		//count++;

		for (int col = 0; col < numPatches; col++) {
			srcCent = patchesList[col].getCentroid();
			srcSevenPt = patchesList[col].getSevenPoints();
			srcArea = patchesList[col].getPatchArea();
			srcNorm = patchesList[col].getNormal();
			srcMaxLen = patchesList[col].getMaxLength();

			integrations.setPatchListNodeList(patchesList[col], patchesList[row], obsCent);
			/*distanceCentToCent = obsCent.nodeDistance(srcCent);

			if (distanceCentToCent <= (4 * obsMaxLen)) {

			integrations.setObsPoint(obsCent);
			momEntry = constant*integrations.integrationAnalytical();
			}

			else if ((distanceCentToCent > (4 * obsMaxLen)) && (distanceCentToCent <= (10 * obsMaxLen))) {

			integrations.setObsPoint(obsCent);
			momEntry = constant*obsArea*integrations.integrationSevenPoint();
			}

			else if (distanceCentToCent>(10 * obsMaxLen)) {
			integrations.setObsPoint(obsCent);
			momEntry = constant*obsArea*integrations.integrationOnePoint();
			}
			else {
			cout << "Invalid MOM filling!" << endl;
			}*/
			momEntry = constant*(integrations.integrationAnalytical());
			zMat.setMatrix(row, col, momEntry);
		}
		//cout << row << endl;
	}
	zTempMat = zMat.getMatrix();
	ipiv = zTempMat.matrixLU();
	//ipiv = zMat.matrixLU();
}

matrix& momFiller::getMomMatrix() {

	return zMat;
}

std::vector<double> momFiller::solveMom(int& i) {
	presentRhs.resize(numPatches);
	fillRhs.fillRhs(presentRhs, patchesList, numPatches, i + 1);
	//zTempMat.matrixSolve(presentRhs, ipiv);
	zTempMat.matrixSolve(presentRhs, ipiv);
	sigma = presentRhs;
	return sigma;
}

void momFiller::chargeDensityCalculation(std::vector<double> sigma, int& i) {

	double sum;
	capMat.generateMatrix(numNets, numNets);
	for (int netRow = 0; netRow < numNets; netRow++) {
		sum = 0;
		for (int netCol = 0; netCol < numNets; netCol++) {
			if (patchesList[netCol].getNetNumber() == (netRow + 1))
				sum = sum + patchesList[netCol].getPatchArea()*sigma[netRow];
		}
		capMat.setMatrix(i, netRow, sum);
		cout << "capMat" << i << netRow << "is" << sum << "\t" << endl;
	}
	cout << endl;
}