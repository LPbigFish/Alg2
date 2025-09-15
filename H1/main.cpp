#include <iostream>

using namespace std;

static void bubble_sort(int* array, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (array[j] > array[j + 1]) {
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

int main() {
	srand(time(nullptr));

	int* array = new int[100];

	for (int i = 0; i < 100; i++) {
		array[i] = rand() % 1000;
	}

	for (int i = 0; i < 100; i++) {
		cout << array[i] << " ";
	}

	cout << endl << endl;

	bubble_sort(array, 100);

	for (int i = 0; i < 100; i++) {
		cout << array[i] << " ";
	}

	return 0;
}