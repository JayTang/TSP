#include "matrix.h"

Matrix2D::Matrix2D(int n) {
    length = n;
    matrix = new int*[length]();
    for (int i = 0; i < length; i++)
        matrix[i] = new int[length]();
}

Matrix2D::~Matrix2D() {
    for(int i = 0; i < length; i++)
        delete [] matrix[i];
    delete [] matrix;
}

// O(n^2)
Matrix2D *Matrix2D::Clone() {
    Matrix2D *clone = new Matrix2D(length);
     for (int i = 0; i < length; i++)
        for (int j = 0; j < length; j++)
            clone->matrix[i][j] = matrix[i][j];
	return clone;
}

// O(n^2)
Matrix2D *Matrix2D::Shrink(int row, int column) {
    Matrix2D *shrink = new Matrix2D(length - 1);
	int skiprow = 0;
    for (int i = 0; i < length; i++) {
        if (i == row) continue;
        if (i > row) skiprow = 1;
        int skipcolumn = 0;
        for (int j = 0; j < length; j++) {
            if (j == column) continue;
            if (j > column) skipcolumn = 1;
            shrink->matrix[i-skiprow][j-skipcolumn] = matrix[i][j];
        }
    }
	return shrink;
}

// O(n^2)
void Matrix2D::Print() {
    for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
		    if (i == 0 && j == 0) cout << "    ";
            else if (matrix[i][j] == INT_MAX) cout <<"--- ";
            else cout << left << setw(3) << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// O(n^2)
void Matrix2D::LoadData() {
    for (int i = 1; i < length; i++) {
		for (int j = 1; j < length; j++) {
            cin >> matrix[i][j];
            if (i == j) matrix[i][j] = INT_MAX;
		}
    }

    for (int i = 0; i < length; i++) {
        matrix[i][0] = i;
        matrix[0][i] = i;
    }
}

// O(n^2)
void Matrix2D::RandomizeData(int minimum, int maximun) {
    srand(time(NULL));
	for (int i = 1; i < length; i++) {
		for (int j = 1; j < length; j++) {
            if (i == j) matrix[i][j] = INT_MAX;
			else matrix[i][j] = rand() % maximun + minimum;
		}
	}

    for (int i = 0; i < length; i++) {
        matrix[i][0] = i;
        matrix[0][i] = i;
    }
}

// should be able to improved O(n^2)
int Matrix2D::Reduce() {
    int total = 0;

	// reduce row
	for (int i = 1; i < length; i++) {
		int minimum = INT_MAX;
		for (int j = 1; j < length; j++)
			if (matrix[i][j] < minimum)
				minimum = matrix[i][j];

        if (minimum != INT_MAX) {
            total += minimum;
        for (int j = 1; j < length; j++)
            if (matrix[i][j] != INT_MAX)
                matrix[i][j] -= minimum;
        }
	}

    // reduce column
	for (int i = 1; i < length; i++) {
		int minimum = INT_MAX;
		for (int j = 1; j < length; j++)
			if (matrix[j][i] < minimum)
				minimum = matrix[j][i];
        if (minimum != INT_MAX) {
            total += minimum;
        for (int j = 1; j < length; j++)
            if (matrix[j][i] != INT_MAX)
                matrix[j][i] -= minimum;
        }
	}

	return total;
}

