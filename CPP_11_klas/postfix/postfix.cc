#include <iostream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

double binary_plus(double val1,double val2) {
	return val1+val2;
}

double binary_minus(double val1,double val2) {
	return val1-val2;
}

double binary_mult(double val1,double val2) {
	return val1*val2;
}

double binary_div(double val1,double val2) {
	return val1/val2;
}

void post_binary(list<double>& context,double(*binary_op)(double,double)) {
	if(context.size()<2) {
		cout << "OOPS: too few arguments..." << endl;
		return;
	}
	
	double val2=context.back();
	context.pop_back();
	
	double val1=context.back();
	context.pop_back();
	
	double res=binary_op(val1,val2);
	context.push_back(res);
}

int main() {
	string token;
	list<double> context;

	while(cin) {
		cin >> token;
		if(!cin) {
			cout << "end of file..." << endl;
			break;
		}
		
		if(token=="+") {
			post_binary(context,binary_plus);
		} else if(token=="-") {
			post_binary(context,binary_minus);
		} else if(token=="*") {
			post_binary(context,binary_mult);
		} else if(token=="/") {
			post_binary(context,binary_div);
		}
	}


	return 0;
}
