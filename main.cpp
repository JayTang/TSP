#include "tsp.h"
int main()
{
    int ncity;
    cin >> ncity;
    Matrix2D origin(ncity + 1);
    origin.RandomizeData(1, 100);
    //origin.LoadData();

    TSP tsp(&origin);
    tsp.Solve();

    return 0;
}
