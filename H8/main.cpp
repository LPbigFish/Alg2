#include <iostream>
#include <string>
#include <vector>

using namespace std;

static vector<size_t> shiftTable(const string& P) {
	size_t m = P.length();

    vector<size_t> table(256, m);

    for (size_t i = 0; i < m - 2; i++) {
		table[(unsigned char)P[i]] = m - 1 - i;
    }

	return table;
}

static int HorspoolMatching(const string& P, const string& T) {
    int i = P.length() - 1, M = T.length() - 1;

	vector<size_t> table = shiftTable(P);

    while (i <= M) {
        int k = 0;
        while (k < P.length() && P[P.length() - 1 - k] == T[i - k]) {
            k++;
        }
        if (k == P.length()) {
			return i - P.length() + 1;
        }
        else {
			i += table[(unsigned char)T[i]];
        }
    }
	return -1;
}

int main() {
    string pattern, text;

    getline(cin, pattern);

    getline(cin, text);

    int result = HorspoolMatching(pattern, text);

    if (result != -1) {
        cout << "Pattern found at index: " << result << endl;
    }
    else {
        cout << "Pattern not found" << endl;
    }

    return 0;
}