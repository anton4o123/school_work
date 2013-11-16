#include <iostream>
using namespace std;


class StackError{};
const int STACK_SIZE=10;
class Stack
{
  int data_[STACK_SIZE];
  int top_;

public:

  Stack()
  {
    top_=0;
  }
  
  bool empty()
  {
  return top_==0;
  }
  
  bool full()
  {
  return top_==STACK_SIZE;
  }
  
  int pop()
  {
  if(empty())
  {
    throw StackError();
  }
  return data_[--top_];
  }
  
  void push(int val)
  {
  if(full())
  {
  throw StackError();
  }
  data_[top_++]=val;
  }

};


int main()
{
  Stack st;
  try {
  st.pop();
  }
  catch(StackError ex)
  {
  cout<<"Stack error..."<<endl;
  }
  st.push(1);
  for(int i=1;i<=10;i++)
  {
  st.push(1);
  }


return 0;
}
