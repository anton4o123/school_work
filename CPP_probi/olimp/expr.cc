#include <iostream>
#include <string>
using namespace std;

int main() {
	string brackets;
	int flag=1,i=0,opened=0;
	char control='(';
	
	cin >> brackets;
	while(i<brackets.length()) {
		if(brackets[i]!='(' && brackets[i]!=')' && brackets[i]!='[' && brackets[i]!=']') {
			flag=0;
			break;
		}
		i++;
	}
	
	if(flag==1) {
		i=0;
		while(i<brackets.length()) {
			if(brackets[i]==control) {
				if(control=='(') {
					opened++;
					control=')';
				} else {
					opened--;
					control='(';
				}
			} else {
				opened=1;
				break;
			}
			i++;
		}
		if(opened!=0) {
			flag=0;
		}
	}
	cout << flag << endl;

	return 0;
}
