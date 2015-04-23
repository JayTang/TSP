#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <ctime>

using namespace std;

class Matrix2D {
public:
    // constructor & destructor
    Matrix2D(int);
    ~Matrix2D();

    // member functions
    Matrix2D *Clone();
    Matrix2D *Shrink(int, int);
    void Print();
    void LoadData();
    void RandomizeData(int, int);
    int Reduce();

    // data members
    int **matrix;
    int length;
};

#endif // MATRIX_H_INCLUDED
