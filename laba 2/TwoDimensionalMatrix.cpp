#include "TwoDimensionalMatrix.h"

double TwoDimensionalMatrix::random()
{
	return  (-999 + rand() % 999 ) / 1000.0;
}

void TwoDimensionalMatrix::print()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			cout << fixed << setprecision(3) << "[" << i << "][" << j << "] == " << getElement(i, j) << ";   \t";
			if (j % 3 == 0)
			{
				cout << endl;
			}
		}
		cout << endl;
	}
}

TwoDimensionalMatrix::TwoDimensionalMatrix(int x, int y)
{
	matrix.resize(x);

	this->x = x;

	this->y = y;
	
	for (int i = 0; i < x; i++)
	{
		matrix[i].resize(y);
	}
	
	srand(time(0));


	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			matrix[i][j] = random();
		}
	}
	
}

double TwoDimensionalMatrix::getElement(int x, int y)
{
	return matrix[x][y];
}

int TwoDimensionalMatrix::getX()
{
	return x;
}

int TwoDimensionalMatrix::getY()
{
	return y;
}

void TwoDimensionalMatrix::setElement(int x, int y, double value)
{
	matrix[x][y] = value;
}