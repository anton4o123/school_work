#include <iostream>
using namespace std;

void copy1(int dst[], int src[], int size) {
	for(int i=0;i<size;i++) {
		dst[i]=src[i];
	}
}

void copy1(double dst[], double src[], int size) {
	for(int i=0;i<size;i++) {
		dst[i]=src[i];
	}
}

void copy_array(void* dst, void* src, int size) {
	for(int i=0;i<size;++i) {
		static_cast<char*>(dst)[i]=static_cast<char*>(src)[i];
	}
}

template<typename T>
void copy2(T dst[], T src[], int size) {
	for(int i=0;i<size;++i) {
		dst[i]=src[i];
	}
}

int main() {
	int a[] = {0,1,2,3,4,5,6,7,8,9};
	int b[10];
	
	copy1(b, a, 10);
	
	for(int i=0;i<10;++i) {
		cout << b[i] << ' ';
	}
	cout << endl;
	
	double e[] = {0.0,1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9};
	double f[10];
	copy1(f, e, 10);
	
	for(int i=0;i<10;++i) {
		cout << f[i] << ' ';
	}
	cout << endl;
	
	copy_array(b, a, sizeof(a));
	
	for(int i=0;i<10;++i) {
		cout << b[i] << ' ';
	}
	cout << endl;
	
	copy_array(f, e, sizeof(e));
	
	for(int i=0;i<10;++i) {
		cout << f[i] << ' ';
	}
	cout << endl;
	
	double ff[10];
	copy_array(ff, a, sizeof(a));
	
	for(int i=0;i<10;++i) {
		cout << ff[i] << ' ';
	}
	cout << endl;
	
	copy2<int>(b, a, 10);
	copy2<double>(f, e, 10);

	for(int i=0;i<10;++i) {
		cout << a[i] << ' ';
	}
	cout << endl;
	
	for(int i=0;i<10;++i) {
		cout << f[i] << ' ';
	}
	cout << endl;
	
//	copy2<int>(f, a, 10);

	return 0;
}
