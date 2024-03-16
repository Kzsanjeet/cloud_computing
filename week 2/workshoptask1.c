
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define FILENAME "WarAndPeace.txt"
#define ALPHABET_SIZE 26

int main(int argc, char *argv[])
{
    int rank, size;
    char c;
    int local_counts[ALPHABET_SIZE] = {0};
    int total_counts[ALPHABET_SIZE] = {0};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        FILE *file = fopen(FILENAME, "r");
        if (file == NULL)
        {
            fprintf(stderr, "Error: Unable to open file %s\n", FILENAME);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        // Read the file and count letters
        while ((c = fgetc(file)) != EOF)
        {
            if (c >= 'a' && c <= 'z')
            {
                local_counts[c - 'a']++;
            }
            else if (c >= 'A' && c <= 'Z')
            { // Convert uppercase to lowercase
                local_counts[c - 'A']++;
            }
        }
        fclose(file);
    }

    // Broadcast counts to all processes
    MPI_Bcast(local_counts, ALPHABET_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process sums up its own range of counts
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        int chunk_size = (ALPHABET_SIZE + size - 1) / size;
        int start = rank * chunk_size;
        int end = (rank + 1) * chunk_size;
        if (end > ALPHABET_SIZE)
        {
            end = ALPHABET_SIZE;
        }
        for (int j = start; j < end; j++)
        {
            total_counts[j] += local_counts[j];
        }
    }

    // Gather total counts from all processes
    MPI_Allreduce(total_counts, local_counts, ALPHABET_SIZE, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Print counts
    if (rank == 0)
    {
        printf("\n---------Letter Counts---------\n");
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            printf("%c: %d\n", 'a' + i, local_counts[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
