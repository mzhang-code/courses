
#include <cstdio> 
#include <vector> 
#include <utility> 

#include <omp.h>

using namespace std;

typedef vector<int> List; 
typedef vector<List> Mat; 

const int INF = 0x7fffffff; 

int n, m; 
Mat D; 
Mat W; 
Mat G; 

int extract_min(List D, List flags) { 
	int m = INF, pos = -1; 
	for (int i = 0; i < D.size(); i++) { 
		if (!flags[i] && D[i] < m) { 
			m = D[i]; 
			pos = i; 
		}
	}
	return pos; 
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

		for (int v : G[node]) { 
			if (D[s][node] + W[node][v] < D[s][v]) { 
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

	#pragma omp parallel {
		for (int s = 0; s < n; s++) { 
			dijkstra(G, D, W, s); 
		}
	}

	return 0; 
}

