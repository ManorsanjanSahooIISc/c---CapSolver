//v_2//
#ifndef PATCH_H_
#define PATCH_H_
#pragma once
#include <iostream>
#include <vector>
#include "node.h"

class patch {
private:
	std::vector <node> patchNodes;
	std::vector <int> patchNodeNumber;
	int patchIndex;
	node centroid;
	std::vector<node> sevenPoints;
	double area;
	double maxEdgeLength;
	//int bodyIndex;
	std::vector<int> indices;
	int patchNumber;
	int netNumber;
	node normals;
	node na, nb, nc;
	node nx, ny, nz;
public:
	patch();
	void setPatchNodes(int, node, int, node, int, node, int, int);
	void setPatchNodes(int, int, int, int, int);
	
	void fillCentroid(node*, node*, node*);
	void fillCentroid(std::vector<node> &);
	
	void setPatch(patch&);
	node getCentroid();
	int getPatchNumber();
	
	void fillSevenPoints(node*, node*, node*);
	void fillSevenPoints(std::vector<node> &);
	
	void fillArea(node*, node*, node*);
	void fillArea(std::vector<node> &);
	double getPatchArea();
	
	void fillMaxLength(node*, node*, node*);
	void fillMaxLength(std::vector<node> &);
	double getMaxLength();

	std::vector <node> getSevenPoints();
	std::vector <node> getPatcNodes();
	
	void setNormal(std::vector <node*>);
	void setNormal(node*, node*, node*);
	void setNormal(std::vector<node> &);
	
	node getNormal();
	int getNetNumber();

	void setPatchNodes(std::vector<node>&);


};
#endif // !PATCH_H_
