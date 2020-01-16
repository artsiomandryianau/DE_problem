#pragma once
#include "CMscnProblem.h"
#include "Array.h"
#include "Matrix.h"
#include "CRandom.h"

class CDiffEvol {
public:
	CDiffEvol(CMscnProblem* _problem, int populationSize);
	~CDiffEvol();
	void initPopulation();
	bool checkStopCondition(int counter);
	double* getRandomInd();
	bool individualsAreDifferent(double* ind, double* baseInd, double* addInd0, double* addInd1);
	double* search();

	void saveQualitiesToFile();

private:
	double** population;
	int populationSize;
	int genotypeSize;
	CMscnProblem* problem;
};