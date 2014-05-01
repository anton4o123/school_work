#include <iostream>
using namespace std;

struct Vec {
	double x, y;
};

int main() {
	Vec f, v, r;
	double m, t=0, dt;
	
	cout << "Molq vuvedete 'm': ";cin >> m;
	
	f.x=0;
	f.y=m*9.8;
	
	cout << "Molq vuvedete 'r.x': ";cin >> r.x;
	cout << "Molq vuvedete 'r.y': ";cin >> r.y;
	
	cout << "Molq vuvedete 'v.x': ";cin >> v.x;
	cout << "Molq vuvedete 'v.y': ";cin >> v.y;
	
	cout << "Molq vuvedete delta t: ";cin >> dt;
	
	while(r.y>0) {
		t+=dt;
		r.x+=(v.x/m)*dt;
		r.y+=(v.y/m)*dt;
		v.x-=(f.x/m)*dt;
		v.y-=(f.y/m)*dt;
	}
	
	cout << r.x << ' ' << r.y << endl;
	
	return 0;
}
