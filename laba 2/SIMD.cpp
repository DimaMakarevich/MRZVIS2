#include "SIMD.h"

SIMD::Subprocessor::Subprocessor(int index)
{
	this->index = index;
}

double SIMD::Subprocessor::run(operationName oparation, double operand1, double operand2)
{
	double result = 0;
	switch (oparation)
	{
	case ADD:
		result = add(operand1, operand2);
		break;
	case SUBSTRACT:
		result = substract(operand1, operand2);
		break;
	case MULTIPLY:
		result = multiply(operand1, operand2);
		break;
	case MIN:
		result = min(operand1, operand2);
		break;
	}
	
	
	return result;
}

double SIMD::Subprocessor::add(double operand1, double operand2)
{
	return operand1 + operand2;
}

double SIMD::Subprocessor::substract(double operand1, double operand2)
{
	return  operand1 - operand2;
}

double SIMD::Subprocessor::multiply(double operand1, double operand2)
{
	return operand1 * operand2;
}

double SIMD::Subprocessor::min(double operand1, double operand2)
{
	return operand1 <= operand2 ? operand1 : operand2;
}

SIMD::SIMD()
{
	cout << "Input subprocessor number: ";
	cin >> this->subprocessorNumber;
	subprocessorList.resize(subprocessorNumber);
	for (int i = 0; i < subprocessorNumber; i++)
	{
		subprocessorList[i] = new Subprocessor(i);
	}

	cout << "Input addition time: ";
	cin >> additionTime;
	cout << "Input substraction time: ";
	cin >> substractionTime;
	cout << "Input multiplication time: ";
	cin >> multiplicationTime;
	cout << "Input compairing time: ";
	cin >> compairingTime;
	cout << "Input p: ";
	cin >> p;
	cout << "Input q: ";
	cin >> q;
	cout << "Input m: ";
	cin >> m;

	A = new TwoDimensionalMatrix(p, m);
	//generateTwoDimensionalMatrix(A);
	B = new TwoDimensionalMatrix(m, q);
	//generateTwoDimensionalMatrix(B);
	E = new TwoDimensionalMatrix(1, m);
	//generateTwoDimensionalMatrix(E);
	G = new TwoDimensionalMatrix(p, q);
	//generateTwoDimensionalMatrix(G);



	cout << "Do you want to print initial matrixes(A, B, E, G)?(y -- yes)";
	string inputString;
	cin >> inputString;
	if (inputString == "y")
	{
		cout << "matrix A:\n";
		A->print();
		cout << "matrix B:\n";
		B->print();
		cout << "matrix E:\n";
		E->print();
		cout << "matrix G:\n";
		G->print();
	}

	calculateDMatrix();

	cout << "Do you want to print D matrix?(y -- yes)";
	cin >> inputString;
	if (inputString == "y")
	{
		cout << "matrix D:\n";
		D->print();
	}

	calculateFMatrix();
	cout << "Do you want to print F matrix?(y -- yes)";
	cin >> inputString;
	if (inputString == "y")
	{
		cout << "matrix F:\n";
		F->print();
	}

	calculateCMatrix();
	cout << "Do you want to print C matrix?(y -- yes)";
	cin >> inputString;
	if (inputString == "y")
	{
		cout << "matrix C:\n";
		C->print();
	}

}

void SIMD::equalizeMatrixes(TwoDimensionalMatrix *matrix1, TwoDimensionalMatrix *matrix2)
{
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			matrix1->setElement(i, j, matrix2->getElement(i, j));
		}
	}

}

void SIMD::equalizeMatrixes(ThreeDimensionalMatrix *matrix1, ThreeDimensionalMatrix *matrix2)
{

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				matrix1->setElement(i, j, k, matrix2->getElement(i, j, k));
			}
		}
	}
}

void SIMD::calculateDMatrix()
{
	D = processThreeDim(MULTIPLY, A, B);
}

