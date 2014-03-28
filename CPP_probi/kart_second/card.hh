#ifndef CARD_HH__
#define CARD_HH__

class Card {
	int power_;
	char type_, color_;
public:
	Card();
	Card(const Card& c);
	Card(char type, char color);
	
	int get_power() const;
	char get_type() const;
	char get_color() const;
	
	void set_power(int power);
	void set_type(char type);
	void set_color(char color);
};

#endif
