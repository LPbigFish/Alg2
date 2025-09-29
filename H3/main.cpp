#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<double>> readMatrix() {
    vector<vector<double>> matrix;
    string line;

    while (getline(cin, line) && !line.empty()) {
        vector<double> row;
        istringstream iss(line);
        double value;
        while (iss >> value) {
            row.push_back(value);
        }
        matrix.push_back(row);
    }

    return matrix;
}

vector<double> readVector() {
    vector<double> vec;
    string line;

    getline(cin, line);
    istringstream iss(line);
    double value;
    while (iss >> value) {
        vec.push_back(value);
    }

    return vec;
}

void printMatrix(const vector<vector<double>>& matrix) {
    cout << "Matrix:" << endl;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << setw(10) << fixed << setprecision(3) << elem << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printVector(const vector<double>& vec) {
    cout << "Vector:" << endl;
    for (const auto& elem : vec) {
        cout << setw(10) << fixed << setprecision(3) << elem << " ";
    }
    cout << endl << endl;
}

static vector<vector<double>> gaus(vector<vector<double>> a, vector<double> b) {
	int n = a.size();
	for (int i = 0; i < n; i++) {
		a[i].push_back(b[i]);
	}

    for (int i = 0; i < n - 1; i++) {
		int piv = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(a[j][i]) > abs(a[piv][i])) {
                piv = j;
            }
        }
        for (int k = i; k <= n; k++) {
            double temp = a[i][k];
            a[i][k] = a[piv][k];
            a[piv][k] = temp;
        }
        for (int j = i + 1; j < n; j++) {
			double temp = a[j][i] / a[i][i];
            for (int k = i; k < n + 1; k++) {
				a[j][k] = a[j][k] - a[i][k] * temp;
            }
        }
    }

    return a;
}

int main() {
    /*
    vector<vector<double>> matrix = readMatrix();
    vector<double> vec = readVector();

    printMatrix(matrix);
    printVector(vec);
    */

    vector<vector<double>> A_2 = {
    {2,4,-2,-2},
    {1,2,4,-3},
    {-3,-3,8,-2},
    {-1,1,6,-3}
    };
    vector<double> B_2 = { -4,5,7,7 };


    printMatrix(A_2);

	vector<vector<double>> result = gaus(A_2, B_2);

	printMatrix(result);
    // result == {1.0, 2.0, 3.0, 4.0}

    return 0;
}