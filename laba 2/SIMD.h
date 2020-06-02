#pragma once
#include<ctime>
#include<iostream>
#include"ThreeDimensionalMatrix.h"
#include"TwoDimensionalMatrix.h"

class SIMD {


private:

	enum operationName
	{
		ADD, SUBSTRACT, MULTIPLY, MIN, MULTIPLICATION_F, MULTIPLICATION_D, MIN_AB, MIN_FD, SUP_AB, SUP_BA
	};

	class Subprocessor
	{
	public:
		Subprocessor(int index);
		double run(operationName, double operand1, double operand2);
		
	private:
		int index;
		double add(double operand1, double operand2);
		double substract(double operand1, double operand2);
		double multiply(double operand1, double operand2);
		double min(double operand1, double operand2);

	};
	int subprocessorNumber;
	int runTime;
	int p;
	int q;
	int m;
	int additionTime;
	int substractionTime;
	int multiplicationTime;
	int compairingTime;

	TwoDimensionalMatrix *A;
	TwoDimensionalMatrix *B;
	TwoDimensionalMatrix *E;
	TwoDimensionalMatrix *G;
	ThreeDimensionalMatrix *D;
	ThreeDimensionalMatrix *F;
	TwoDimensionalMatrix* C;


	vector <SIMD::Subprocessor*> subprocessorList;

	void generateTwoDimensionalMatrix(TwoDimensionalMatrix* matrix);

	void switchSubprocessorIndex(int* index);
	void updateTime(const operationName operation);
	ThreeDimensionalMatrix* processThreeDim(const operationName operation, TwoDimensionalMatrix* matrix1, TwoDimensionalMatrix*matrix2);
	ThreeDimensionalMatrix* processThreeDim(const operationName operation, TwoDimensionalMatrix*matrix1, const double value);
	ThreeDimensionalMatrix* processThreeDim(const operationName operation, ThreeDimensionalMatrix*matrix1, const double value);
	ThreeDimensionalMatrix* processThreeDim(const operationName operation, ThreeDimensionalMatrix*matrix1, TwoDimensionalMatrix*matrix2);
	ThreeDimensionalMatrix* processThreeDim(const operationName operation, const double value, TwoDimensionalMatrix*matrix2);
	ThreeDimensionalMatrix* processThreeDim(const operationName operation, ThreeDimensionalMatrix*matrix1, ThreeDimensionalMatrix*matrix2);
	TwoDimensionalMatrix* processTwoDim(const operationName operation, ThreeDimensionalMatrix*matrix1);
	TwoDimensionalMatrix* processTwoDim(const operationName operation, ThreeDimensionalMatrix*matrix1, ThreeDimensionalMatrix*matrix2);///
	TwoDimensionalMatrix* processTwoDim(const operationName operation, TwoDimensionalMatrix*matrix1, const double value);
	TwoDimensionalMatrix* processTwoDim(const operationName operation, TwoDimensionalMatrix*matrix1, TwoDimensionalMatrix*matrix2);
	TwoDimensionalMatrix* processTwoDim(const operationName operation, const double value, TwoDimensionalMatrix*matrix2);
	void equalizeMatrixes(TwoDimensionalMatrix*, TwoDimensionalMatrix*);
	void equalizeMatrixes(ThreeDimensionalMatrix*, ThreeDimensionalMatrix*);
	void calculateDMatrix();
	void calculateFMatrix();
	void calculateCMatrix();
public:

	SIMD();

};
