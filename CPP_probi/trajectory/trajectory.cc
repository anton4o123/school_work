#include <iostream>
#include <cmath>
using namespace std;

struct Vec {
	double x, y;
};

int main() {
	Vec f, v, r;
	double m, t=0, dt, angle, v0;
	
	cout << "Molq vuvedete 'm': ";cin >> m;
	
	cout << "Molq vuvedete 'r.x': ";cin >> r.x;
	cout << "Molq vuvedete 'r.y': ";cin >> r.y;
	
	cout << "Molq vuvedete ugul: ";cin >> angle;
	cout << "Molq vuvedete v0: ";cin >> v0;
	
	if(angle==90 || angle==270) {
		v.x=0;
		v.y=v0*sin(angle*M_PI/180.0);
	} else if(angle==0 || angle==180 || angle==360) {
		v.x=v0*cos(angle*M_PI/180.0);
		v.y=0;
	} else {
		v.x=v0*cos(angle*M_PI/180.0);
		v.y=v0*sin(angle*M_PI/180.0);
	}
	
	f.x=-0.5*1.225*v.x*v.x*0.04*0.020;
	f.y=-m*9.8+0.5*1.225*v.y*v.y*0.04*0.020;
	
	cout << f.x << f.y << endl;
	
	cout << "Molq vuvedete delta t: ";cin >> dt;
	
	int i=10;
	while(r.y>0 && i>0) {
		t+=dt;
		r.x+=(v.x/m)*dt;
		r.y+=(v.y/m)*dt;
		v.x+=(f.x/m)*dt;
		v.y+=(f.y/m)*dt;
		
		f.x=-0.5*1.225*v.x*v.x*0.04*0.020;
		f.y=-m*9.8+0.5*1.225*v.y*v.y*0.04*0.020;
		--i;
	}
	
	cout << r.x << ' ' << r.y << ' ' << t << endl;
	
	return 0;
}
