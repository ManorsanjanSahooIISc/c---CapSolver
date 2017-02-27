//v_2//
#include "node.h"
using namespace std;


//-------------------Empty Constructor----------------------------//
node::node() {
	coordinates.resize(3);
	nodeIndex = -1;
	//coordinates.clear();
}

//-----------------Parameterize Constructor----------------------//
node::node(int index, double x, double y, double z) {

	coordinates.resize(3);
	nodeIndex = index;
	coordinates[0] = x;
	coordinates[1] = y;
	coordinates[2] = z;
	//cout << coordinates[0] << "\t" << coordinates[1] << "\t" << coordinates[2] << endl;
}

void node::setNodeCoordinates(int index, double x, double y, double z) {
	nodeIndex = index;
	coordinates[0] = x; coordinates[1] = y; coordinates[2] = z; }

void node::setNode(int index, double val_1, double val_2, double val_3) {
	nodeIndex = index;
	coordinates.resize(3);
	coordinates[0] = val_1;
	coordinates[1] = val_2;
	coordinates[2] = val_3;
}

void node::setNode(node& N) {
	nodeIndex = N.nodeIndex;
	coordinates[0] = N.coordinates[0];
	coordinates[1] = N.coordinates[1];
	coordinates[2] = N.coordinates[2];
}
//void node::readNode(FILE* f) {	
//	for (int i = 0; i < 3; i++)   {	fprintf(f, "%lf", coordinates[0]);   fprintf(f, "%c", "\t");	}
//	fprintf(f, "%d", nodeIndex);   fprintf(f, "%c", "\n"); }

std::vector<double> node::getNodeCoordinates() {
	return coordinates;
}

double& node::getNodeCoordinate_x() { return coordinates[0]; }
double& node::getNodeCoordinate_y() { return coordinates[1]; }
double& node::getNodeCoordinate_z() { return coordinates[2]; }


//----------------Operations with Nodes-----------------------------//
//double node::dotProduct(node n1) {
//	double res = 0;
//	res = coordinates[0] * n1.coordinates[0] + coordinates[1] * n1.coordinates[1] + coordinates[2] * n1.coordinates[2];
//	return res;
//}

double node::dotProduct(node& n1) {
	double res = 0;
	res = coordinates[0] * n1.coordinates[0] + coordinates[1] * n1.coordinates[1] + coordinates[2] * n1.coordinates[2];
	return res;
}

//void node::crossProduct(node* n1, node* n2) {
//	coordinates[0] = n1->coordinates[1] * n2->coordinates[2] - n1->coordinates[2] * n1->coordinates[1];
//	coordinates[1] = n1->coordinates[2] * n2->coordinates[0] - n1->coordinates[0] * n1->coordinates[2];
//	coordinates[2] = n1->coordinates[0] * n2->coordinates[1] - n1->coordinates[1] * n2->coordinates[0];
//}

void node::crossProduct(node& n1, node& n2) {

	coordinates[0] = n1.coordinates[1] * n2.coordinates[2] - n1.coordinates[2] * n2.coordinates[1];
	coordinates[1] = n1.coordinates[2] * n2.coordinates[0] - n1.coordinates[0] * n2.coordinates[2];
	coordinates[2] = n1.coordinates[0] * n2.coordinates[1] - n1.coordinates[1] * n2.coordinates[0];
}

//double node::nodeDistance(node* n1) {
//	double distance = sqrt((coordinates[0] - n1->coordinates[0])*(coordinates[0] - n1->coordinates[0])
//		+ (coordinates[1] - n1->coordinates[1])*(coordinates[1] - n1->coordinates[1])
//		+ (coordinates[2] - n1->coordinates[2])*(coordinates[2] - n1->coordinates[2]));
//	return distance;
//}

double node::nodeDistance(node& n1) {
	double res= 0;
	res = sqrt((coordinates[0] - n1.coordinates[0])*(coordinates[0] - n1.coordinates[0]) + (coordinates[1] - n1.coordinates[1])*(coordinates[1] - n1.coordinates[1]) + (coordinates[2] - n1.coordinates[2])*(coordinates[2] - n1.coordinates[2]));
	return res;
}

