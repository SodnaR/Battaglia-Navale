#ifndef HEALSHIP_H
#define HEALSHIP_H
class HealShip: public Ship{
	public:
		HealShip HealShip(std::vector<int> bow, std::vector<int> stern);
		void move(int x, int y, Griglia d);
		void heal(Griglia d);
};
#endif
