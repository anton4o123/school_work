#include <iostream>
using namespace std;

int main() {
	int x1,y1,x2,y2,a,b;
	
	do {
		cin >> x1 >> y1 >> x2 >> y2 >> a >> b;
	} while(((x1<1)||(x1>=50)) || ((y1<1)||(y1>=50)) || ((x2<1)||(x2>=50)) || ((y2<1)||(y2>=50)) || ((a<1)||(a>=50)) || ((b<1)||(b>=50)));
	
	return 0;
}
