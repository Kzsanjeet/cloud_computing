#include <stdio.h>
#include <stdbool.h>
#include <mpi.h>

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main(int argc, char **argv) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int nstart = 1, nfinish = 10000;
    if (rank == 0) {
        printf("%s : Prime numbers between %d and %d are :\n", 
             argv[0], nstart, nfinish);
    }
    
    for (int i = nstart + rank; i <= nfinish; i += size) {
        if (isPrime(i)) {
            printf("%s : %d\n", argv[0], i);
        }
    }
    
    MPI_Finalize();
    return 0;
}
