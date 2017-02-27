//v_2//
#include "rhsFiller.h"

void rhsFiller::fillRhs(std::vector<double>& rhs, std::vector<patch>& patchList, int numPatches, int bodyNo) {

	//FILE *(cppRhs);
	//cppRhs = fopen("cppRhs.txt", "w");

	int body;
	//int b;
	for (int pat = 0; pat < numPatches; pat++) {

		body = patchList[pat].getNetNumber();
		if (body == bodyNo){
			rhs[pat] = 1;
		//	b = rhs[pat];
		}
		else{
			rhs[pat] = 0;
			//b = rhs[pat];
		}
		//fprintf(cppRhs, "%f",b);
		//fprintf(cppRhs, "\n");
	}
	//fclose(cppRhs);
}