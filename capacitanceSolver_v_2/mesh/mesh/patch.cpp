//v_2//
#include<iostream>
#include<vector>
#include<math.h>
#include "node.h"
#include "patch.h"

using namespace std;

patch::patch() {

	patchNodes.resize(3);
	patchNodeNumber.resize(3);
	patchIndex = -1;
	centroid = node(-1, -1, -1, -1);
	normals = node(-1, -1, -1, -1);
	sevenPoints.resize(7);
	area = 0;
	maxEdgeLength = 0;
	patchNumber = 0;
	netNumber = 0;
}

void patch::setPatchNodes(int indx, node n_0, int ind_0, node n_1, int ind_1, node n_2, int ind_2, int netNo) {
	patchNodes.resize(3);
	indices.resize(3);
	patchIndex = indx;
	patchNodes[0] = n_0;
	indices[0] = ind_0;
	patchNodes[1] = n_1;
	indices[1] = ind_1;
	patchNodes[2] = n_2;
	indices[2] = ind_2;
	patchNumber = 0;
	netNumber = netNo;
	//cout << patchNodes[0] << patchNodes[1] << patchNodes[2] << endl;
}


void patch::setPatchNodes(int indx, int n_0, int n_1, int n_2, int netNo) {
	patchNodeNumber.resize(3);
	patchIndex = indx;
	netNumber = netNo;
	patchNodeNumber[0] = n_0;
	patchNodeNumber[1] = n_1;
	patchNodeNumber[2] = n_2;

}
void patch::setPatchNodes(std::vector<node>& N) {

	patchNodes[0] = N[patchNodeNumber[0]];
	patchNodes[1] = N[patchNodeNumber[1]];
	patchNodes[2] = N[patchNodeNumber[2]];
	//cout << patchNodeNumber[0] << patchNodeNumber[1] << patchNodeNumber[2] << endl;
}
std::vector<node> patch::getPatcNodes() {
	return patchNodes;
}

void patch::setPatch(patch& p) {
	netNumber = p.netNumber;
	patchIndex = p.patchIndex;
	patchNodeNumber[0] = p.patchNodeNumber[0];
	patchNodeNumber[1] = p.patchNodeNumber[1];
	patchNodeNumber[2] = p.patchNodeNumber[2];
	centroid = p.centroid;
	normals = p.normals;
	sevenPoints = p.sevenPoints;
	maxEdgeLength = p.maxEdgeLength;
	area = p.area;
	patchNodes = p.patchNodes;
	patchNumber = p.patchNumber;

	//patchNodes[0] = p.patchNodes[0];
	//patchNodes[1] = p.patchNodes[1];
	//patchNodes[2] = p.patchNodes[2];
}

void patch::fillCentroid(node* n1, node* n2, node* n3) {
	double c1, c2, c3;
	c1 = (n1->getNodeCoordinates().at(0) + n2->getNodeCoordinates().at(0) + n3->getNodeCoordinates().at(0)) / 3;
	c2 = (n1->getNodeCoordinates().at(1) + n2->getNodeCoordinates().at(1) + n3->getNodeCoordinates().at(1)) / 3;
	c3 = (n1->getNodeCoordinates().at(2) + n2->getNodeCoordinates().at(2) + n3->getNodeCoordinates().at(2)) / 3;
	centroid = node(patchIndex,c1, c2, c3);
	//centroid.setNodeCoordinates(c1,c2,c3);
}
node patch::getCentroid() { return centroid; }

int patch::getPatchNumber() { return patchNumber; }

int patch::getNetNumber() { return netNumber; }

