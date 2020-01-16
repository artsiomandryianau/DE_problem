#include "pch.h"
#include "CMscnProblem.h"
#include "ErrorCodes.h"
#include "CRandom.h"
#include "CMscnProblem.h"
#include "CRandomSearch.h"
#include "CDiffEvol.h"
#include <iostream>


int main() {
	int errCode = IS_OK;
	CMscnProblem* problem;
	problem = new CMscnProblem(2, 2, 2, 2);
	problem->vGenerateInstance(5, errCode);
	problem->printProblem();
	std::cout << "\n\n-------------------------------------------------------------\n\n";

	CRandomSearch rsearch(problem);
	problem->setSolution(rsearch.search(10000, errCode), errCode);

	std::cout << "\nSOLUTION: \n";
	problem->getSolution(errCode)->printArray();
	std::cout << "\nQUALITY: \n";
	std::cout << problem->dGetQuality(problem->getSolution(errCode)->getTable(), errCode);
	std::cout << "\nCONSTRAINTS SATISFIED: \n";
	std::cout << problem->bConstraintsSatisfied(problem->getSolution(errCode)->getTable(), errCode);

	std::cout << "\n\n-------------------------------------------------------------\n\n";

	CDiffEvol diffEvol(problem, 50);
	double* solutionDiffEvol = diffEvol.search();
	std::cout << "\nSOLUTION: \n";
	for (int i = 0; i < problem->getSolutionSize(); i++) {
		std::cout << "  " << solutionDiffEvol[i];
	}
	std::cout << "\nQUALITY: \n";
	std::cout << problem->dGetQuality(solutionDiffEvol, errCode);
	std::cout << "\nCONSTRAINTS SATISFIED: \n";
	std::cout << problem->bConstraintsSatisfied(solutionDiffEvol, errCode);
}