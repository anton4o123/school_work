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
	: head_(0), tail_(0) {}
	
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
	
	T pop_back() {
		Node* del_node=tail_;
		Node* help_node=head_;
		T value=tail_->data_;
		iterator it(head_);
		
		while(true) {
			help_node=it.current_;
			if(help_node->next_==tail_->next_) {
				break;
			}
			it++;
		}
		tail_=help_node;
		tail_->next_=help_node;
		delete del_node;
		return value;
	}
	
	class iterator {
		friend class List;
		Node* current_;
		iterator(Node* current)
		: current_(current) {}
	public:
		iterator& operator++() {
			current_=current_->next_;
			return *this;
		}
		
		iterator operator++(int) {
			iterator res=*this;
			
			current_=current_->next_;
			return res;
		}
		
		int& operator*() {
			return current_->data_;
		}
		
		bool operator==(const iterator& other) const {
			return current_==other.current_;
		}
		
		bool operator!=(const iterator& other) const {
			return !operator==(other);
		}
	};
};

int main() {
	List<int> l1;
	
	cout << l1.empty() << endl;
	l1.push_back(6);
	l1.push_back(5);
	l1.push_front(7);
	l1.push_back(4);
	cout << l1.empty() << endl;
	cout << l1.front() << endl;
	cout << l1.back() << endl;
	cout << l1.pop_front() << endl;
	cout << l1.pop_front() << endl;
	cout << l1.pop_back() << endl;
	cout << l1.empty() << endl;

	return 0;
}
