#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

const int K = 10000000;
const int N1 = 1000;
const int N2 = 500;
const int N3 = 250;

void sortSubarray(std::vector<int> &array, int start, int end)
{
    std::sort(array.begin() + start, array.begin() + end);
}

int main()
{
    std::vector<int> array(K);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < K; ++i)
    {
        array[i] = std::rand() % 1000000;
    }

    int numThreads;
    std::cout << "Введите количество потоков (1, 2, 4 или 10): ";
    std::cin >> numThreads;

    if (numThreads != 1 && numThreads != 2 && numThreads != 4 && numThreads != 10)
    {
        std::cout << "Неверное количество потоков. Допустимые значения: 1, 2, 4, 10." << std::endl;
        return 1;
    }

    std::vector<std::thread> threads;

    auto start_time = std::chrono::high_resolution_clock::now();

    int portionSize = K / numThreads;
    
    for (int i = 0; i < numThreads; ++i)
    {
        int start = i * portionSize;
        int end = (i == numThreads - 1) ? K : (i + 1) * portionSize;
        threads.emplace_back(sortSubarray, std::ref(array), start, end);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Содержимое массива от 500 до 750 элементов:" << std::endl;
    for (int i = 500; i <= 750; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Время выполнения операции сортировки: " << execution_time << " миллисекунд." << std::endl;

    return 0;
}
