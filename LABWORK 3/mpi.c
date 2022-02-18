#include <mpi/mpio.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    //init mpi env
    MPI_Init(NULL, NULL);
    //rank and size of communication
    int world_size = 2, world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size < 2) {
        printf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    else {
         printf("connected\n");
    }
    int number;
    if (world_rank == 0) {
        // If we are rank 0, set the number to -1 and send it to process 1
        number = -1;
        MPI_Send(
        &number,
        1,
        MPI_INT,
        1,
        0,
        MPI_COMM_WORLD);
    }
    else if(world_rank==1) {
    MPI_Recv(&number,
    1,
    MPI_INT,
    0,
    0,
    MPI_COMM_WORLD,
    MPI_STATUSES_IGNORE);
    printf("Process 1 received number %d from process 0\n", number);
    }
    MPI_Finalize();
}