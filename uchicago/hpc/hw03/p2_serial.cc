
#include <cstdio> 

using namespace std; 

const int I = 1000;
const int N = I + 1;
const int T = 200;
const int R = 2;

double x_min = -2.0; 
double x_max = 1.0; 
double y_min = -1.5;
double y_max = 1.5; 

double dx = (x_max - x_min) / (double)I; 
double dy = (y_max - y_min) / (double)I; 

int main() { 
	
	double c_x, c_y; 
	double z_x, z_y; 
	for (int r = 0; r < N; r++) { 
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
			printf("%d ", (k == T)? 0 : 1); 
		}
		printf("\n"); 
	}
	return 0; 
}

