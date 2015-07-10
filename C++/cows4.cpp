#include <stdio.h>
#include <map>

using namespace std;

typedef unsigned int T;
typedef pair<T,T> be_pair_t;

map<be_pair_t,T> mem;

inline T max(T x, T y) {
	if(x > y) return x;
	else return y;
}

T find_max_profit(T treat[], T begin, T end, T age) {
	map<be_pair_t,T>::iterator it = mem.find(be_pair_t(begin,end));
	if(it != mem.end()) return it->second;
	if(begin == end) {
		mem.insert(pair<be_pair_t,T>(be_pair_t(begin,end),treat[begin]*age));
		return age*treat[begin];
	}
	else return max(find_max_profit(treat, begin+1, end, age+1) + age*treat[begin],
					find_max_profit(treat, begin, end-1, age+1) + age*treat[end]);
}

int main() {
	T treat[2010];
	T num_of_treats;
	scanf("%u", &num_of_treats);
	for(T i = 0; i < num_of_treats; i++)
		scanf("%u", &treat[i]);
	printf("%u\n", find_max_profit(treat, 0, num_of_treats-1, 1));
	return 0;
}
