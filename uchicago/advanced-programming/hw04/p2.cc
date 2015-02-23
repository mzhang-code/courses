
#include <cstdio> 
#include <vector> 
#include <utility> 

using namespace std;

typedef vector<int> List; 
typedef vector<List> Mat; 

const int INF = 0x7fffffff; 

int n, m; 
Mat D; 
Mat W; 
Mat G; 

int extract_min(List D, List flags) { 
	int thread_num = omp_get_num_threads(); 
	List min_vals, indices; 
	min_vals.resize(n); 
	indices.resize(n); 

	#pragma omp parallel { 
		int tid = omp_get_thread_num(); 
		int min_vals[tid] = INF;
		int indices[tid] = -1; 
		int n = D.size(); 

		int start = tid * n / thread_num; 
		int end = (tid+1) * n / thread_num; 
		if (tid = thread_num - 1) { 
			end = n; 
		}
		for (int i = start; i < end; i++) { 
			if (!flags[i] && D[i] < min_vals[tid]) { 
				min_vals[tid] = D[i]; 
				indices[tid] = i; 
			}
		}
	}

	int m = INF; 
	int index = -1; 
	for (int i = 0; i < thread_num; i++) { 
		if (min_vals[i] < m) { 
			m = min_vals[i]; 
			index = indices[i]; 
		}
	}
	return index; 
}

void dijkstra(Mat G, Mat &D, Mat W, int s) { 
	int n = G.size(); 
	List flags; 
	flags.resize(n); 
	for (int& f : flags) { 
		f = 0; 
	}
	flags[s] = 1; 
	D[s][s] = 0; 

	for (int& d : D[s]) { 
		d = INF; 
	}

	for (int v : G[s]) { 
		D[s][v] = W[s][v]; 
	}

	int k = n - 1; 
	while (k--) { 
		int node = extract_min(D[s], flags); 
		flags[node] = 1; 
		
		/* relax */ 
		#pragma omp parallel for
		for (int i = 0; i < G[node].size(); i++) { 
			int v = G[node][i]; 
			if (!flags[v] && D[s][node] + W[node][v] < D[s][v]) { 
				D[s][v] = D[s][node] + W[node][v]; 
			}
		}
	}
}

int main() { 

	scanf("%d%d", &n, &m); 

	D.resize(n);
	W.resize(n);
	G.resize(n); 

	for (int i = 0; i < n; i++) { 
		D[i].resize(n); 
		W[i].resize(n); 
		G[i].clear(); 
	}

	for (int i = 0; i < m; i++) { 
		int s, t, w; 
		scanf("%d%d%d", &s, &t, &w); 
		W[s][t] = w; 
		G[s].push_back(t); 
	}

	#pragma omp parallel for 
	for (int s = 0; s < n; s++) { 
		dijkstra(G, D, W, s); 
	}

	return 0; 
}

