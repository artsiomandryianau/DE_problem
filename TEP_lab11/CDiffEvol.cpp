#include "pch.h"
#include "CDiffEvol.h"
#include <iostream>
#include <fstream>



CDiffEvol::CDiffEvol(CMscnProblem * _problem, int _populationSize)
{
	problem = _problem;
	populationSize = _populationSize;
	genotypeSize = problem->getSolutionSize();
}

CDiffEvol::~CDiffEvol()
{
}

void CDiffEvol::initPopulation()
{
	int errCode = 0;
	population = new double*[populationSize];
	double best = 0;
	for (int i = 0; i < populationSize; i++) {
		population[i] = (problem->generateSolution(errCode))->getTable();
	}


}

bool CDiffEvol::checkStopCondition(int counter)
{
	return counter == 500;
}

double * CDiffEvol::getRandomInd()
{
	CRandom random;
	int index = random.getRandomInt(0, populationSize - 1);
	return population[index];
}


bool CDiffEvol::individualsAreDifferent(double * ind, double * baseInd, double * addInd0, double * addInd1) {

	int similarity = 0;

	double dIndActualNumber = 0.0;
	double dBaseIndActualNumber = 0.0;
	double dAddInd0ActualNumber = 0.0;
	double dAddInd1ActualNumber = 0.0;

	for (int i = 0; i < problem->getSolutionSize(); i++) {
		dIndActualNumber = ind[0];
		dBaseIndActualNumber = baseInd[0];
		dAddInd0ActualNumber = addInd0[0];
		dAddInd1ActualNumber = addInd1[0];

		if ((dIndActualNumber == dBaseIndActualNumber) && (dIndActualNumber == dAddInd0ActualNumber) && (dIndActualNumber == dAddInd1ActualNumber) 
			&& (dBaseIndActualNumber == dAddInd0ActualNumber) && (dBaseIndActualNumber == dAddInd1ActualNumber) && (dAddInd0ActualNumber == dAddInd1ActualNumber))
			similarity++;
	}

	return similarity != (problem->getSolutionSize());
}

double* CDiffEvol::search()
{
	initPopulation();
	int max = 0;
	int counter = 0;
	int errCode = 0;

	double diffWeight = 0.2;
	double crossProb = 0.8;

	CRandom random;
	double* ind;
	double* baseInd;
	double* addInd0;
	double* addInd1;

	double* result = new double[genotypeSize];

	double* indNew;
	indNew = new double[genotypeSize];

	while (checkStopCondition(counter) == false) {
		for (int i = 0; i < populationSize; i++) {
			ind = population[i];
			baseInd = getRandomInd();
			addInd0 = getRandomInd();
			addInd1 = getRandomInd();
			if (individualsAreDifferent(ind, baseInd, addInd0, addInd1)) {
				indNew = new double[genotypeSize];
				for (int geneOffset = 0; geneOffset < genotypeSize; geneOffset++) {
					if (random.getRandomDouble(0, 1) < crossProb) {
						indNew[geneOffset] = baseInd[geneOffset] + diffWeight * (addInd0[geneOffset] - addInd1[geneOffset]);
					}
					else {
						indNew[geneOffset] = ind[geneOffset];
					}
				}

				if (problem->dGetQuality(indNew, errCode) >= problem->dGetQuality(ind, errCode) && problem->bConstraintsSatisfied(indNew, errCode) && population[i] != indNew) {
					population[i] = indNew;

					if (problem->dGetQuality(indNew, errCode) > max &&problem->bConstraintsSatisfied(indNew, errCode)) {
						max = problem->dGetQuality(indNew, errCode);
						errCode = 0;
						for (int l = 0; l < genotypeSize; l++) {
							result[l] = indNew[l];
						}
					}
				}

			}
		}
		counter++;
		//saveQualitiesToFile();
	}


	return result;
}
void CDiffEvol::saveQualitiesToFile()
{

	int errCode = 0;
	std::ofstream file;
	file.open("differentialEvolution.txt", std::ios::app);
	if (file.is_open())
	{
		for (int i = 0; i < populationSize - 1; i++)
		{
			file << problem->dGetQuality(population[i], errCode);
			file << ',';
		}
		file << problem->dGetQuality(population[populationSize - 1], errCode);
		file << "\n";
	}
}