void patch::fillCentroid(std::vector<node> &N) {

	na.setNodeCoordinates(-1,N[patchNodeNumber[0]].getNodeCoordinate_x(), 
		N[patchNodeNumber[0]].getNodeCoordinate_y(), N[patchNodeNumber[0]].getNodeCoordinate_z());
	nb.setNodeCoordinates(-1,N[patchNodeNumber[1]].getNodeCoordinate_x(), 
		N[patchNodeNumber[1]].getNodeCoordinate_y(), N[patchNodeNumber[1]].getNodeCoordinate_z());
	nc.setNodeCoordinates(-1,N[patchNodeNumber[2]].getNodeCoordinate_x(), 
		N[patchNodeNumber[2]].getNodeCoordinate_y(), N[patchNodeNumber[2]].getNodeCoordinate_z());
	centroid = (na + nb + nc) / 3;
	centroid.setNodeCoordinates(patchIndex, centroid.getNodeCoordinate_x(), 
		centroid.getNodeCoordinate_y(), centroid.getNodeCoordinate_z());
}

void patch::setNormal(std::vector <node*> N) {

	na.setNodeCoordinates(-1,N[patchNodeNumber[0]]->getNodeCoordinates().at(0), 
		N[patchNodeNumber[0]]->getNodeCoordinates().at(1), N[patchNodeNumber[0]]->getNodeCoordinates().at(2));
	nb.setNodeCoordinates(-1,N[patchNodeNumber[1]]->getNodeCoordinates().at(0), 
		N[patchNodeNumber[1]]->getNodeCoordinates().at(1), N[patchNodeNumber[1]]->getNodeCoordinates().at(2));
	nc.setNodeCoordinates(-1,N[patchNodeNumber[2]]->getNodeCoordinates().at(0), 
		N[patchNodeNumber[2]]->getNodeCoordinates().at(1), N[patchNodeNumber[2]]->getNodeCoordinates().at(2));

	nx.setNodeCoordinates(-1,0, 0, 0);
	ny.setNodeCoordinates(-1,0, 0, 0);
	nx = nb, ny = nc;
	nx = nx - na;
	ny = ny - na;
	normals.setNodeCoordinates(-1,0, 0, 0);
	normals.crossProduct(nx, ny);
	normals.divideNode(2 * area);
	/*	cout << "Normal" << normals.getNodeCoordinates().at(0) << "\t" 
	<< normals.getNodeCoordinates().at(1) << "\t" << normals.getNodeCoordinates().at(2) << endl;*/
}

void patch::setNormal(std::vector<node>& N) {
	na.setNodeCoordinates(-1,N[patchNodeNumber[0]].getNodeCoordinate_x(), 
		N[patchNodeNumber[0]].getNodeCoordinate_y(), N[patchNodeNumber[0]].getNodeCoordinate_z());
	nb.setNodeCoordinates(-1,N[patchNodeNumber[1]].getNodeCoordinate_x(), 
		N[patchNodeNumber[1]].getNodeCoordinate_y(), N[patchNodeNumber[1]].getNodeCoordinate_z());
	nc.setNodeCoordinates(-1,N[patchNodeNumber[2]].getNodeCoordinate_x(),
		N[patchNodeNumber[2]].getNodeCoordinate_y(), N[patchNodeNumber[2]].getNodeCoordinate_z());

	nx.setNodeCoordinates(-1,0, 0, 0);
	ny.setNodeCoordinates(-1,0, 0, 0);
	nx = nb, ny = nc;
	//nx = nx - na;
	//ny = ny - na;
	nx.substractNode(na);
	ny.substractNode(na);
	normals.setNodeCoordinates(patchIndex,0, 0, 0);
	normals.crossProduct(nx, ny);
	normals.divideNode(2 * area);
}

