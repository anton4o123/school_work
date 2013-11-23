#include <iostream>
using namespace std;

class ListError {};

class List {
	struct Node {
		Node* next_;
		Node* prev_;
		int data_;
		
		Node(int val)
		: next_(0),prev_(0),data_(val) {}
	};
	
	Node* head_;
public:
	List()
	: head_(new Node(0)) {
		head_->next_=head_->prev_=head_;
	}
	
	~List() {
		while(!empty()) {
			pop_front();
		}
		delete head_;
	}
	
	bool empty() const {
		return head_->next_==head_;
	}
	
	void push_front(int val) {
		Node* front=head_->next_;
		Node* ptr=new Node(val);
		
		head_->next_=ptr;
		ptr->prev_=head_;
		
		head_->prev_=ptr;
		ptr->next_=front;
	}
	
	void push_back(int val) {
		Node* back=head_->prev_;
		Node* ptr=new Node(val);
		
		back->next_=ptr;
		ptr->prev_=back;
		
		ptr->next_=head_;
		head_->prev_=ptr;
	}
	
	int front() {
		if(empty())
			throw ListError();
		return head_->next_->data_;
	}
	
	int back() {
		if(empty())
			throw ListError();
		return head_->prev_->data_;
	}
	
	void pop_front() {
		if(empty())
			throw ListError();
		Node* front=head_->next_;
		Node* new_front=front->next_;
		
		new_front->prev_=head_;
		head_->next_=new_front;
		
		delete front;
	}
	
	void pop_back() {
		if(empty())
			throw ListError();
		Node* back=head_->prev_;
		Node* new_back=back->prev_;
		
		head_->prev_=new_back;
		new_back->next_=head_;
		
		delete back;
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
			return ! operator==(other);
		}
	};
	
	iterator begin() const {
		return iterator(head_->next_);
	}
	
	iterator end() const {
		return iterator(head_);
	}
	
	iterator insert(iterator it,int val) {
		Node* n=new Node(val);
		Node* prev=it.current_->prev_;
		
		n->next_=it.current_;
		it.current_->prev_=n;
		
		prev->next_=n;
		n->prev_=prev;
		
		return iterator(n);
	}
	
	iterator erase(iterator pos) {
		Node* curr=pos.current_;
		Node* next=curr->next_;
		Node* prev=curr->prev_;
		
		next->prev_=prev;
		prev->next_=next;
		
		delete curr;
		return iterator(next);
	}

};	

int main() {
	List ls;
	
	cout << "ls.empty()?:" << ls.empty() << endl;
	ls.push_front(1);
	cout << "ls.empty()?:" << ls.empty() << endl;
	ls.push_back(2);
	cout << "ls.empty()?:" << ls.empty() << endl;
	cout << "ls.front(): " << ls.front() << endl;
	ls.push_back(3);
	cout << "ls.back(): " << ls.back() << endl;
	ls.pop_front();
	cout << "ls.front(): " << ls.front() << endl;
	ls.pop_back();
	cout << "ls.back()?:" << ls.back() << endl;
	
	List::iterator it=ls.begin();
	ls.push_back(5);
	it++;
	cout << "iterator : " << *it << endl;
	*it=6;
	cout << "iterator : " << *it << endl;
	if(it!=ls.end())
		cout << "The iterator isn't in the end!" << endl;
	cout << endl;
	it=ls.insert(it,4);
	for(List::iterator it2=ls.begin();it2!=ls.end();it2++)
		cout << "iterator : " << *it2 << endl;
	ls.erase(it);
	for(List::iterator it2=ls.begin();it2!=ls.end();it2++)
		cout << "iterator : " << *it2 << endl;

	return 0;
}
