#pragma once
#include "CMscnProblem.h"

class CRandomSearch
{
public:
	CRandomSearch();
	CRandomSearch(CMscnProblem* cProblem);
	~CRandomSearch() { delete problem; }

	Array<double>* search(int numOfTries, int& errCode);

private:

	CMscnProblem *problem;
};