#include <iostream>
#include <vector>
#include <string>

using namespace std;

static int CoinRow(vector<vector<short>> array) {
	int n = array.size();
	int m = array[0].size();

	vector<vector<int>> temp_array(n, vector<int>(m, 0));

	temp_array[0][0] = array[0][0];

	for (size_t i = 1; i < m; i++) {
		temp_array[0][i] = temp_array[0][i - 1] + array[0][i];
	}

	for (size_t i = 1; i < n; i++) {
		temp_array[i][0] = temp_array[i - 1][0] + array[i][0];
		for (size_t j = 1; j < m; j++) {
			temp_array[i][j] = max(temp_array[i - 1][j], temp_array[i][j - 1]) + array[i][j];
		}
	}

	return temp_array.back().back();
}


int main() {
	string line;
	vector<vector<short>> array;
	while (getline(cin, line)) {
		if (line.empty()) {
			break;
		}
		vector<short> row;
		for (char c : line) {
			if (isdigit(c)) {
				row.push_back(c - '0');
			}
		}
		if (!row.empty()) {
			array.push_back(row);
		}
	}

	cout << CoinRow(array) << endl;

	return 0;
}