void patch::setNormal(node* n1, node* n2, node* n3) {
	na.setNodeCoordinates(-1,n1->getNodeCoordinate_x(), n1->getNodeCoordinate_y(), n1->getNodeCoordinate_z());
	nb.setNodeCoordinates(-1,n2->getNodeCoordinate_x(), n2->getNodeCoordinate_y(), n3->getNodeCoordinate_z());
	nc.setNodeCoordinates(-1,n3->getNodeCoordinate_x(), n3->getNodeCoordinate_y(), n3->getNodeCoordinate_z());
	nx.setNodeCoordinates(-1,0, 0, 0);
	ny.setNodeCoordinates(-1,0, 0, 0);
	nx = nb; ny = nc;
	nx = nx - na;
	ny = ny - na;
	normals.setNodeCoordinates(patchIndex,0, 0, 0);
	normals.crossProduct(nx, ny);
	normals.divideNode(2 * area);
	/*cout << "normals \t" << normals.getNodeCoordinate_x() << normals.getNodeCoordinate_y() 
	<< normals.getNodeCoordinate_z() << endl;*/

}

node patch::getNormal() {
	return normals;
}


void patch::fillSevenPoints(node* n1, node* n2, node* n3) {
	sevenPoints.resize(7);
	double x = 0, y = 0, z = 0;
	double x_1, x_2, x_3, y_1, y_2, y_3, z_1, z_2, z_3;
	double diffx_21, diffx_31, diffy_21, diffy_31, diffz_21, diffz_31;
	double xsi[] = { 0.3333333, 0.0597158, 0.470142, 0.470142, 0.7974269, 0.1012865, 0.1012865 };
	double eta[] = { 0.3333333, 0.470142, 0.0597158, 0.470142, 0.1012865, 0.7974269, 0.1012865 };
	//double gamma[] = {0.3333334, 0.47014220, 0.4701422, 0.05971599, 0.1012866, 0.1012866, 0.7974270};

	x_1 = n1->getNodeCoordinates().at(0);   x_2 = n2->getNodeCoordinates().at(0);	x_3 = n3->getNodeCoordinates().at(0);
	y_1 = n1->getNodeCoordinates().at(1);	y_2 = n2->getNodeCoordinates().at(1);   y_3 = n3->getNodeCoordinates().at(1);
	z_1 = n1->getNodeCoordinates().at(2); 	z_2 = n2->getNodeCoordinates().at(2);	z_3 = n3->getNodeCoordinates().at(2);
	diffx_21 = x_2 - x_1; diffx_31 = x_3 - x_1;
	diffy_21 = y_2 - y_1; diffy_31 = y_3 - y_1;
	diffz_21 = z_2 - z_1; diffz_31 = z_3 - z_1;
	for (int i = 0;i < 7;i++) {
		x = x_1 + diffx_21*xsi[i] + diffx_31*eta[i];
		y = y_1 + diffy_21*xsi[i] + diffy_31*eta[i];
		z = z_1 + diffz_21*xsi[i] + diffz_31*eta[i];
		sevenPoints[i] = node(x, y, z, i);

		cout << x << "\t" << y << "\t" << z << endl;
	}
}

