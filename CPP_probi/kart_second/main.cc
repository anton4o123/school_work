#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "card.hh"
using namespace std;

void create_deck(Card c[]) {
	int color;
	for(int i=0;i<52;++i) {
		c[i].set_power(rand()/(RAND_MAX/13)+1);
		color=rand()/(RAND_MAX/4);
		switch(color) {
			case 0: c[i].set_color('P');break;
			case 1: c[i].set_color('K');break;
			case 2: c[i].set_color('R');break;
			case 3: c[i].set_color('S');break;
		}
		
		for(int j=0;j<i;++j) {
			if(c[i].get_power()==c[j].get_power() && c[i].get_color()==c[j].get_color()) {
				--i;
				break;
			}
		}
	}
}

void write_score(int p1, int p2) {
	cout << "               Player1:" << p1 << "    " << "Player2:" << p2 << endl;
}

void write_cards(const Card& c1, const Card& c2) {
	cout << endl << endl << endl;
	cout << "               " << c1.get_type() << ' ' << c1.get_color();
	cout << "               " << c2.get_type() << ' ' << c2.get_color();
	cout << endl;
}

void player_one(Card c1[], Card c2[], int& p1, int& p2) {
	Card temp;
	
	temp=c1[0];
	for(int i=0;i<p1-1;++i) {
		c1[i]=c2[i+1];
	}
	c1[p1-1]=temp;
	c1[p1]=temp;
	++p1;
	
	for(int i=0;i<p2-1;++i) {
		c2[i]=c2[i+1];
	}
	--p2;
}

void player_two(Card c1[], Card c2[], int& p1, int& p2) {
	Card temp;
	
	temp=c2[0];
	for(int i=0;i<p2-1;++i) {
		c2[i]=c1[i+1];
	}
	c1[p2-1]=temp;
	c1[p2]=temp;
	++p2;
	
	for(int i=0;i<p1-1;++i) {
		c1[i]=c2[i+1];
	}
	--p1;
}

void war(Card c1[], Card c2[], int& p1, int & p2, int& i) {
	cout << "                WAR!!!" << endl;
	++i;
	write_cards(c1[i], c2[i]);
	getchar();
	++i;
	write_cards(c1[i], c2[i]);
	getchar();
	++i;
	write_cards(c1[i], c2[i]);
	getchar();
	
	if(c1[i].get_power()>c2[i].get_power()) {
		while(i>=0) {
			player_one(c1, c2, p1, p2);
			--i;
		}
		++i;
	} else if(c1[i].get_power()<c2[i].get_power()) {
		while(i>=0) {
			player_two(c1, c2, p1, p2);
			--i;
		}
		++i;
	} else {
		war(c1, c2, p1, p2, i);
	}
}

int main() {
	srand((unsigned)time(NULL));
	Card main_deck[52];
	Card deck1[52];
	Card deck2[52];
	int player1_score=26, player2_score=26, i=0;
	
	create_deck(main_deck);
	
	for(int i=0;i<26;++i) {
		deck1[i]=main_deck[i];
		deck2[i]=main_deck[i+26];
	}
	
	while(player1_score<52 && player2_score<52) {
		system("clear");
		write_score(player1_score, player2_score);
		write_cards(deck1[i], deck2[i]);
		
		if(deck1[i].get_power()>deck2[i].get_power()) {
			player_one(deck1, deck2, player1_score, player2_score);
		} else if(deck1[i].get_power()<deck2[i].get_power()) {
			player_two(deck1, deck2, player1_score, player2_score);
		} else {
			war(deck1, deck2, player1_score, player2_score, i);
		}
		
		getchar();
	}
	
	return 0;
}
