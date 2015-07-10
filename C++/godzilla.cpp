#include <iostream>
#include <list>

using namespace std;

int main() {
	int t, g, m, a;
	bool decided;
	cin >> t;
	while(t--) {
		list<int> gl, ml;
		decided = false;
		cin >> g >> m;
		cin >> a;
		gl.push_front(a);
		g--;
		while(g--) {
			cin >> a;
			list<int>::iterator it=gl.begin();
			while(a < *it && it != gl.end()) it++;
			gl.insert(it, a);
		}
		cin >> a;
		ml.push_front(a);
		m--;
		while(m--) {
			cin >> a;
			if(a > gl.front()) {
				cout << "MechaGodzilla" << endl;
				decided = true;
			}
			list<int>::iterator it=ml.begin();
			while(a < *it && it != ml.end()) it++;
			ml.insert(it, a);
		}
		while(!gl.empty() && !ml.empty() && !decided) {
			if(gl.front() > ml.front() ||
				gl.front() == ml.front()) {
					cout << "Godzilla" << endl;
					break;
				}
			else {
				cout << "MechaGodzilla" << endl;
				break;
			}
			gl.pop_front(); ml.pop_front();
		}
	}
	return 0;
}
