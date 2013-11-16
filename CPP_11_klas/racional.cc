#include <iostream>
using namespace std;

class Rational
{
long num_;
long den_;

long evklid(long a,long b)
{
  while(b!=0)
  {
  long temp=a;
  a=b;
  b=temp%a;
  }
  return a;
  }

  void normalize()
  {
  long d=evklid(num_,den_);
  num_/=d;
  den_/=d;
  }

public:
  Rational(long num,long den)
  {
  long d=evklid(num_,den_);
  num_=num;
  den_=den;
  normalize();
  }

  void print()
  {
  cout<<"("<<num_<<"/"<<den_<<")"<<endl;
  }

  void add(Rational r)
  {
  num_=num_*r.den_+den_*r.num_;
  den_=den_*r.den_;
  normalize();
  }

  void sub(Rational r)
  {
  num_=num_*r.den_-den_*r.num_;
  den_=den_*r.den_;
  normalize();
  }

  void mul(Rational r)
  {
  num_*=r.num_;
  den_*=r.den_;
  normalize();
  }

  void dev(Rational r)
  {
  num_*=r.den_;
  den_*=r.num_;
  normalize();
  }
};

int main()
{
Rational r1(1,2);
Rational r2(3,4);

r1.print();
r2.print();
cout<<endl;
r1.add(r2);
r1.print();
cout<<endl;
r1.sub(r2);
r1.print();
cout<<endl;
r1.mul(r2);
r1.print();
cout<<endl;
r1.dev(r2);
r1.print();


return 0;
}
