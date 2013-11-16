#include "kart.cc"

int main()
{
	srand((unsigned)time(NULL));
	kart k[52],p1[52],p2[52];
	int b1=26,b2=26,i=0;

	deck(k);

	for(i=0;i<26;i++) {
		p1[i]=k[i];
		p2[i]=k[i+26];
	}
	result(b1,b2);

	getchar();
	do {
		i=0;
		system("clear");
		result(b1,b2);
		writer(p1,p2,i);
		cout << endl;
		getchar();
		if(p1[i].get_karta()>p2[i].get_karta())
			winner(p1,p2,b1,b2,1);
		else if(p1[i].get_karta()<p2[i].get_karta())
			winner(p1,p2,b1,b2,2);
		else war(p1,p2,b1,b2,i);	
	}
	while((b1!=0)&&(b2!=0));
	system("clear");
	result(b1,b2);
	if(b1==0)
		cout << "\n\n                         POBEDITEL E PLAYER2!!!\n";
	else cout << "\n\n                         POBEDITEL E PLAYER1\n";

	return 0;
}
