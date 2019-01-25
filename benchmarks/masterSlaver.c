// master slver scheme 

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

 

int subtask1 =1;
int subtask2 = 2; 
 
int result1 =1;
int result2 = 2; 

  // We are assuming at least 3 processes for this task
  if (world_size < 3) {
    fprintf(stderr, "World size must be = 3 for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }


  if (world_rank == 0) {
    // If we are rank 0, send the subtasks to slavers

    MPI_Send(&subtask1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(&subtask2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);

    MPI_Recv(&result1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf(" \n receiving from p1 = %d\n", result1);
    
    MPI_Recv(&result2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf(" \n receiving from p2 = %d\n", result2);

  } else if (world_rank == 1) {

	int subtask; 
  MPI_Recv(&subtask, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("i am process %d i have received data from master", world_rank);

  subtask = world_rank +subtask;
  MPI_Send(&subtask, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
 
  }

 else if (world_rank == 2) {

	int subtask; 
  MPI_Recv(&subtask, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("i am process %d i have received data from master", world_rank);

  subtask = world_rank +subtask;
  MPI_Send(&subtask, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
 
  }
  MPI_Finalize();
}