void SIMD::calculateFMatrix()
{
	vector<ThreeDimensionalMatrix*> buffer(3, new ThreeDimensionalMatrix(p, q, m));

	buffer[1] = processThreeDim(SUP_AB, A, B);
	buffer[2] = processThreeDim(MULTIPLY, E, 2);
	buffer[2] = processThreeDim(SUBSTRACT, buffer[2], 1);
	buffer[1] = processThreeDim(MULTIPLY, buffer[1], buffer[2]);
	buffer[1] = processThreeDim(MULTIPLY, buffer[1], E);

	equalizeMatrixes(buffer[0], buffer[1]);

	buffer[1] = processThreeDim(SUP_BA, B, A);
	buffer[2] = processThreeDim(SUP_AB, A, B);
	buffer[2] = processThreeDim(MULTIPLY, buffer[2], 4);
	buffer[2] = processThreeDim(SUBSTRACT, buffer[2], 2);
	buffer[2] = processThreeDim(MULTIPLY, buffer[2], E);
	buffer[2] = processThreeDim(ADD, buffer[2], 1);
	buffer[1] = processThreeDim(MULTIPLY, buffer[1], buffer[2]);
	buffer[2] = processThreeDim(SUBSTRACT, 1, E);
	buffer[1] = processThreeDim(MULTIPLY, buffer[1], buffer[2]);
	buffer[0] = processThreeDim(ADD, buffer[0], buffer[1]);

	F = buffer[0];

}

void SIMD::calculateCMatrix()
{
	vector<TwoDimensionalMatrix*> buffer(4, new TwoDimensionalMatrix(p, q));

	buffer[1] = processTwoDim(MULTIPLICATION_F, F);
	buffer[2] = processTwoDim(MULTIPLY, G, 3);
	buffer[2] = processTwoDim(SUBSTRACT, buffer[2], 2);
	buffer[1] = processTwoDim(MULTIPLY, buffer[1], buffer[2]);
	buffer[1] = processTwoDim(MULTIPLY, buffer[1], G);
	equalizeMatrixes(buffer[0], buffer[1]);

	buffer[1] = processTwoDim(MULTIPLICATION_D, D);
	buffer[2] = processTwoDim(MULTIPLICATION_F, F);
	buffer[3] = processTwoDim(MULTIPLICATION_D, D);
	buffer[2] = processTwoDim(MIN, buffer[2], buffer[3]); /// тут метод мин вместо умножения 
	buffer[2] = processTwoDim(MULTIPLY, buffer[2], 4);
	buffer[3] = processTwoDim(MULTIPLICATION_D, D);
	buffer[3] = processTwoDim(MULTIPLY, buffer[3], 3);
	buffer[2] = processTwoDim(SUBSTRACT, buffer[2], buffer[3]);
	buffer[2] = processTwoDim(MULTIPLY, buffer[2], G);
	buffer[1] = processTwoDim(ADD, buffer[1], buffer[2]);
	buffer[2] = processTwoDim(SUBSTRACT, 1, G);
	buffer[1] = processTwoDim(MULTIPLY, buffer[1], buffer[2]);
	buffer[0] = processTwoDim(ADD, buffer[0], buffer[1]);

	C = buffer[0];
}

void SIMD::generateTwoDimensionalMatrix(TwoDimensionalMatrix * matrix) // нужен ли метод?
{
	srand(time(0));

	for (int i = 0; i < matrix->getX(); i++)
	{
		for (int j = 0; j < matrix->getY(); j++)
		{
			matrix->setElement(i, j, (double)rand() / RAND_MAX * 2 - 1);
		}
	}
}

void SIMD::switchSubprocessorIndex(int *index)
{
	if (*index < subprocessorNumber - 1)
	{
		(*index)++;
	}
	else
	{
		*index = 0;
	}
}