void patch::fillSevenPoints(std::vector<node> & N) {
	sevenPoints.resize(7);
	double x = 0, y = 0, z = 0;
	double x_1, x_2, x_3, y_1, y_2, y_3, z_1, z_2, z_3;
	double diffx_21, diffx_31, diffy_21, diffy_31, diffz_21, diffz_31;

	double xsi[] = { 0.3333333, 0.0597158, 0.470142, 0.470142, 0.7974269, 0.1012865, 0.1012865 };
	double eta[] = { 0.3333333, 0.470142, 0.0597158, 0.470142, 0.1012865, 0.7974269, 0.1012865 };

	na.setNodeCoordinates(-1,N[patchNodeNumber[0]].getNodeCoordinate_x(), 
		N[patchNodeNumber[0]].getNodeCoordinate_y(), N[patchNodeNumber[0]].getNodeCoordinate_z());
	nb.setNodeCoordinates(-1,N[patchNodeNumber[1]].getNodeCoordinate_x(), 
		N[patchNodeNumber[1]].getNodeCoordinate_y(), N[patchNodeNumber[1]].getNodeCoordinate_z());
	nc.setNodeCoordinates(-1,N[patchNodeNumber[2]].getNodeCoordinate_x(), 
		N[patchNodeNumber[2]].getNodeCoordinate_y(), N[patchNodeNumber[2]].getNodeCoordinate_z());

	x_1 = na.getNodeCoordinate_x(); y_1 = na.getNodeCoordinate_y(); z_1 = na.getNodeCoordinate_z();
	x_2 = nb.getNodeCoordinate_x(); y_2 = nb.getNodeCoordinate_y(); z_2 = nb.getNodeCoordinate_z();
	x_3 = nc.getNodeCoordinate_x(); y_3 = nc.getNodeCoordinate_y(); z_3 = nc.getNodeCoordinate_z();

	diffx_21 = x_2 - x_1; diffx_31 = x_3 - x_1;
	diffy_21 = y_2 - y_1; diffy_31 = y_3 - y_1;
	diffz_21 = z_2 - z_1; diffz_31 = z_3 - z_1;

	for (int i = 0; i < 7; i++) {
		sevenPoints[i].setNodeCoordinates(patchIndex,(x_1 + diffx_21*xsi[i] + diffx_31*eta[i]), 
			(y_1 + diffy_21*xsi[i] + diffy_31*eta[i]), (z_1 + diffz_21*xsi[i] + diffz_31*eta[i]));
	}
}

std::vector <node> patch::getSevenPoints() {
	return sevenPoints;
}

void patch::fillArea(node* n1, node* n2, node* n3) {
	double l_1, l_2, l_3, s;
	double x_1, x_2, x_3, y_1, y_2, y_3, z_1, z_2, z_3;
	//double diffx_21, diffx_31, diffy_21, diffy_31, diffz_21, diffz_31, diffx_32, diffy_32, diffz_32;

	x_1 = n1->getNodeCoordinates().at(0);   x_2 = n2->getNodeCoordinates().at(0);	x_3 = n3->getNodeCoordinates().at(0);
	y_1 = n1->getNodeCoordinates().at(1);	y_2 = n2->getNodeCoordinates().at(1);   y_3 = n3->getNodeCoordinates().at(1);
	z_1 = n1->getNodeCoordinates().at(2); 	z_2 = n2->getNodeCoordinates().at(2);	z_3 = n3->getNodeCoordinates().at(2);

	l_1 = sqrt((x_2 - x_1)*(x_2 - x_1) + (y_2 - y_1)*(y_2 - y_1) + (z_2 - z_1)*(z_2 - z_1));
	l_2 = sqrt((x_3 - x_1)*(x_3 - x_1) + (y_3 - y_1)*(y_3 - y_1) + (z_3 - z_1)*(z_3 - z_1));
	l_3 = sqrt((x_3 - x_2)*(x_3 - x_2) + (y_3 - y_2)*(y_3 - y_2) + (z_3 - z_2)*(z_3 - z_2));
	s = (l_1 + l_2 + l_3) / 2;
	area = sqrt(s*(s - l_1)*(s - l_2)*(s - l_3));
	cout << area << endl;
}

void patch::fillArea(std::vector<node>& N) {
	double l_1, l_2, l_3;
	double s;

	na.setNodeCoordinates(-1,N[patchNodeNumber[0]].getNodeCoordinate_x(), 
		N[patchNodeNumber[0]].getNodeCoordinate_y(), N[patchNodeNumber[0]].getNodeCoordinate_z());
	nb.setNodeCoordinates(-1,N[patchNodeNumber[1]].getNodeCoordinate_x(), 
		N[patchNodeNumber[1]].getNodeCoordinate_y(), N[patchNodeNumber[1]].getNodeCoordinate_z());
	nc.setNodeCoordinates(-1,N[patchNodeNumber[2]].getNodeCoordinate_x(), 
		N[patchNodeNumber[2]].getNodeCoordinate_y(), N[patchNodeNumber[2]].getNodeCoordinate_z());

	nx = na;
	nx.substractNode(nb);

	ny = na;
	ny.substractNode(nc);

	nz = nb;
	nz.substractNode(nc);

	l_1 = nx.norm();
	l_2 = ny.norm();
	l_3 = nz.norm();

	s = (l_1 + l_2 + l_3) / 2;
	area = sqrt(s*(s - l_1)*(s - l_2)*(s - l_3));
}

