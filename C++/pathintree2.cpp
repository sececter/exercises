#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef unsigned int T;

struct furthest_node_info {
	furthest_node_info() :
		node_number(0),
		distance(0)
	{ }
	T node_number;
	T distance;
};

struct node_search_struct {
	node_search_struct(T node_number, T parent_node, T distance) :
		node_number(node_number),
		parent_node(parent_node),
		distance(distance)
	{ }
	T node_number;
	T parent_node;
	T distance;
};

//Finds the furthest node from the given node and returns either distance
//to the node or the node number
furthest_node_info find_furthest_node(T node, vector< vector<T> > A) {
	furthest_node_info ret;
	//Stack used for DFS
	stack<node_search_struct> search_stack;
	//Push the first node to the stack
	search_stack.push(node_search_struct(node, node, 0));
	//While the stack is not empty
	while(!search_stack.empty()) {
		//Take the first node from the stack
		node_search_struct current_node = search_stack.top();
		search_stack.pop();
		//If we have found the largest distance so far
		if(current_node.distance > ret.distance) {
			ret.distance = current_node.distance;
			ret.node_number = current_node.node_number;
		}
		//Put all the children of the node onto the stack
		for(vector<T>::iterator it = A[current_node.node_number].begin(); it != A[current_node.node_number].end(); it++) {
			if(*it != current_node.parent_node)
				search_stack.push(node_search_struct(*it, current_node.node_number, current_node.distance+1));
		}
	}
	return ret;
}


int main() {
	//Init and input, no input validity check
	T n, u, v;
	vector< vector<T> > A;
	cin >> n;
	A.resize(n);
	for(T i = 0; i < n-1; i++) {
		cin >> u >> v;
		//Node's position will be one less than its number
		u--; v--;
		A[u].push_back(v);
		A[v].push_back(u);
	}
	//First find the furthest node from any node, e.g. the first
	furthest_node_info furthest_node_from_first = find_furthest_node(0, A);
	//Find the furthest from it
	furthest_node_info furthest_node_from_furthest_from_first = find_furthest_node(furthest_node_from_first.node_number, A);
	//Print the distance between the two
	cout << furthest_node_from_furthest_from_first.distance << endl;

	return 0;
}
