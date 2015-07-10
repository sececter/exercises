#include <iostream>

using namespace std;

typedef unsigned short T;

void go_level_down(T node_number, T current_depth, T& max_depth, T* A, T n) {
	current_depth++;
	for(T i = 0; i < n; i++)
		if(A[node_number][i] == 1) 
			go_level_down(i, current_depth, max_depth, A, n);
	if(current_depth > max_depth) max_depth = current_depth;
}

int main() {
	T n, u, v, max_depth, one_edge_node;
	T A[n][n];
	T number_of_edges_in[n];
	for(int i = 0; i < n; i++) {
		cin >> u >> v;
		A[u][v] = 1;
		A[v][u] = 1;
		number_of_edges_in[u]++;
		number_of_edges_in[v]++;
	}
	one_edge_node = n;
	for(int i = 0; i < n; i++) {
		if(number_of_edges_in[i] == 1) {
			one_edge_node = i;
			break;
		}
	}
	max_depth = 1;
	go_level_down(one_edge_node, 1, max_depth, *A, n);
	cout << max_depth << endl;
	return 0;
}
	
