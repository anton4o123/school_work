#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class kart {
	char karta_;
	char tip_;
public:
	kart(int karta=0,int tip=0)
	: karta_(karta),tip_(tip) {}

	char get_karta() {
		return karta_;
	}

	char get_tip() {
		return tip_;
	}

	void set_karta(int karta) {
		int k;
		if((karta>0)&&(karta<9)) {
			k=karta+49;
			karta_=k;
		}
		else if(karta==9)
			karta_='T';
		else if(karta==10)
			karta_='J';
		else if(karta==11)
			karta_='Q';
		else if(karta==12)
			karta_='K';
		else if(karta==13)
			karta_='A';
	}

	void set_tip(int tip) {
		if(tip==1)
			tip_='P';
		else if(tip==2)
			tip_='K';
		else if(tip==3)
			tip_='R';
		else if(tip==4)
			tip_='S';
	}

	bool& operator>(kart& k) {
		int k1,k2;
		bool b;

		if(karta_>'1' && karta_<='9')
			k1=karta_;
		else if(karta_=='T')
			k1=58;
		else if(karta_=='J')
			k1=59;
		else if(karta_=='Q')
			k1=60;
		else if(karta_=='K')
			k1=61;
		else if(karta_=='A')
			k1=62;

		if(k.get_karta()>'1' && k.get_karta()<='9')
			k2=k.get_karta();
		else if(k.get_karta()=='T')
			k2=58;
		else if(k.get_karta()=='J')
			k2=59;
		else if(k.get_karta()=='Q')
			k2=60;
		else if(k.get_karta()=='K')
			k2=61;
		else if(k.get_karta()=='A')
			k2=62;

		b=k1>k2;
		return b;
	}

	bool& operator<(kart& k) {
		int k1,k2;
		bool b;

		if(karta_>'1' && karta_<='9')
			k1=karta_;
		else if(karta_=='T')
			k1=58;
		else if(karta_=='J')
			k1=59;
		else if(karta_=='Q')
			k1=60;
		else if(karta_=='K')
			k1=61;
		else if(karta_=='A')
			k1=62;

		if(k.get_karta()>'1' && k.get_karta()<='9')
			k2=k.get_karta();
		else if(k.get_karta()=='T')
			k2=58;
		else if(k.get_karta()=='J')
			k2=59;
		else if(k.get_karta()=='Q')
			k2=60;
		else if(k.get_karta()=='K')
			k2=61;
		else if(k.get_karta()=='A')
			k2=62;

		b=k1<k2;
		return b;
	}
};

void deck(kart k[]) {
	int j=0,t=0;
	for(int i=0;i<52;i++) {
		k[i].set_karta(rand()/(RAND_MAX/13)+1);
		k[i].set_tip(rand()/(RAND_MAX/4)+1);
		if(i) {
			j=0;
			t=0;
			while(j<i) {
				if(k[j].get_karta()==k[i].get_karta()) {
					t++;
					if(t==4) {
						k[i].set_karta(rand()/(RAND_MAX/13)+1);
						k[i].set_tip(rand()/(RAND_MAX/4)+1);
						j=0;
						t=0;
						continue;
					}
					else
						if(k[j].get_tip()==k[i].get_tip()) {
							k[i].set_karta(rand()/(RAND_MAX/13)+1);
							k[i].set_tip(rand()/(RAND_MAX/4)+1);
							j=0;
							t=0;
							continue;
						}
				}
				j++;
			}
		}
	}
}

void result(int b1,int b2) {
	cout << "              Player1:" << b1 << "  " << "Player2:" << b2 << endl;
}

void writer(kart p1[],kart p2[],int i) {
	cout << endl << endl << endl;
	cout << "                   " << p1[i].get_karta() << " " << p1[i].get_tip() << "     " << p2[i].get_karta() << " " << p2[i].get_tip() << endl;
}

void winner(kart p1[],kart p2[],int& b1,int& b2,int j) {
	kart c;

	if(j==1) {
		c=p1[0];
		for(int i=0;i<b1-1;i++)
			p1[i]=p1[i+1];
		p1[b1-1]=c;
		p1[b1]=p2[0];
		p1[b1+1]=0;
		for(int i=0;i<b2-1;i++)
			p2[i]=p2[i+1];
		p2[b2-1]=0;
		b1=b1+1;
		b2=b2-1;
	}
	else if(j==2) {
		c=p2[0];
		for(int i=0;i<b2-1;i++)
			p2[i]=p2[i+1];
		p2[b2-1]=c;
		p2[b2]=p1[0];
		p2[b2+1]=0;
		for(int i=0;i<b1-1;i++)
			p1[i]=p1[i+1];
		p1[b1-1]=0;
		b1=b1-1;
		b2=b2+1;
	}
}

void war(kart p1[],kart p2[],int b1,int b2,int& i) {
cout << "\n                   VOINA!!!\n\n";
i++;
getchar();
writer(p1,p2,i);
i++;
getchar();
writer(p1,p2,i);
i++;
getchar();
writer(p1,p2,i);

if(p1[i].get_karta()>p2[i].get_karta()) {
	winner(p1,p2,b1,b2,1);
	winner(p1,p2,b1,b2,1);
	winner(p1,p2,b1,b2,1);
	winner(p1,p2,b1,b2,1);
	getchar();
}else if(p1[i].get_karta()<p2[i].get_karta()) {
	winner(p1,p2,b1,b2,2);
	winner(p1,p2,b1,b2,2);
	winner(p1,p2,b1,b2,2);
	winner(p1,p2,b1,b2,2);
	getchar();
}else war(p1,p2,b1,b2,i);
}
