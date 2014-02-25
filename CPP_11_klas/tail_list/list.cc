#include <iostream>
using namespace std;

template<typename T>
class List {
	struct Node {
		Node* next_;
		T data_;
		
		Node(T val)
		: next_(0), data_(val) {}
	};
	Node* head_;
	Node* tail_;
public:
	List()
	: head_(0), tail_(0) {
	//	head_->next_=tail_;
	}
	
	bool empty() {
		return head_==0;
	}
	
	void push_front(T val) {
		Node* new_node=new Node(val);
		
		if(!empty()) {
			new_node->next_=head_;
			head_=new_node;
			tail_->next_=new_node;
		} else {
			new_node->next_=tail_;
			head_=new_node;
			tail_=new_node;
		}
	}
	
	void push_back(T val) {
		Node* new_node=new Node(val);
		
		if(!empty()) {
			new_node->next_=head_;
			tail_->next_=new_node;
			tail_=new_node;
		} else {
			new_node->next_=tail_;
			head_=new_node;
			tail_=new_node;
		}
	}
	
	T front() {
		return head_->data_;
	}
	
	T back() {
		return tail_->data_;
	}
	
	T pop_front() {
		Node* del_node=head_;
		T value=head_->data_;
		
		head_=head_->next_;
		delete del_node;
		return value;
	}
	
/*	T pop_back() {
		Node* del_node=tail_;
		T value=tail_->data_;
		
		tail_
	}*/
};

int main() {
	List<int> l1;
	
	cout << l1.empty() << endl;
	l1.push_back(6);
	l1.push_back(5);
	cout << l1.empty() << endl;
	cout << l1.front() << endl;
	cout << l1.back() << endl;
	cout << l1.pop_front() << endl;
	cout << l1.pop_front() << endl;
	cout << l1.empty() << endl;

	return 0;
}
