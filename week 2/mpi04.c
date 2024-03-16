// #include <stdio.h>
// #include <mpi.h>

// #define NUMDATA 10000

// void LoadData(int data[], int count)
// {
//     for (int i = 0; i < count; i++) {
//         data[i] = 1;
//     }
// }

// int AddUp(int data[], int count)
// {
//     int sum = 0;
//     for (int i = 0; i < count; i++) {
//         sum += data[i];
//     }
//     return sum;
// }

// int main(int argc, char **argv)
// {
//     int rank, size;
//     int sum_local = 0;
//     int sum_total = 0;
//     int data[NUMDATA];

//     MPI_Init(&argc, &argv);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);

//     // Load data only once by rank 0
//     if (rank == 0) {
//         LoadData(data, NUMDATA);
//     }

//     // Broadcast the data to all processes
//     MPI_Bcast(data, NUMDATA, MPI_INT, 0, MPI_COMM_WORLD);

//     // Calculate local sum
//     int chunk_size = NUMDATA / size;
//     int start = rank * chunk_size;
//     int end = (rank == size - 1) ? NUMDATA : start + chunk_size;
//     for (int i = start; i < end; i++) {
//         sum_local += data[i];
//     }

//     // Reduce the local sums to get the total sum
//     MPI_Reduce(&sum_local, &sum_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

//     // Print the total sum only by rank 0
//     if (rank == 0) {
//         printf("The total sum of data is %d\n", sum_total);
//     }

//     MPI_Finalize();
//     return 0;
// }

// #include <stdio.h>
// #include <mpi.h>

// #define NUMDATA 10000

// void LoadData(int data[], int count)
// {
//     for (int i = 0; i < count; i++) {
//         data[i] = 1;
//     }
// }

// int main(int argc, char **argv)
// {
//     int rank, size;
//     int sum_local = 0;
//     int sum_total = 0;
//     int data[NUMDATA];

//     MPI_Init(&argc, &argv);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);

//     LoadData(data, NUMDATA);

//     int chunk_size = NUMDATA / size;
//     int start = rank * chunk_size;
//     int end = (rank == size - 1) ? NUMDATA : start + chunk_size;

//     for (int i = start; i < end; i++) {
//         sum_local += data[i];
//     }

//     MPI_Reduce(&sum_local, &sum_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

//     if (rank == 0) {
//         printf("The total sum of data is %d\n", sum_total);
//     }

//     MPI_Finalize();
//     return 0;
// }

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int size;
    int rank;
    int tag = 0;
    int count;
    MPI_Status status;
    int *data = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_INT, &count);
            data = (int *)malloc(count * sizeof(int));
            MPI_Recv(data, count, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Node ID: %d; tag: %d; MPI_Get_count: %d; \n", status.MPI_SOURCE, status.MPI_TAG, count);
            free(data);
        }
    }
    else
    {
        int num_elements = rand() % 100;
        data = (int *)malloc(num_elements * sizeof(int));
        MPI_Send(data, num_elements, MPI_INT, 0, tag, MPI_COMM_WORLD);
        free(data);
    }

    MPI_Finalize();
    return 0;
}