#include <iostream>
#include <vector>
#ifndef NODE_H_
//v_2//
#define NODE_H_
#pragma once

class node {
private:
	std::vector <double> coordinates;
	int nodeIndex;

public:
	int countNAN = 0;
	node();
	node(int, double, double, double);
	void setNodeCoordinates(int, double, double, double);
	std::vector <double> getNodeCoordinates();
	void setNode(node&);
	void setNode(int, double, double, double);
	double& getNodeCoordinate_x();
	double& getNodeCoordinate_y();
	double& getNodeCoordinate_z();

	//double dotProduct(node);
	double dotProduct(node&);
	//void crossProduct(node*, node*);
	void crossProduct(node&, node&);
	//double nodeDistance(node*);
	double nodeDistance(node&);
	double norm();

	void substractNode(node);
	void multiplyNode(double);
	void divideNode(double);
	void substractWithScaleNode(node&, double);


	node operator +(const node*);
	//node operator +(const node);
	node operator +(const node&);
	node operator -(const node*);
	//node operator -(const node);
	node operator -(const node&);
	node& operator =(const node&);
	node operator *(const double);
	node operator /(const double);
	node operator /(const node*);


	//~node() { coordinates.clear(); }
};
#endif // !NODE_H_