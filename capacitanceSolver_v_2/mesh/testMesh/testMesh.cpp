// testMesh.cpp : Defines the entry point for the console application.
#include<Windows.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "node.h"
//v_2//
#include "patch.h"
#include "mesh.h"
using namespace std;

//void startProgram(string file) {
//	ShellExecute(NULL, "open", file.c_str(), NULL, NULL, SW_SHOWNORMAL);
//}
int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	clock_t start, end;
	start = clock();
	mesh m;
	m.nodeListSize();
	m.readNodeList(); //m.nodeListReadError();
	m.patchListSize();
	m.readPatchList();
	m.findNumNets();

	//node n1, n2, n3, n4, n6;
	//node n5;
	//int my5 = 5;
	//n1 = node(4, 6, 8, 1); n2 = node(1, 5, 10, 2); n3 = node(1, 1, 0, 2);
	//
	////n1 = node(0, 0, 0); n2 = node(6, 0, 0); n3 = node(3, 3, 0);
	////n1 = node(0, 0, 0); n2 = node(6, 0, 0); n3 = node(6, 8, 0);
	////n1 = node(0, 0, 0); n2 = node(6, 0, 0); n3 = node(0, 8, 0);
	////n1.crossProduct(&n2, &n3);
	////n1.dotProduct(&n2);
	////n1.norm();
	////FILE* fi;
	////n1.readNode(fi);

	//patch p;
	//n4 = n1 + &n2;
	//n5 = n1 - n2;
	//n6 = n1 - &n2;

	////n6 = n5 * 5;
	//n1.dotProduct(n2);
	//p.fillCentroid(&n1, &n2, &n3);
	//p.fillSevenPoints(&n1, &n2, &n3);
	//p.fillArea(&n1, &n2, &n3);
	//p.fillMaxLength(&n1, &n2, &n3);
	//p.setNormal(&n1, &n2, &n3);
	////p.setNormal();
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

	end = clock();
	double time = end - start;
	cout << "Time for Execution  " << time << " Micro Seconds" << endl;
	//startProgram("mspaint");

	system("pause");
	//getchar();
}