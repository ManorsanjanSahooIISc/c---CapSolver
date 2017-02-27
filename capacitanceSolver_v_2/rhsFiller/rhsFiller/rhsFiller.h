//v_2//
#ifndef  RHSFILLER_H_
#define RHSFILLER_H_
#pragma once

#include <iostream>
#include<vector>
#include<fstream>
#include<string>

#include "../../mesh/mesh/node.h"
#include "../../mesh/mesh/patch.h"
#include "../../mesh/mesh/mesh.h"
#include "../../integration/integration/integration.h"
#include "../../matrix/matrix/matrix.h"

using namespace std;

class rhsFiller {
private:

public:
	void fillRhs(std::vector<double>&, std::vector<patch>&, int, int);
};

#endif // ! RHSFILLER_H_

