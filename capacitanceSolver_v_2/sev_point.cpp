#include "sev_point.h"
#include <math.h>
double sev_point::cal_integ(patch& p,node& test_centroid)
{
	std::vector<node*> source_node;
	std::vector<double> test_centroid_cords , alpha , beta , weight , r;
	std::vector<double> source_node1_cords , source_node2_cords , source_node3_cords , node1_1 , node2_2;
	double& source_area = p.get_area();
	double integral = 0.0 , dummy;
	alpha.resize(7);
	alpha[0] = 0.3333333; alpha[1] = 0.0597158; alpha[2] =  0.470142; alpha[3] = 0.470142; alpha[4] = 0.7974269; alpha[5] = 0.1012865; alpha[6] = 0.1012865;
	beta.resize(7);
	beta[0] = 0.3333333; beta[1] = 0.470142; alpha[2] =  0.0597158; alpha[3] = 0.470142; alpha[4] = 0.1012865; alpha[5] = 0.7974269; alpha[6] = 0.1012865;
	weight.resize(7);
	weight[0] = 0.225; weight[1] = 0.13239415278851; weight[2] = 0.13239415278851; weight[3] = 0.13239415278851; weight[4] = 0.12593918054483; weight[5] = 0.12593918054483; weight[6] = 0.12593918054483;
	r.resize(3);
	test_centroid_cords.resize(3);
	source_node.resize(3);
	source_node1_cords.resize(3);
	source_node2_cords.resize(3);
	source_node3_cords.resize(3);
	node1_1.resize(3);
	node2_2.resize(3);
	source_node = p.get_node();
	source_node1_cords = source_node[0]->get_cords();
	source_node2_cords = source_node[1]->get_cords();
	source_node3_cords = source_node[2]->get_cords();
	test_centroid_cords = test_centroid.get_cords();
	for(int i = 0; i < 3; i++)
	{
		node1_1[i] = source_node2_cords[i] - source_node1_cords[i];
		node2_2[i] = source_node3_cords[i] - source_node1_cords[i];
	}
	for(int i = 0; i < 7; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			r[j] = alpha[i] * node1_1[j] + beta[i] * node2_2[j] + source_node1_cords[j];
			r[j] = test_centroid_cords[j] - r[j];
		}
		dummy = 1/sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
		integral = integral + weight[i] * dummy;
	}
	integral = integral * source_area;
	return(integral);
}

