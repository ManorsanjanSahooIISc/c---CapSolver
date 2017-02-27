//v_2//
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <math.h>

#include "node.h"
#include "patch.h"
#include "mesh.h"

using namespace std;

void mesh::nodeListSize() {
	numNodes = 0;
	string line;
	ifstream nodeFile;
	nodeFile.open("nodelist_3D.txt");
	if (nodeFile.fail()) {
		cerr << "Error in opening nodelist_3D.txt" << endl;
	}
	if (nodeFile.is_open()) {
		while (!nodeFile.eof()) {
			getline(nodeFile, line);
			numNodes++;
		}
		nodeFile.close();
	}
	cout << "Number of Nodes are " << numNodes << endl;
}

void mesh::findNumNets() {
	numNets = 1;
	string line;
	int patch = 0;
	double netNum[4];
	ifstream numnet("patchlist_3D.txt");
	if (numnet.fail()) {
		cerr << "Error in reading patchlist_3D.txt" << endl;
	}
	if (numnet.is_open()) {
		while (!numnet.eof()) {
			numnet >> netNum[0] >> netNum[1] >> netNum[2] >> netNum[3];
			if (numNets <= netNum[3])
				numNets = (int)netNum[3];
		}
		cout << "Number of Conductor" << "\t" << numNets << endl;
		numnet.close();
	}
}

void mesh::readNodeList() {
	nodeList.resize(numNodes);
	ifstream readNodeList;
	readNodeList.open("nodelist_3D.txt");
	//	ofstream nodeListCrossCheck("nodeListCrossCheck.txt");

	int nodes = 0;
	double coordinate[3];
	while (!readNodeList.eof())
	{
		readNodeList >> coordinate[0] >> coordinate[1] >> coordinate[2];
		//nodeList[nodes] = node(nodes, coordinate[0], coordinate[1], coordinate[2]);
		nodeList[nodes].setNode(nodes, coordinate[0], coordinate[1], coordinate[2]);
		//nodeListCrossCheck.precision(12);
		//nodeListCrossCheck << coordinate[0] << '\t' << coordinate[1] << '\t' << coordinate[2] << endl;
		nodes = nodes + 1;
	}
	readNodeList.close();
}

//If necessary to check then run it.
//void mesh::nodeListReadError() {
//	ifstream readNodeList; readNodeList.open("nodelist_3D.txt");
//	ifstream readNodeListCrossCheck; readNodeListCrossCheck.open("nodeListCrossCheck.txt");
//
//	int nodes = 0; double a, b, c, error = 0; double cord[3]; double cordCrossCheck[3];
//	while (!readNodeList.eof()) {
//		readNodeList >> cord[0] >> cord[1] >> cord[2];
//		readNodeListCrossCheck >> cordCrossCheck[0] >> cordCrossCheck[1] >> cordCrossCheck[2];
//		a = fabsl (cord[0] - cordCrossCheck[0]) / fabsl (cord[0]); b = fabsl (cord[1] - cordCrossCheck[1]) / fabsl (cord[1]); c = fabsl (cord[2] - cordCrossCheck[2]) / fabsl (cord[2]);
//		error = (a + b + c); error+= error; nodes++; }
//	cout << "Error in reading nodeList is " << error << endl;
//	readNodeList.close(); readNodeListCrossCheck.close(); }

void mesh::patchListSize() {
	numPatches = 0;
	string line;
	ifstream patchFile("patchlist_3D.txt");
	if (patchFile.is_open()) {
		while (!patchFile.eof()) {
			getline(patchFile, line);
			numPatches++;
		}
		patchFile.close();
	}
	cout << "Number of Patches are " << numPatches << endl;
}

void mesh::readPatchList() {

	patchList.resize(numPatches);
	ifstream readPatch;
	readPatch.open("patchlist_3D.txt");
	int patches = 0;
	int patchNode[4];
	string line;

	while (!readPatch.eof())
	{
		readPatch >> patchNode[0] >> patchNode[1] >> patchNode[2] >> patchNode[3];
		//patchList[patches].setPatchNodes(patches, &nodeList[patchNode[0]], &nodeList[patchNode[1]], &nodeList[patchNode[2]]);

		//patchList[patches].setPatchNodes(patches, nodeList[patchNode[0]-1], patchNode[0], nodeList[patchNode[1]-1], patchNode[1], nodeList[patchNode[2]-1], patchNode[2]);
		patchList[patches].setPatchNodes(patches, patchNode[0] - 1, patchNode[1] - 1, patchNode[2] - 1, patchNode[3]);
		getline(readPatch, line);

		if (numNets <= patchNode[3])
			numNets = patchNode[3];

		//if (patches > numPatches - 2) {
		//	cout << "0th Index = " <<patchNode[0] << "  1st Index = " << patchNode[1] << "   2nd Index = " << patchNode[2] << endl;
		//}
		patches++;
	}
	cout << "Number of Conductor bodies are" << numNets << endl;
	cout << patches << endl;
	readPatch.close();
}

int mesh::getNumNodes() { return numNodes; }
int mesh::getNumPatches() { return numPatches; }
int mesh::getNumNets() { return numNets; }

std::vector<node>& mesh::getNodeList() { return nodeList; }
std::vector<patch>& mesh::getPatchList() { return patchList; }