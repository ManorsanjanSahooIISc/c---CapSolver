//V_2 Integration CPP//

#include "integration.h"
#include <math.h>
using namespace std;

void integration::setPatchListNodeList(patch& SP, patch& OP, node& obscent) {
	srcPatch.setPatch(SP);
	obsPatch.setPatch(OP);
	obsCentroid.setNode(obscent);
	//	obsPatch.getCentroid(obscent);
}

void integration::setObsPoint(node& observerPoint)
{
	obsCentroid = node(observerPoint);
}

double integration::greensfunction(node& n1, node& n2) {

	double gf, dist;
	dist = n1.nodeDistance(n2);
	gf = 1 / dist;
	return gf;
}


double integration::integrationOnePoint() {
	srcCentroid = srcPatch.getCentroid();
	onePoint = this->greensfunction(srcCentroid, obsCentroid);
	return onePoint;
}

double integration::integrationSevenPoint() {
	//double x = 0, y = 0, z = 0;
	double sum = 0;
	double dist;
	double weights[] = { 0.225, 0.13239415278851, 0.13239415278851, 0.13239415278851, 
						0.12593918054483, 0.12593918054483, 0.12593918054483 };
	srcSevenPoints = srcPatch.getSevenPoints();
	for (int i = 0; i < 7; i++)
	{

		dist = this->greensfunction(obsCentroid, srcSevenPoints[i]);
		sum = sum + weights[i] * distance;
		//temps = this->greensfunction(obsCentroid, srcSevenPoints[i]);
		//x = x + (temps.getNodeCoordinate_x() * weights[i]);
		//y = y + (temps.getNodeCoordinate_y() * weights[i]);
		//z = z + (temps.getNodeCoordinate_z() * weights[i]);
		//sevPtRes = node(x, y, z);
	}
	return sum;
}

double integration::integrationAnalytical() {

	this->setIntegration();
	return momEntry;
}

void integration::setIntegration() {
	src = srcPatch.getPatcNodes();
	momEntry = 0;
	//momEntry[0] = 0;
	//momEntry[1] = 0;
	//momEntry[2] = 0;
	//dummy.resize(3);
	//dummy[0] = 0;
	//dummy[1] = 0;
	//dummy[2] = 0;
	copy_node1 = src[0];
	copy_node2 = src[1];
	copy_node3 = src[2];
	//node n1(0, 0, 0, 1), n2(0, 1, 0, 3), n3(1, 0, 0, 2);
	//patch p;
	//srcPatch.setPatchNodes(&n1, &n2, &n3);
	//srcPatch.fillSevenPoints(&n1, &n2, &n3);
	//src = srcPatch.getPatcNodes();
	//srcPatch.fillArea(&n1, &n2, &n3);
	//area_source = srcPatch.getPatchArea();
	//cout << "Area is" << area_source << endl;

	//double a = (src[1]->getNodeCoordinate_x() - src[0]->getNodeCoordinate_x());
	area_source = srcPatch.getPatchArea();

	diff1 = src[1];
	diff1.substractNode(src[0]);

	diff2 = src[2];
	diff2.substractNode(src[0]);

	diff0 = obsCentroid;
	diff0.substractNode(src[0]);

	array_area.crossProduct(diff1, diff2);

	unit_n = array_area;
	unit_n.multiplyNode(-1);
	unit_n.divideNode(area_source * 2);

	dot_product = diff0.dotProduct(unit_n);

	//unit_n.
	centroid_on_plane = obsCentroid;
	centroid_on_plane.substractWithScaleNode(unit_n, dot_product);
	//centroid_on_plane = (unit_n*dot_product);
	//dot_product = diff0.dotProduct(unit_n);
	dot_product = std::abs(dot_product);

	for (int i = 1; i <= 3; i++)
	{
		int flag = 1;

		if (i == 1) { process_node1 = copy_node1;	process_node2 = copy_node2; }

		if (i == 2) { process_node1 = copy_node2;	process_node2 = copy_node3; }

		if (i == 3) { process_node1 = copy_node3;	process_node2 = copy_node1; }

		temp = process_node1 - process_node2;
		//length_side = sqrt(pow(temp.getNodeCoordinate_x(), 2) + pow(temp.getNodeCoordinate_y(), 2) + pow(temp.getNodeCoordinate_z(), 2));
		length_side = temp.norm();
		control = process_node1;
		control.substractNode(obsCentroid);

		//r_plus = sqrt(pow(control.getNodeCoordinate_x(), 2) + pow(control.getNodeCoordinate_y(), 2) + pow(control.getNodeCoordinate_z(), 2));
		r_plus = control.norm();

		control = process_node2;
		control.substractNode(obsCentroid);

		//r_minus = sqrt(pow(control.getNodeCoordinate_x(), 2) + pow(control.getNodeCoordinate_y(), 2) + pow(control.getNodeCoordinate_z(), 2));
		r_minus = control.norm();

		p_plus = process_node1;
		p_plus.substractNode(centroid_on_plane);

		p_minus = process_node2;
		p_minus.substractNode(centroid_on_plane);

		temp = process_node1;
		temp.substractNode(process_node2);

		//distance = sqrt(pow(temp.getNodeCoordinate_x(), 2) + pow(temp.getNodeCoordinate_y(), 2) + pow(temp.getNodeCoordinate_z(), 2));
		distance = temp.norm();

		unit_l = temp;
		unit_l.divideNode(distance);

		l_plus = p_plus.dotProduct(unit_l);
		l_minus = p_minus.dotProduct(unit_l);
		unit_u.crossProduct(unit_l, unit_n);


		p0 = p_plus.dotProduct(unit_u);

		if (p0 < 0) { p0 = p0*(-1); }

		if (p0 < (1e-10)*length_side) { flag = 0; }

		if (flag) {
			//r0 = sqrt(pow(p0, 2) + pow(dot_product, 2));
			r0 = sqrt((p0*p0)+(dot_product*dot_product));
			unit_p = p_plus;
			unit_p.substractWithScaleNode(unit_l, l_plus);

			distance = unit_p.norm();
			unit_p.divideNode(distance);	

			t1 = p0*log((r_plus + l_plus) / (r_minus + l_minus));

			if (p0 < ((1e-6)*length_side)) {

				if (r0 < ((1e-4)*length_side)) { t1 = 0; }
			}

			t2 = std::atan((p0*l_plus) / ((r0*r0) + (dot_product*r_plus)));
			t3 = std::atan((p0*l_minus) / (pow(r0, 2) + (dot_product*r_minus)));
			t4 = unit_p.dotProduct(unit_u);

			momEntry = momEntry + (t4*(t1 - dot_product*(t2 - t3)));
		}
	} 
momEntry = momEntry;
}