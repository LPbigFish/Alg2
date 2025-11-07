#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<float>> readMatrix() {
    vector<vector<float>> matrix;
    string line;

    while (getline(cin, line) && !line.empty()) {
        vector<float> row;
        istringstream iss(line);
        float value;
        while (iss >> value) {
            row.push_back(value);
        }
        matrix.push_back(row);
    }

    return matrix;
}

vector<float> readVector() {
    vector<float> vec;
    string line;

    getline(cin, line);
    istringstream iss(line);
    float value;
    while (iss >> value) {
        vec.push_back(value);
    }

    return vec;
}

static void printVector(const vector<float>& v) {
    cout << fixed << setprecision(3);
    for (size_t i = 0; i < v.size(); ++i) cout << v[i] << (i + 1 < v.size() ? ' ' : '\n');
}

static vector<vector<float>> gaus(vector<vector<float>> a, vector<float> b) {
	int n = a.size();
	for (int i = 0; i < n; i++) {
		a[i].push_back(b[i]);
	}

    for (int i = 0; i < n - 1; i++) {
		int piv = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(a[j][i]) > fabs(a[piv][i])) {
                piv = j;
            }
        }
        for (int k = i; k <= n; k++) {
            float temp = a[i][k];
            a[i][k] = a[piv][k];
            a[piv][k] = temp;
        }
        for (int j = i + 1; j < n; j++) {
			float temp = a[j][i] / a[i][i];
            for (int k = i; k < n + 1; k++) {
				a[j][k] = a[j][k] - a[i][k] * temp;
            }
        }
    }

    return a;
}

static vector<float> backSubstitution(const vector<vector<float>>& aug) {
    int n = (int)aug.size();
    vector<float> x(n, 0.0f);

    for (int i = n - 1; i >= 0; --i) {
        // find first non-zero in row i (pivot column)
        int piv = -1;
        for (int c = 0; c < n; ++c) {
            if (fabs(aug[i][c]) > 1e-9f) { piv = c; break; }
        }
        if (piv == -1) continue; // zero row -> free variable (handled by rank check in main)
        float rhs = aug[i][n];
        for (int c = piv + 1; c < n; ++c) rhs -= aug[i][c] * x[c];
        x[piv] = rhs / aug[i][piv];
    }
    return x;
}

static bool inconsistentRow(const vector<float>& row) {
    int n = (int)row.size() - 1;
    bool allZero = true;
    for (int c = 0; c < n; ++c) if (fabs(row[c]) > 1e-9f) { allZero = false; break; }
    return allZero && fabs(row[n]) > 1e-9f;
}

static int rankA(const vector<vector<float>>& aug) {
    int n = (int)aug.size();
    int r = 0;
    for (int i = 0; i < n; ++i) {
        bool nonZero = false;
        for (int c = 0; c < n; ++c) if (fabs(aug[i][c]) > 1e-9f) { nonZero = true; break; }
        if (nonZero) ++r;
    }
    return r;
}

int main() {
    vector<vector<float>> matrix = readMatrix();
    vector<float> vec = readVector();

	vector<vector<float>> result = gaus(matrix, vec);

    int dim = result.size();

    if (dim < 1) {
        return 0;
    }

    for (int i = 0; i < dim; ++i) {
        if (inconsistentRow(result[i])) {
            cout << "žádné øešení" << endl;
            return 0;
        }
    }

    if (rankA(result) < dim) {
        cout << "nekoneènì mnoho øešení" << endl;
        return 0;
    }

	vector<float> solution = backSubstitution(result);

	printVector(solution);

    // result == {1.0, 2.0, 3.0, 4.0}

    return 0;
}