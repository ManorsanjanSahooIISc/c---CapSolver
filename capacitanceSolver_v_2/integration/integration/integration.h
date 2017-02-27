
//Integration H//

#ifndef INTEGRATION_H_
#define INTEGRATION_H_
#pragma once
#include<iostream>
#include<vector>
#include <string>

#include "../../mesh/mesh/mesh.h"
#include "../../mesh/mesh/node.h"
#include "../../mesh/mesh/patch.h"
#include "../../../10.3/include/mkl.h"
#include "../../../10.3/include/mkl_blas.h"
#include "../../../10.3/include/mkl_blacs.h"
#include "../../../10.3/include/mkl_lapack.h"


class integration {
private:
	patch srcPatch;
	patch obsPatch;
	node obsCentroid;
	std::vector <node> src;
	std::vector <node> srcSevenPoints;
	double momEntry;
	node centroid_on_plane;
	node copy_node1;
	node copy_node2;
	node copy_node3;
	node diff2;
	node diff1;
	node diff0;

	int obsMatrix;
	node dummy;
	double area_source, dot_product, length_side;
	double r_plus, r_minus;
	double distance;
	//double momEntry[3];
	double l_plus, l_minus;
	double p0, p0_prime;
	double r0, sq_r0;
	double t1, t1_prime;
	double t2, t2_prime;
	double t3, t3_prime;
	double t4, t4_prime;

	node srcCentroid;
	double onePoint;
	node Area0, Area1, Area2;
	node array_area;
	node unit_n;
	node temp;
	node p_plus, p_minus;
	node control;
	node temps;
	node sevPtRes;
	node unit_l, unit_u, unit_p;
	node process_node1, process_node2;
	node rho_res;
	node perp_res;
	node integ;
	node l;

public:

	integration() {};
	void setPatchListNodeList(patch&, patch&, node&);
	void integration::setObsPoint(node&);
	double integrationSevenPoint();
	double integrationOnePoint();
	double integrationAnalytical();
	void setIntegration();
	double greensfunction(node&, node&);
	//node& greensfunctionv(node&, node&);

	~integration() {};
};
#endif // !INTEGRATION_H_