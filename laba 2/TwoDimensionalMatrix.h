#pragma once

#include<vector>
#include<ctime>
#include<iostream>
#include <iomanip>

using namespace std;

class TwoDimensionalMatrix {

private:

	int x, y;

	vector <vector<double>> matrix;
	double random();


public:

	double getElement(int x, int y);
	void setElement(int x, int y, double value);
	int getX();
	int getY();
	 void print();
	TwoDimensionalMatrix(int x, int y);
};