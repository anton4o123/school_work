#include "card.hh"

class CardError{};

Card::Card()
: power_(0), color_('0'), type_('0') {}

Card::Card(const Card& c) {
	power_=c.get_power();
	type_=c.get_type();
	color_=c.get_color();
}

Card::Card(char type, char color)
: type_(type), color_(color) {
	if(type>='2' && type<='9') {
		power_=type-49;
	} else {
		switch(type) {
			case 'T': power_=9;break;
			case 'J': power_=10;break;
			case 'Q': power_=11;break;
			case 'K': power_=12;break;
			case 'A': power_=13;break;
			default: throw CardError();break;
		}
	}
	
	if(color!='P' && color!='K' && color!='R' && color!='S') {
		throw CardError();
	}
}

int Card::get_power() const {
	return power_;
}

char Card::get_type() const {
	return type_;
}

char Card::get_color() const {
	return color_;
}

void Card::set_power(int power) {
	power_=power;
	if(power>=1 && power<=8) {
		type_=power+49;
	} else {
		switch(power) {
			case 9: type_='T';break;
			case 10: type_='J';break;
			case 11: type_='Q';break;
			case 12: type_='K';break;
			case 13: type_='A';break;
			default: throw CardError();break;
		}
	}
}

void Card::set_type(char type) {
	type_=type;
	if(type>='2' && type<='9') {
		power_=type-49;
	} else {
		switch(type) {
			case 'T': power_=9;break;
			case 'J': power_=10;break;
			case 'Q': power_=11;break;
			case 'K': power_=12;break;
			case 'A': power_=13;break;
			default: throw CardError();break;
		}
	}
}

void Card::set_color(char color) {
	color_=color;
	if(color!='P' && color!='K' && color!='R' && color!='S') {
		throw CardError();
	}
}