double patch::getPatchArea() {
	return area;
}

void patch::fillMaxLength(node* n1, node* n2, node* n3) {
	double l_1, l_2, l_3, maxLen;
	double x_1, x_2, x_3, y_1, y_2, y_3, z_1, z_2, z_3;

	x_1 = n1->getNodeCoordinates().at(0);   x_2 = n2->getNodeCoordinates().at(0);	x_3 = n3->getNodeCoordinates().at(0);
	y_1 = n1->getNodeCoordinates().at(1);	y_2 = n2->getNodeCoordinates().at(1);   y_3 = n3->getNodeCoordinates().at(1);
	z_1 = n1->getNodeCoordinates().at(2); 	z_2 = n2->getNodeCoordinates().at(2);	z_3 = n3->getNodeCoordinates().at(2);

	l_1 = sqrt((x_2 - x_1)*(x_2 - x_1) + (y_2 - y_1)*(y_2 - y_1) + (z_2 - z_1)*(z_2 - z_1));
	l_2 = sqrt((x_3 - x_1)*(x_3 - x_1) + (y_3 - y_1)*(y_3 - y_1) + (z_3 - z_1)*(z_3 - z_1));
	l_3 = sqrt((x_3 - x_2)*(x_3 - x_2) + (y_3 - y_2)*(y_3 - y_2) + (z_3 - z_2)*(z_3 - z_2));

	/* if (l_1 >= l_2) { maxLen = l_1; if (l_3>=maxLen) maxLen = l_3; maxLen = maxLen; }
	else { maxLen = l_2; if (l_3 >= maxLen) maxLen = l_3; maxLen = maxLen; }*/

	if (l_1 >= l_2 && l_1 >= l_3) maxLen = l_1;
	else if (l_2 >= l_3) maxLen = l_2;
	else maxLen = l_3;
	maxEdgeLength = maxLen;
	//	cout << maxLen << endl;
}

void patch::fillMaxLength(std::vector<node> &N) {
	double l_1, l_2, l_3, maxLen;
	//double x_1, x_2, x_3, y_1, y_2, y_3, z_1, z_2, z_3;

	na.setNodeCoordinates(-1,N[patchNodeNumber[0]].getNodeCoordinate_x(), 
		N[patchNodeNumber[0]].getNodeCoordinate_y(), N[patchNodeNumber[0]].getNodeCoordinate_z());
	nb.setNodeCoordinates(-1,N[patchNodeNumber[1]].getNodeCoordinate_x(), 
		N[patchNodeNumber[1]].getNodeCoordinate_y(), N[patchNodeNumber[1]].getNodeCoordinate_z());
	nc.setNodeCoordinates(-1,N[patchNodeNumber[2]].getNodeCoordinate_x(), 
		N[patchNodeNumber[2]].getNodeCoordinate_y(), N[patchNodeNumber[2]].getNodeCoordinate_z());

	nx = na;
	nx.substractNode(nb);

	ny = na;
	ny.substractNode(nc);

	nz = nb;
	nz.substractNode(nc);

	l_1 = nx.norm();
	l_2 = ny.norm();
	l_3 = nz.norm();
	if (l_1 >= l_2 && l_1 >= l_3) maxLen = l_1;
	else if (l_2 >= l_3) maxLen = l_2;
	else maxLen = l_3;
	maxEdgeLength = maxLen;
}

double patch::getMaxLength() {
	return maxEdgeLength;
}