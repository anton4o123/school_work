#include <iostream>
using namespace std;

int main()
{
	

	for(int i=0;i<10;i++) {
		if(i>0 && i<9) {
			for(int j=0;j<30-i;j++)
				cout << " ";
			cout << "o";
			for(int j=0;j<i*2;j++)
				cout << " ";
			cout << "o";
			cout << endl;
		}
		else {
			for(int j=0;j<30-i;j++)
				cout << " ";
			cout << "o";
			if(!i)
				for(int j=0;j<i;j++)
					cout << " ";
			else {
				for(int j=0;j<i;j++) {
					cout << "o";
					cout << " ";
				}
				cout << "o";
			}
			cout << endl;
		}
	}
}
