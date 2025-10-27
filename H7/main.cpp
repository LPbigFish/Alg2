#include <iostream>
#include <vector>

using namespace std;

static vector<int> countingComparisonSort(vector<int> array) {
    vector<int> S;
	vector<int> C;

    for (int i = 0; i < array.size(); ++i) {
        C.push_back(0);
		S.push_back(0);
	}

    for (int i = 0; i < array.size() - 1; i++) {
        for (int j = i + 1; j < array.size(); j++) {
            if (array[i] < array[j]) {
                C[j] += 1;
            }
            else {
                C[i] += 1;
            }
        }
    }
    
    for (int i = 0; i < array.size(); ++i) {
        S[C[i]] = array[i];
    }

    return S;
}

int main() {
    vector<int> array;

    int num;

    while (cin >> num) {
        array.push_back(num);
    }

	array = countingComparisonSort(array);

    for (int i = 0; i < array.size(); i++) {
		cout << array[i] << " ";
	}

	return 0;
}