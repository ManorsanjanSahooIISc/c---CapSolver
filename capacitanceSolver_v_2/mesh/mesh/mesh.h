//v_2//
#include <iostream>
#include <vector>
#ifndef MESH_H_
#define MESH_H_
#include "node.h"
#include "patch.h"

#pragma once

class mesh {
private:
	std::vector <node> nodeList;
	std::vector <patch> patchList;
	int numNodes;
	int numPatches;
	int numNets;

public:
	void nodeListSize();
	void readNodeList();
	//void nodeListReadError();

	void patchListSize();
	void findNumNets();
	void readPatchList();

	int getNumNodes();
	int getNumPatches();
	int getNumNets();

	std::vector<node>& getNodeList();
	std::vector<patch>& getPatchList();
};
#endif // !PATC_H_