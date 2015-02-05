
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h> 

#define M 1000

int main(int argc, char *argv[]) {
	int ID, P; 
	int tag = 1;
	MPI_Status status;

	MPI_Init (&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);	
	MPI_Comm_size(MPI_COMM_WORLD, &P); 

	if (ID == 0) { 
		double t = MPI_Wtime(); 
		for (int i = 0; i < M; i++) { 
			MPI_Send(NULL, 0, MPI_INT, 1, tag, MPI_COMM_WORLD); 
			MPI_Recv(NULL, 0, MPI_INT, 1, tag, 
					MPI_COMM_WORLD, &status); 
		}
		printf("send/recv throughput %lf/s\n", 
				(double)M / (MPI_Wtime() - t)); 
		printf("send/recv latency %lf/s\n", 
				(MPI_Wtime() - t) / (double) M); 

  	}
	else { 
		for (int i = 0; i < M; i++) { 
			MPI_Recv(NULL, 0, MPI_INT, 0, tag, 
					MPI_COMM_WORLD, &status); 
			MPI_Send(NULL, 0, MPI_INT, 0, tag, MPI_COMM_WORLD); 
		}

	}

	MPI_Finalize();
	return 0;
}


