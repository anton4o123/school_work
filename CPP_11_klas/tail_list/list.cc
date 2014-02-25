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
//		head_->next_=tail_;
	}
	
	bool empty() {
		return head_==0 && tail_==0;
	}
	
	void push_front(T val) {
		Node* new_node=new Node(val);
		
		if(!empty()) {
			new_node->next_=head_->next_;
			head_->next_=new_node;
		} else {
			new_node->next_=tail_;
			head_->next_=new_node;
			tail_->next_=new_node;
		}
	}
	
	void push_back(T val) {
		Node* new_node=new Node(val);
		
		if(!empty()) {
			//need to finish
		} else {
			new_node->next_=tail_;
			head_->next_=new_node;
			tail_->next_=new_node;
		}
	}
};

int main() {
	List<int> l1;
	
	cout << l1.empty() << endl;
	l1.push_front(6);
	cout << l1.empty() << endl;

	return 0;
}
