#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class kart {
	char karta_;
	bool boq_;
	char tip_;
public:
	kart(int karta=0,bool boq=0,int tip=0)
	: karta_(karta),boq_(boq),tip_(tip) {}

	char get_karta() {
		return karta_;
	}

	bool get_boq() {
		return boq_;
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

	void set_boq(bool& boq) {
		boq_=boq;
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

int main()
{
	srand((unsigned)time(NULL));
	kart k[52];

	deck(k);

	for(int i=0;i<52;i++)
		cout << k[i].get_karta() << " " << k[i].get_tip() << endl;

	return 0;
}
