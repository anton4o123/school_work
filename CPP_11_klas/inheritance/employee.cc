#include <iostream>
#include <string>
using namespace std;

class Employee {
	long id_;
	string name_;
public:
	Employee(long id, string name)
	: id_(id), name_(name) {}

	long get_id() const {
		return id_;
	}
	
	const string& get_name() const {
		return name_;
	}
	
	virtual void print() const {
		cout << "id: " << get_id() << "; " << "name: " << get_name() << endl;
	}
};

class Manager: public Employee {
	int level_;
public:
	Manager(long id, string name, int level)
	: Employee(id,name), level_(level) {}
	
	int get_level() const {
		return level_;
	}
	
	virtual void print() const {
		Employee::print();
		cout << "level: " << get_level() << endl;
	}
};

int main() {
	Employee e1(1L,"Anton Georgiev");
	Manager m1(2L,"Ivan Ivanov",3);	
	e1.print();
	m1.print();
	Employee& e2=m1;
	e2.print();

	return 0;
}
