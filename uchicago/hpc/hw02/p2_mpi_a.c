
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h> 

#define I 1000
#define N (I + 1)
#define T 200
#define R 2

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
	  }
	  printf("\n");
	}
}

int msg_cnt(int ID, int P) { 
	int cnt = 0;
	for (int r = ID - 1; r < N; r += (P-1)) { 
		cnt += 1; 
	}
	return cnt; 
}

int main(int argc, char *argv[]) {
	int ID, P; 
	int tag = 1;
	MPI_Status status;

	MPI_Init (&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);	
	MPI_Comm_size(MPI_COMM_WORLD, &P); 

	if (ID == 0) { 
		int buf[N+1]; 
		for (int i = 1; i < P; i++) { 
			for (int j = 0; j < msg_cnt(i, P); j++) { 
				MPI_Recv(buf, N+1, MPI_INT, i, tag, MPI_COMM_WORLD, &status); 
				int r = buf[0]; 
				// printf("recv row %d\n", r); 
				for (int c = 0; c < N; c++) { 
					M[r][c] = buf[c+1]; 
				}
			}
		}
		print_grid(M); 
	  
  	}
	else { 
		double c_x, c_y; 
		double z_x, z_y; 
		int buf[N+1]; 
		for (int r = ID - 1; r < N; r += (P-1)) { 
			c_y = y_max - r * dy; 

			buf[0] = r; 
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
				buf[c+1] = (k == T)? 0 : 1; 
			}
			MPI_Send(buf, N+1, MPI_INT, 0, tag, MPI_COMM_WORLD); 
		}
	}

	MPI_Finalize();
	return 0;
}




