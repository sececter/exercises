#include <iostream>
#include <stack>
#include <list>

using namespace std;

int main() {
	int n, next, i;
	bool possible;
	while(cin >> n, n != 0) {
		i = 1;
		possible = true;
		list<int> li;
		stack<int> st;
		while(n--) {
			cin >> next;
			li.push_back(next);
		}
		while(!li.empty()) {
			next = li.front();
			//cout << "next = " << next << endl;
			//cout << "i = " << i << endl;
			//if(!st.empty()) cout << "top = " << st.top() << endl;
			if(next == i) {
				li.pop_front();
				i++;
			}
			else if(!st.empty() && st.top() == i) {
				st.pop();
				i++;
			}
			else if(st.empty() || st.top() > next) {
				st.push(next);
				li.pop_front();
			}
			else {
				possible = false;
				break;
			}
		}
		possible ? cout << "yes" << endl : cout << "no" << endl;
	}
	return 0;
}
