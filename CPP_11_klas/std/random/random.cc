#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int a[]={1, 2, 3, 4, 5, 6};
	vector<int> v(a, a+6);
	
	srand((unsigned)time(NULL));
	
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	
	for(int i=0;i<10;++i) {
		random_shuffle(v.begin(), v.end());
		copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}
	
	return 0;
}
