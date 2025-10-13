#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    void heapify(int i) {
		int n = heap.size();
        int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

        if (left < n && heap[left] > heap[largest]) {
			largest = left;
        }
        if (right < n && heap[right] > heap[largest]) {
            largest = right;
        }
        if (largest != i) {
			int temp = heap[i];
			heap[i] = heap[largest];
			heap[largest] = temp;
            heapify(largest);
		}
    }

public:
    void insert(int key) {
		heap.push_back(key);
		int n = heap.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    int extractMax() {
		int n = heap.size();
        if (n == 0) {
            return -1;
        }
        int max = heap[0];
		heap[0] = heap[n - 1];
        heap.pop_back();
        heapify(0);
		return max;
    }

    void printHeap() {
        for (int i : heap) {
            cout << i << " ";
        }
        cout << endl;
    }

    bool isEmpty() {
        return heap.empty();
    }
};

int main() {
    MaxHeap maxHeap;
    int num;

    // Načtení čísel ze stdin
    while (cin >> num) {
        maxHeap.insert(num);
    }

    // Postupné odebírání prvků a tisk haldy
    while (!maxHeap.isEmpty()) {
        cout << "(" << maxHeap.extractMax() << ") ";
        maxHeap.printHeap();
    }

    return 0;
}