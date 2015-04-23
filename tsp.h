#ifndef TSP_H_INCLUDED
#define TSP_H_INCLUDED
//#define DEBUG
#include <vector>
#include <algorithm>
#include "matrix.h"
#include "cycle.h"

class TSP {
public:
    // constructor
	TSP(Matrix2D *m) : ncity(m->length - 1), OriginMatrix(m), UpperBound(INT_MAX), UpperBoundCount(0), TerminateCount(0), TotalCount(0) {}
	~TSP() {}
    void Solve();

private:
	void BnB(Matrix2D *, int); // recursive branch and bound
	void DeleteCycle(Matrix2D *, Path); // remove cycle for inclusion step
	Path FindPath(Matrix2D *); // finding next path
	void PrintPath();

    // data members
    vector<Path> TraveledPath, OptPath; // path that are traveled during running and optimal solution of traveled path
    Matrix2D *OriginMatrix; // origin matrix
    int ncity; // city #
	int UpperBound; // optimal cost
	int UpperBoundCount, TerminateCount, TotalCount; // statistics variables
};

#endif // TSP_H_INCLUDED
