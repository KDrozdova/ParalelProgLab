#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>

using namespace std;

const int K = 10000000;
const int N_values[] = {1000, 500, 250};

vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
    return arr;
}

void sortArrayInChunks(vector<int>& arr, int N, int numThreads) {
    int chunkSize = arr.size() / numThreads;

    #pragma omp parallel num_threads(numThreads)
    {
        #pragma omp for
        for (int i = 0; i < numThreads; ++i) {
            int startIdx = i * chunkSize;
            int endIdx = (i == numThreads - 1) ? arr.size() : startIdx + chunkSize;
            sort(arr.begin() + startIdx, arr.begin() + endIdx);
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr));

    vector<int> arr = generateRandomArray(K);

    int numThreads;
    cout << "Введите количество потоков (1, 2, 4 или 10): ";
    cin >> numThreads;

    if (numThreads != 1 && numThreads != 2 && numThreads != 4 && numThreads != 10) {
        cout << "Некорректное количество потоков. Выход из программы." << endl;
        return 1;
    }

    for (int N : N_values) {
        auto startTime = chrono::high_resolution_clock::now();

        sortArrayInChunks(arr, N, numThreads);

        auto endTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

        cout << "Сортировка для N = " << N << " заняла " << duration.count() << " миллисекунд." << endl;
    }

    cout << "Содержимое массива с 500 по 750 элемент: ";
    for (int i = 500; i <= 750; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
