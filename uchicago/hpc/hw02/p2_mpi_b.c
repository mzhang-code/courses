
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h> 

#define I 1000
#define N (I + 1)
#define T 200
#define R 2
#define TERM_TAG 2
#define NORM_TAG 1

double x_min = -2.0; 
double x_max = 1.0; 
double y_min = -1.5;
double y_max = 1.5; 

double dx = (x_max - x_min) / (double)I; 
double dy = (y_max - y_min) / (double)I; 


int M[N][N];

void print_grid(int M[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) { 
			printf("%d ", M[i][j]);
			fflush(stdout);
	  }
	  printf("\n");
	}
}

int si = -1; 

int next_index() { 
	si += 1;
	return si;
}

int main(int argc, char *argv[]) {
	int ID, P; 
	int tag = NORM_TAG; 

	MPI_Init (&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);	
	MPI_Comm_size(MPI_COMM_WORLD, &P); 

	if (ID == 0) { 
		MPI_Status status;
		int req_buf[1]; 
		int res_buf[N+1];
		for (int proc = 1; proc < P; proc++) { 
			req_buf[0] = next_index(); 
			MPI_Send(req_buf, 1, MPI_INT, proc, 
					tag, MPI_COMM_WORLD); 	
			// printf("init sent [%d] to %d\n", req_buf[0], proc); 

		}
		while (si < N-1) { 
			MPI_Recv(res_buf, N+1, MPI_INT, MPI_ANY_SOURCE, 
					MPI_ANY_TAG, MPI_COMM_WORLD, &status); 
			int r = res_buf[0];
			for (int c = 0; c < N; c++) { 
				M[r][c] = res_buf[c+1];
			} 
			// printf("recv [%d] from %d\n", r, status.MPI_SOURCE); 

			req_buf[0] = next_index();
			MPI_Send(req_buf, 1, MPI_INT, status.MPI_SOURCE, 
					tag, MPI_COMM_WORLD); 	
			// printf("sent [%d] to %d\n", req_buf[0], status.MPI_SOURCE); 
		}

		for (int proc = 1; proc < P; proc++) { 
			MPI_Recv(res_buf, N+1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, 
					MPI_COMM_WORLD, &status); 

			int r = res_buf[0];
			for (int c = 0; c < N; c++) { 
				M[r][c] = res_buf[c+1];
			} 
			// printf("finally recv [%d] from %d\n", r, status.MPI_SOURCE); 
		}
		
		for (int proc = 1; proc < P; proc++) { 
			MPI_Send(NULL, 0, MPI_INT, proc, 
					TERM_TAG, MPI_COMM_WORLD); 	

		}

		print_grid(M); 
	  
  	}
	else { 
		MPI_Status status;
		double c_x, c_y; 
		double z_x, z_y; 
		int req[1]; 
		int res[N+1]; 
		while (1) { 
			MPI_Recv(req, 1, MPI_INT, 0, MPI_ANY_TAG, 
					MPI_COMM_WORLD, &status); 
			if (status.MPI_TAG == TERM_TAG) { 
				break; 
			}
			int r = req[0]; 
			res[0] = r; 

			c_y = y_max - r * dy; 

			for (int c = 0; c < N; c++) { 
				c_x = x_min + c * dx; 

				z_x = 0.0; 
				z_y = 0.0; 

				int k;
				for (k = 0; k < T; k++) { 
					if (z_x*z_x + z_y*z_y > R*R) { 
						break;
					}
					double px = z_x; 
					double py = z_y; 

					z_x = px*px - py*py + c_x; 
					z_y = 2*px*py + c_y; 
				}
				res[c+1] = (k == T)? 0 : 1; 
			}

			MPI_Send(res, N+1, MPI_INT, 0, tag, MPI_COMM_WORLD); 
		}

	}

	MPI_Finalize();
	return 0;
}


