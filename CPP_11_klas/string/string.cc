#include <iostream>
#include <cstring>
using namespace std;

class StringError{};
class String {
	int capacity_, size_;
	char *buffer_;
	
	void ensure_capacity(int cap) {
		if(capacity_>=cap) {
			return;
		}
		char *tmp=buffer_;
		capacity_=cap;
		buffer_=new char[capacity_];
		strcpy(buffer_, tmp);
		delete [] tmp;
	}
	
	friend ostream& operator<<(ostream&, const String&);
public:
	String(int capacity)
	: capacity_(capacity), size_(0), buffer_(new char[capacity_]) {
		buffer_[0]='\0';
	}
	
	~String() {
		delete [] buffer_;
	}
	
	String(const char *str)
	: capacity_(0), size_(0), buffer_(0) {
		size_=strlen(str);
		capacity_=size_+1;
		buffer_=new char[capacity_];
		strcpy(buffer_, str);
	}
	
	String& operator+=(const String& s) {
		ensure_capacity(size_+s.size_+1);
		strcat(buffer_, s.buffer_);
		return *this;
	}
	
	int size() const {
		return size_;
	}
	
	int length() const {
		return size_;
	}
	
	int capacity() const {
		return capacity_;
	}
	
	bool empty() const {
		return size_==0;
	}
	
	void clear() {
		size_=0;
		buffer_[0]='\0';
	}
	
	char& operator[](int index) {
		return buffer_[index];
	}
	
	char& at(int index) {
		if(index<=size_) {
			return buffer_[index];
		}
		throw StringError();
	}
	
	bool operator==(const String& other) {
		return strcmp(buffer_, other.buffer_)==0;
	}
	
	bool operator!=(const String& other) {
		return strcmp(buffer_, other.buffer_)!=0;
	}
	
	bool operator<(const String& other) {
		return strcmp(buffer_, other.buffer_)<0;
	}
	
	bool operator>(const String& other) {
		return strcmp(buffer_, other.buffer_)>0;
	}
	
	bool operator<=(const String& other) {
		bool res=strcmp(buffer_, other.buffer_);
		return (res==0 || res<0);
	}
	
	bool operator>=(const String& other) {
		bool res=strcmp(buffer_, other.buffer_);
		return (res==0 || res>0);
	}
	
	String(const String& other) {
		size_=other.size();
		capacity_=other.capacity();
		buffer_=new char[other.capacity()];
		strcat(buffer_, other.buffer_);
	}
	
	String operator=(const String& other) {
		size_=other.size();
		capacity_=other.capacity();
		buffer_=new char[other.capacity()];
		strcat(buffer_, other.buffer_);
	}
	
	class iterator {
		char *symbol_;
		
		friend class String;
	public:
		iterator operator++() {
			symbol_++;
			return *this;
		}
		
		iterator operator++(int) {
			iterator old=*this;
			symbol_++;
			return old;
		}
		
		bool operator==(const iterator& other) {
			return symbol_==other.symbol_;
		}
		
		bool operator!=(const iterator& other) {
			return symbol_!=other.symbol_;
		}
		
		char& operator*() {
			return *symbol_;
		}
	};
	
	iterator begin() const {
		iterator it;
		it.symbol_=buffer_;
		return it;
	}
	
	iterator end() const {
		iterator it;
		it.symbol_=&buffer_[size_];
		return it;
	}
};

ostream& operator<<(ostream& out, const String& s) {
	out << s.buffer_;
	return out;
}

int main() {
	String s1("Hello");
	String s2("World!");
	
	cout << s1 << endl;
	cout << s2 << endl;
	s1+=s2;
	cout << s1 << endl;
	
	return 0;
}
