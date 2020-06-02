#include "ThreeDimensionalMatrix.h"

ThreeDimensionalMatrix::ThreeDimensionalMatrix(int x, int y, int z)
{
	matrix.resize(x);

	this->x = x;

	this->y = y;

	this->z = z;
	for (int i = 0; i < x; i++)
	{
		matrix[i].resize(y);

		for (int j = 0; j < y; j++)
		{
			matrix[i][j].resize(z);
		}
	}

	srand(time(0));

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				matrix[i][j][k] = random();
			}
			
		}
	}
}

double ThreeDimensionalMatrix::getElement(int x, int y, int z)
{
	return matrix[x][y][z];
}

int ThreeDimensionalMatrix::getX()
{
	return x;
}

int ThreeDimensionalMatrix::getY()
{
	return y;
}

int ThreeDimensionalMatrix::getZ()
{
	return z;
}

void ThreeDimensionalMatrix::setElement(int x, int y, int z, double value)
{
	matrix[x][y][z] = value;
}


double ThreeDimensionalMatrix::random()
{
	return  (-999 + rand() % 999) / 1000.0;
}

void ThreeDimensionalMatrix::print()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				cout << fixed << setprecision(3) << "[" << i << "][" << j << "][" << k << "] == " << getElement(i, j, k) << ";     \t";
				if (k % 3 == 0)
				{
					cout << endl;
				}
			}
		}
		cout << endl;
	}
}