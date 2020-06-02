#pragma once

#include<vector>
#include<ctime>
#include<iostream>
#include<string>
#include <iomanip>

using namespace std;


class ThreeDimensionalMatrix {

	vector <vector <vector<double>>> matrix;

	double random();
	int x, y, z;


public:
	double getElement(int, int, int);
	int getX();
	int getY();
	int getZ();
	void setElement(int, int, int, double);
	void print();
	ThreeDimensionalMatrix(int x, int y, int z);
};