#include <iostream>
#include <string>
using namespace std;

int main() {
	string brackets;
	int flag=1,i=0,opened=0,big_opened=0;
	char control='(',big_control='[';
	
	cin >> brackets;
	
	if(flag==1) {
		i=0;
		while(i<brackets.length()) {
			if(brackets[i]==big_control) {
				if(big_control=='[') {
					big_opened++;
					big_control=']';
				} else {
					big_opened--;
					big_control='[';
				}
			} else {
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
			}
			i++;
		}
		if(opened!=0 || big_opened!=0) {
			flag=0;
		}
	}
	cout << flag << endl;

	return 0;
}
