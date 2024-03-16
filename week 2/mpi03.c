#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, parcel = 1;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    while (parcel <= size)
    {
        if (rank == 0)
        {
            MPI_Send(&parcel, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&parcel, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process 0 received parcel: %d\n", parcel);
        }
        else
        {
            MPI_Recv(&parcel, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            parcel++;
            MPI_Send(&parcel, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
            printf("Process %d received parcel: %d, added 1 and sent to Process %d\n", rank, parcel, (rank + 1) % size);
        }
    }

    MPI_Finalize();
    return 0;
}