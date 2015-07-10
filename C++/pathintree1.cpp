#include <iostream>
#include <vector>

using namespace std;

//Type used for marking nodes - vary with tree size
typedef unsigned int T;

//Recursive function, returns maximum depth reached by following node
T max_depth_reached_following_node(T node, T parent_node, T current_depth, T& max_depth_reached, vector< vector<T> > A) {
	if(current_depth > max_depth_reached) max_depth_reached = current_depth;
	//Try following all children, if any
	for(vector<T>::iterator it = A[node].begin(); it != A[node].end(); it++) {
		//Make sure we don't come back via parent
		if(*it != parent_node) {
			current_depth++;
			max_depth_reached_following_node(*it, node, current_depth, max_depth_reached, A);
			current_depth--;
		}
	}
	return max_depth_reached;
}

//Main function
int main() {
	//Init and input, no input validity check
	T n, u, v, max_depth_reached = 0;
	vector< vector<T> > A;
	cin >> n;
	T last_node = n-1;
	A.resize(n);
	for(T i = 0; i < n-1; i++) {
		cin >> u >> v;
		//Node's position will be one less than its number
		u--; v--;
		A[u].push_back(v);
		A[v].push_back(u);
	}
		
	cout << max_depth_reached_following_node(last_node, last_node, 0, max_depth_reached, A) << endl;

	return 0;
}
