#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int punches = 3;

    int boxerHits[punches];
    int totalHits = 0;

    // Боксер наносит удары
    for (int i = 0; i < punches; ++i) {
        boxerHits[i] = rand() % 10 + 1; // Генерация случайной силы удара от 1 до 10
        totalHits += boxerHits[i];
    }

    // Боксер отправляет сумму ударов рефери
    MPI_Send(&totalHits, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    // Рефери
    if (rank == 0) {
        int totalHitsBoxer1, totalHitsBoxer2;

        // Получаем сумму ударов от обоих боксеров
        MPI_Recv(&totalHitsBoxer1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&totalHitsBoxer2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Определение победителя
        if (totalHitsBoxer1 < totalHitsBoxer2) {
            std::cout << "Боксер 1 победил!\n";
        } else if (totalHitsBoxer1 > totalHitsBoxer2) {
            std::cout << "Боксер 2 победил!\n";
        } else {
            std::cout << "Ничья!\n";
        }
    }

    MPI_Finalize();
    return 0;
}
