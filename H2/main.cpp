#include <iostream>

static void quick_sort(int* arr, int left, int right) {
	if (left >= right) return;
	int pivot = arr[right];
	int i = left - 1;
	for (int j = left; j < right; ++j) {
		if (arr[j] <= pivot) {
			++i;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	int temp = arr[i + 1];
	arr[i + 1] = arr[right];
	arr[right] = temp;

	int partition_index = i + 1;
	quick_sort(arr, left, partition_index - 1);
	quick_sort(arr, partition_index + 1, right);
}

static bool transform_and_conquer(int* arr, int N) {
	quick_sort(arr, 0, N - 1);

	for (int i = 0; i < N - 2; i++) {
		if (arr[i] == arr[i + 1]) {
			return false;
		}
	}

	return true;
}

static int modus(int* arr, int N) {
	quick_sort(arr, 0, N - 1);

	int max_count = 1;
	int modus_value = arr[0];

	int current_value = arr[0];
	int temp_count = 1;

	for (int i = 0; i < N; i++) {
		if (arr[i] == current_value) {
			temp_count++;
		}
		else {
			if (temp_count > max_count) {
				max_count = temp_count;
				modus_value = current_value;
			}
			temp_count = 1;
			current_value = arr[i];
		}
	}

	return modus_value;
}

int main() {
	int data[] = { 3, 1, 4, 2, 5, 3, 4, 4 };
	int data2[] = { 3, 1, 4, 2, 5, 7, 8, 0 };

	std::cout << (transform_and_conquer(data, 8) ? "jedinečné" : "nejedinečné") << std::endl;
	std::cout << "Modus: " << modus(data, 8) << std::endl;
	
	return 0;
}