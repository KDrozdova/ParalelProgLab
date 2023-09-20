#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <chrono>

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

    // ��������� ������ ���������� �������
    for (int i = 0; i < K; ++i)
    {
        array[i] = rand() % 1000000;
    }

    std::vector<std::thread> threads;

    auto start_time = std::chrono::high_resolution_clock::now();

    // ��������� ������ ��� ���������� ������ ������ �������
    threads.emplace_back(sortSubarray, std::ref(array), 500, 750);
    threads.emplace_back(sortSubarray, std::ref(array), N1, N1 + 500);
    threads.emplace_back(sortSubarray, std::ref(array), N1 + N2, N1 + N2 + 250);
    threads.emplace_back(sortSubarray, std::ref(array), N1 + N2 + N3, N1 + N2 + N3 + 250);

    // ���������� ���������� ���� �������
    for (auto &thread : threads)
    {
        thread.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // ������� ���������� ������� � 500 �� 750 �������
    for (int i = 500; i <= 750; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "����� ���������� ���������: " << execution_time << " �����������" << std::endl;

    return 0;
}
