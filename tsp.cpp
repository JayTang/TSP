#include "tsp.h"
// O(??)
void TSP::BnB(Matrix2D *Origin, int LowerBound) {

#ifdef DEBUG
    cout << "======================================" << endl;
    Origin->Print();
#endif

	LowerBound += Origin->Reduce(); // reduce matrix

#ifdef DEBUG
    Origin->Print();
    cout << "cost = " << LowerBound << ", opt = ";
    if (UpperBound == INT_MAX) cout << "¡Û" << endl;
    else cout << UpperBound << endl;
#endif

#ifndef DEBUG
    cout << ".";
#endif

    TotalCount++;

    // terminate
	if (LowerBound >= UpperBound) {
        TerminateCount++;
#ifndef DEBUG
        cout << "x";
#endif
		return;
	}

    // update upper bound
    if (Origin->length == 2) {
        if (LowerBound < UpperBound) {
#ifndef DEBUG
            cout << "u";
#endif
            UpperBoundCount++;
            UpperBound = LowerBound;
#ifdef DEBUG
            cout << "update OptCost = " << UpperBound << endl;
#endif
            OptPath = vector<Path>(TraveledPath);
            return;
        }
#ifndef DEBUG
        cout << "x";
#endif
        return;
    }

    // find path
	Path VirtualPath = FindPath(Origin);
	Path RealPath(Origin->matrix[VirtualPath.row][0], Origin->matrix[0][VirtualPath.column]);

#ifdef DEBUG
    cout << "Path = " << RealPath.row << "(index " << VirtualPath.row << ") " << RealPath.column << "(index " << VirtualPath.column << ")" << endl;
#endif

	// include
    Matrix2D *shrink = Origin->Shrink(VirtualPath.row, VirtualPath.column);
    DeleteCycle(shrink, RealPath);
    TraveledPath.push_back(RealPath);
    BnB(shrink, LowerBound);
    TraveledPath.pop_back();
    delete shrink;


    // exclude
    Matrix2D *clone = Origin->Clone();
    clone->matrix[VirtualPath.row][VirtualPath.column] = INT_MAX;
    BnB(clone, LowerBound);
    delete clone;

#ifndef DEBUG
    cout << "-";
#endif
}

// need to be improved O(n)
void TSP::DeleteCycle(Matrix2D *m, Path p) {
    // find cycle
    int row = p.column, column = p.row;
    bool flag = true;
    while (flag) {
        flag = false;
        for (vector<Path>::iterator it = TraveledPath.begin() ; it != TraveledPath.end(); it++) {
            if (p.row == it->column) {
                p.row = it->row;
                column = it->row;
                flag = true;
            }
            if (p.column == it->row) {
                p.column = it->column;
                row = it->column;
                flag = true;
            }
        }
    }

    // find cycle index
    int r = -1, c = -1;
    for (int i = 0; i < m->length; i++) {
        if (m->matrix[i][0] == row) r = i;
        if (m->matrix[0][i] == column) c = i;
    }

#ifdef DEBUG
    cout << "cycle " << row << "(index = " << r << ") " << column << "(index = " << c << ")" << endl;
#endif // DEBUG
    // delete cycle
    if (r != -1 && c != -1)
        m->matrix[r][c] = INT_MAX;
}

// should be able to improved O(n^3)
Path TSP::FindPath(Matrix2D *m) {
    int maximun = -1;
    Path p(0, 0);
    for (int i = 1; i < m->length; i++) {
        for (int j = 1; j < m->length; j++) {
            int total = 0;
            if (m->matrix[i][j] == 0) {
                // row
                int minimum = INT_MAX;
                for (int k = 1; k < m->length; k++)
                    if (k != j && m->matrix[i][k] < minimum)
                        minimum = m->matrix[i][k];
                if (minimum != INT_MAX)
                    total += minimum;

                // column
                minimum = INT_MAX;
                for (int k = 1; k < m->length; k++)
                    if (k != i && m->matrix[k][j] < minimum)
                        minimum = m->matrix[k][j];
                if (minimum != INT_MAX)
                    total += minimum;

                // update path with larger cost
                if (total > maximun) {
                    maximun = total;
                    p = Path(i, j);
                }
            }
        }
    }
    return p;
}

// O(n)
void TSP::PrintPath() {
    // find first and last path
    sort(OptPath.begin(), OptPath.end());
    int first = 0, last = 0;
    for (vector<Path>::iterator it = OptPath.begin() ; it != OptPath.end(); it++) {
#ifdef DEBUG
        cout << it->row << "->" << it->column << endl;
#endif
        first += it->column;
        last += it->row;
    }
    int sum = (ncity + 1) * ncity / 2;
    int s = sum - first, e = sum - last, skip;

#ifdef DEBUG
    cout << "s = " << s << ", e = " << e << endl;
#endif

    for (int i = 0; i < OptPath.size(); i++) {
        s > e ? skip = 2 : skip = 1;
        if (i == 0) cout << OptPath[s-skip].row << "->" << OptPath[s-skip].column;
        else cout << "->" << OptPath[s-skip].column;
        s = OptPath[s-skip].column;
    }
    cout << endl;
}

void TSP::Solve() {
#ifndef DEBUG
    OriginMatrix->Print();
#endif
    BnB(OriginMatrix, 0);

    // output answer & statistics
    cout << endl << endl << "Optimal Cost = " << UpperBound << endl;
    cout << "Total = " << TotalCount << endl;
    cout << "Updated = " << UpperBoundCount << endl;
    cout << "Terminated = " << TerminateCount << endl;

    // print path
    PrintPath();
}