void SIMD::updateTime(const operationName operation)
{
	switch (operation)
	{
	case ADD:
		runTime += additionTime;
		break;
	case SUBSTRACT:
		runTime += substractionTime;
		break;
	case MULTIPLY:
		runTime += multiplicationTime;
		break;
	case MIN:
		runTime += compairingTime;
		break;
	default:
		break;

	}
}

ThreeDimensionalMatrix * SIMD::processThreeDim(const operationName operation, TwoDimensionalMatrix *matrix1, TwoDimensionalMatrix *matrix2)
{
	
	int subprocessorIndex = 0;
	double buffer;
	ThreeDimensionalMatrix *resultMatrix = new ThreeDimensionalMatrix(p, q, m); 

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				case MULTIPLY:
					resultMatrix->setElement(i,j,k,
						subprocessorList[subprocessorIndex]->run(MULTIPLY, matrix1->getElement(i, k), matrix2->getElement(k, j)));
					switchSubprocessorIndex(&subprocessorIndex);
					break;




				case MIN_AB:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(MIN, matrix1->getElement(i, k), matrix2->getElement(k, j)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MIN);
					break;
				case SUP_AB:
					buffer = subprocessorList[subprocessorIndex]->run(MULTIPLY, 1 - matrix1->getElement(i, k), 0);
					updateTime(MULTIPLY);
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(MIN, buffer, matrix2->getElement(k, j)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MIN);
					break;
				case SUP_BA:
					buffer = subprocessorList[subprocessorIndex]->run(MULTIPLY, 1 - matrix1->getElement(k, j), 0);
					updateTime(MULTIPLY);
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(MIN, buffer, matrix2->getElement(i, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MIN);
					break;
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, matrix1->getElement(i, k), matrix2->getElement(k, j)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}
	
	
	
	
	return resultMatrix;
}

ThreeDimensionalMatrix * SIMD::processThreeDim(const operationName operation, TwoDimensionalMatrix * matrix1, const double value)
{
	int subprocessorIndex = 0;
	ThreeDimensionalMatrix* resultMatrix = new ThreeDimensionalMatrix(p, q, m);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, matrix1->getElement(0, k), value));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}

	return resultMatrix;
}

ThreeDimensionalMatrix * SIMD::processThreeDim(const operationName operation, ThreeDimensionalMatrix * matrix1, const double value)
{
	int subprocessorIndex = 0;
	ThreeDimensionalMatrix* resultMatrix = new ThreeDimensionalMatrix(p, q, m);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, matrix1->getElement(i, j, k), value));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}

	return resultMatrix;
}

ThreeDimensionalMatrix * SIMD::processThreeDim(const operationName operation, ThreeDimensionalMatrix * matrix1, TwoDimensionalMatrix * matrix2)
{
	int subprocessorIndex = 0;
	ThreeDimensionalMatrix* resultMatrix = new ThreeDimensionalMatrix(p, q, m);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, matrix1->getElement(i, j, k), matrix2->getElement(0, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}

	return resultMatrix;
}

ThreeDimensionalMatrix * SIMD::processThreeDim(const operationName operation, const double value, TwoDimensionalMatrix * matrix2)
{
	 int subprocessorIndex = 0;
	ThreeDimensionalMatrix* resultMatrix = new ThreeDimensionalMatrix(p, q, m);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, value, matrix2->getElement(0, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}

	return resultMatrix;
}

ThreeDimensionalMatrix * SIMD::processThreeDim(const operationName operation, ThreeDimensionalMatrix * matrix1, ThreeDimensionalMatrix * matrix2)
{
	int subprocessorIndex = 0;
	ThreeDimensionalMatrix* resultMatrix = new ThreeDimensionalMatrix(p, q, m);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, matrix1->getElement(i, j, k), matrix2->getElement(i, j, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}

	return resultMatrix;
}

