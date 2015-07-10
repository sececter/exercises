#include <iostream>
#include <list>

using namespace std;

unsigned int numNodes, numEdges, numMarked, a, b;
list<int> nodes[10000];
bool marked[10000];
bool isNoCycle = true;
bool isConnected;

void traverse(int node, int parent) {
	if(marked[node]){ isNoCycle = false; return; }
	marked[node] = true;
	numMarked = numMarked + 1;
	list<int>::iterator it=nodes[node].begin();
	while(it != nodes[node].end() && isNoCycle) {
		if(*it != parent) traverse(*it, node);
		it++;
	}
}

int main() {
	cin >> numNodes; cin >> numEdges;
	for(unsigned int i = 0; i <= numNodes; i++) marked[i] = false;
	while(numEdges--) {
		cin >> a; cin >> b;
		nodes[a].push_back(b); nodes[b].push_back(a);
	}
	traverse(1, 0);
	if(numMarked == numNodes) isConnected = true;
	else isConnected = false;
	if(isNoCycle && isConnected) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
