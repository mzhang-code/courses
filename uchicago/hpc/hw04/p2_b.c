
#include <cstdio> 
#include <cstdlib> 
#include <cmath> 
#include <ctime> 

#include <omp.h>

using namespace std;

#define THREAD_NUM 10
#define PI 3.1415926535

struct Vector { 
    double x, y, z; 
    Vector(double _x, double _y, double _z) { 
        x = _x; 
        y = _y; 
        z = _z; 
    }
}; 

double** create_mat(int n) { 
	double **A = new double*[n];
	for (int i = 0; i < n; i++) {
		A[i] = new double[n];
		for (int j = 0; j < n; j++) { 
			A[i][j] = 0.0;
		}	
	}
	return A; 
}

void print_mat(double **G, int n) { 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            printf("%f ", G[i][j]); 
        }
        printf("\n"); 
    }
}

double rand_radian(double r) { 
    int a = rand() % 1000000; 
    return ((double)a) / 1000000.0 * r; 
}

Vector vec_mul_scalar(Vector v, double s) { 
    return Vector(v.x * s, v.y * s, v.z * s); 
}

double vec_mul_vec(Vector v, Vector u) {
    return v.x * u.x + v.y * u.y + v.z * u.z; 
}

double vec_len(Vector V) { 
    return sqrt(V.x*V.x + V.y*V.y + V.z*V.z); 
}

Vector vec_sub(Vector V, Vector C) { 
    return Vector(V.x - C.x, V.y - C.y, V.z - C.z); 
}

double max(double x, double y) { 
    return (x > y) ? x : y; 
}

void ray_tracing(int n, double W_y, double W_max, 
                Vector L, Vector C, double R, int nrays) { 

    double **G = create_mat(n); 

    double** grids[THREAD_NUM];  

    for (int i = 0; i < THREAD_NUM; i++) { 
        grids[i] = create_mat(n);
    }

    #pragma omp parallel for
    for (int ray = 0; ray < nrays; ray++) { 
        double theta = rand_radian(2*PI); 
        double phi = rand_radian(2*PI); 

        // printf("%f %f\n", theta, phi);

        Vector V = Vector(sin(theta) * cos(phi), 
                        sin(theta) * sin(phi), cos(phi)); 
        
        // printf("V: %f %f %f\n", V.x, V.y, V.z); 

        Vector W = vec_mul_scalar(V, W_y / V.y); 

        // printf("W: %f %f %f\n", W.x, W.y, W.z); 

        if (abs(W.x) < W_max && abs(W.z) < W_max && 
            pow(vec_mul_vec(V, C), 2.0) + R*R - vec_mul_vec(C, C) >= 0) { 

            double t = vec_mul_vec(V, C) - 
                sqrt(pow(vec_mul_vec(V, C), 2) + R*R - vec_mul_vec(C,C)); 

            Vector I = vec_mul_scalar(V, t); 
            Vector N = vec_mul_scalar(vec_sub(I, C), 
                            1.0 / vec_len(vec_sub(I, C))); 
            Vector S = vec_mul_scalar(vec_sub(L, I), 
                            1.0 / vec_len(vec_sub(L, I)));

            double b = max(0.0, vec_mul_vec(S, N)); 
            // printf("b: %f\n", b); 

            int i = (int)(abs(W.x) / W_max * n);
            int j = (int)(abs(W.z) / W_max * n);  

            int tid = omp_get_thread_num();

            #pragma omp atomic
            grids[tid][i][j] += b; 
        }
    }
    for (int t = 0; t < THREAD_NUM; t++) { 
        for (int i = 0; i < n; i++) { 
            for (int j = 0; j < n; j++) { 
                G[i][j] += grids[t][i][j];
            }
        }
    }
    print_mat(G, n); 
   
}

int main() { 

    omp_set_num_threads(THREAD_NUM); 

    srand(time(0)); 

    int n = 2500; 
    Vector L(4.0, 4.0, -1.0); 
    double W_y = 10.0;
    double W_max = 10.0; 
    Vector C(0, 12, 0); 
    double R = 6.0; 
    int nrays = 1000000; 

	clock_t ts = clock(); 

    ray_tracing(n, W_y, W_max, L, C, R, nrays); 

    ts = clock() - ts; 
	printf("%ld clocks (%f seconds)\n", ts, ((float)ts)/CLOCKS_PER_SEC); 

    return 0; 
}
