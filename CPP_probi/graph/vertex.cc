#include <iostream>
using namespace std;

class Vertex {
	int name_;
	Vertex* v[100];
	int weight[100];
	int vertex;
public:
	Vertex(int name=0)
	: name_(name),vertex(1) {}

	int get_name() {
		return name_;
	}
	
	Vertex* get_vertex(int a) {
		return v[a-1];
	}
	
	int get_weight(int w) {
		return weight[w-1];
	}
	
	void set_vertex(Vertex& other,int w) {
		v[vertex-1]=&other;
		weight[vertex-1]=w;
		vertex++;
	}
};

int main() {
	Vertex v(1),v2(2),vr;
	
	cout << v.get_name() << endl;
	cout << v2.get_name() << endl;
	
	v.set_vertex(v2,100);
	vr=*v.get_vertex(1);
	cout << vr.get_name() << endl;
	
	v2.set_vertex(v,100);
	vr=*v2.get_vertex(1);
	cout << vr.get_name() << endl;

	return 0;
}