double node::norm() {
	double nodeNorm =0;
	nodeNorm = sqrt(coordinates[0] * coordinates[0] + coordinates[1] * coordinates[1] + coordinates[2] * coordinates[2]);
	return nodeNorm;
}



//---------------------Operators On NODE------------------------------//

void node::substractNode(node n1) {
	for (int i = 0; i<3; i++)
		coordinates[i] = coordinates[i] - n1.coordinates[i];

}

void node::multiplyNode(double scale) {
	for (int i = 0; i<3; i++)
		coordinates[i] = scale*coordinates[i];
}

void node::divideNode(double scale) {
	for (int i = 0; i < 3; i++)
		//coordinates[i] = coordinates[i] / scale;
		coordinates[i] /= scale;
}

void node::substractWithScaleNode(node& n1, double scale) {

	for (int i = 0; i<3; i++)
		coordinates[i] = coordinates[i] - scale*n1.coordinates[i];
	nodeIndex = n1.nodeIndex;
}


//-----------------Operators to NODE------------------------//
node node::operator +(const node* n1) {
	node n2;
	for (int i = 0; i<3; i++)
		n2.coordinates[i] = coordinates[i] + n1->coordinates[i];
	//nodeIndex = n1->nodeIndex;
	return n2;
}
//node node::operator +(node n1) {
//	node n2;
//	for (int i = 0; i<3; i++)
//		n2.coordinates[i] = coordinates[i] + n1.coordinates[i];
//	//nodeIndex = n1.nodeIndex;
//	return n2;
//}
node node::operator +(const node& n1) {
	node n2;
	for (int i = 0; i < 3; i++)
		n2.coordinates[i] = coordinates[i] + n1.coordinates[i];
	return n2;
}

node node::operator -(const node& n1) {
	node n2;
	for (int i = 0; i < 3; i++)
		n2.coordinates[i] = coordinates[i] - n1.coordinates[i];
	return n2;
}

node node::operator -(const node* n1) {
	node n3;
	for (int i = 0; i<3; i++)
		n3.coordinates[i] = coordinates[i] - n1->coordinates[i];
	//nodeIndex = n1->nodeIndex;
	return n3;
}

//node node::operator -(const node n1) {
//	node n2;
//	for (int i = 0; i<3; i++)
//		n2.coordinates[i] = coordinates[i] - n1.coordinates[i];
//	nodeIndex = n1.nodeIndex;
//	return n2;
//}

//node node::operator -(node& n1) {
//	node n2;
//	for (int i = 0; i<3; i++)
//		n2.coordinates[i] = coordinates[i] - n1.coordinates[i];
//	return n2;
//}

node& node::operator =(const node& n1) {
	for (int i = 0; i<3; i++)
		coordinates[i] = n1.coordinates[i];
	nodeIndex = n1.nodeIndex;
	return *this;
}


node node::operator*(const double constant) {
	node n2;
	for (int i = 0; i<3; i++)
		n2.coordinates[i] = coordinates[i] * constant;
	nodeIndex = n2.nodeIndex;
	return n2;
}
node node::operator/(double constant) {
	node n2;
	if (constant == 0) { cout << "NAN triying to devide by '0'" << countNAN++ << "NAN Count" << endl; 	return n2; }
	for (int i = 0; i<3; i++)
		n2.coordinates[i] = coordinates[i] / constant;
	nodeIndex = n2.nodeIndex;
	return n2;
}


node node::operator/(const node* n1) {
	node n2;
	if (n1->coordinates[0] == 0) { cout << "NAN triying to devide by '0' to x-coordinate! " << endl; return n2; }
	n2.coordinates[0] = coordinates[0] / n1->coordinates[0];
	if (n1->coordinates[1] == 0) { cout << "NAN triying to devide by '0' to y-coordinate! " << endl; return n2; }
	n2.coordinates[1] = coordinates[1] / n1->coordinates[1];
	if (n1->coordinates[2] == 0) { cout << "NAN triying to devide by '0' to z-coordinate! " << endl; return n2; }
	n2.coordinates[2] = coordinates[2] / n1->coordinates[2];
	return n2;
}