TwoDimensionalMatrix * SIMD::processTwoDim(const operationName operation, ThreeDimensionalMatrix * matrix1)
{
	int subprocessorIndex = 0;
	TwoDimensionalMatrix* resultMatrix = new TwoDimensionalMatrix(p, q);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			switch (operation)
			{
			case MULTIPLICATION_F:
				for (int k = 0; k < m; k++)
				{
					resultMatrix->setElement(i, j,
						subprocessorList[subprocessorIndex]->run(MULTIPLY, resultMatrix->getElement(i, j), matrix1->getElement(i, j, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MULTIPLY);
				}
				break;
			case MULTIPLICATION_D:
				for (int k = 0; k < m; k++)
				{
					resultMatrix->setElement(i, j,
						subprocessorList[subprocessorIndex]->run(MULTIPLY, resultMatrix->getElement(i, j), 1 - matrix1->getElement(i, j, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MULTIPLY);
				}

				resultMatrix->setElement(i, j, 1 - resultMatrix->getElement(i, j));
				updateTime(SUBSTRACT);
				break;
			}
		}
	}

	return resultMatrix;
}

TwoDimensionalMatrix * SIMD::processTwoDim(const operationName operation, ThreeDimensionalMatrix * matrix1, ThreeDimensionalMatrix * matrix2)// минимум сделать
{
	int subprocessorIndex = 0;
	TwoDimensionalMatrix* resultMatrix = new TwoDimensionalMatrix(p, q);
	TwoDimensionalMatrix* buffer1 = new TwoDimensionalMatrix(p, q);
	TwoDimensionalMatrix* buffer2 = new TwoDimensionalMatrix(p, q);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			switch (operation)
			{
			case MIN_FD:
				for (int k = 0; k < m; k++)
				{
					buffer1 = processTwoDim(MULTIPLICATION_F, F);
					buffer2 = processTwoDim(MULTIPLICATION_D, D);
					resultMatrix->setElement(i, j,
						subprocessorList[subprocessorIndex]->run(MIN, buffer1->getElement(i, j), buffer2->getElement(i, j)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MIN);
				}
				break;
			}
		}
	}

	return resultMatrix;
}

TwoDimensionalMatrix * SIMD::processTwoDim(const operationName operation, TwoDimensionalMatrix * matrix1, const double value)
{
	int subprocessorIndex = 0;
	TwoDimensionalMatrix* resultMatrix = new TwoDimensionalMatrix(p, q);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			switch (operation)
			{
			default:
				resultMatrix->setElement(i, j,
					subprocessorList[subprocessorIndex]->run(operation, matrix1->getElement(i, j), value));
				switchSubprocessorIndex(&subprocessorIndex);
				updateTime(operation);
				break;
			}
		}
	}

	return resultMatrix;
}

TwoDimensionalMatrix * SIMD::processTwoDim(const operationName operation, TwoDimensionalMatrix * matrix1, TwoDimensionalMatrix * matrix2)
{
	int subprocessorIndex = 0;
	TwoDimensionalMatrix* resultMatrix = new TwoDimensionalMatrix(p, q);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			switch (operation)
			{
			default:
				resultMatrix->setElement(i, j,
					subprocessorList[subprocessorIndex]->run(operation, matrix1->getElement(i, j), matrix2->getElement(i, j)));
				switchSubprocessorIndex(&subprocessorIndex);
				updateTime(operation);
				break;
			}
		}
	}

	return resultMatrix;
}

TwoDimensionalMatrix * SIMD::processTwoDim(const operationName operation, const double value, TwoDimensionalMatrix * matrix2)
{
	int subprocessorIndex = 0;
	TwoDimensionalMatrix* resultMatrix = new TwoDimensionalMatrix(p, q);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			switch (operation)
			{
			default:
				resultMatrix->setElement(i, j,
					subprocessorList[subprocessorIndex]->run(operation, value, matrix2->getElement(i, j)));
				switchSubprocessorIndex(&subprocessorIndex);
				updateTime(operation);
				break;
			}
		}
	}

	return resultMatrix;
}
