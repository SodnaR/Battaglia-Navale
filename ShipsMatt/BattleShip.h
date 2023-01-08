#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include "Ship.h"
class BattleShip: public Ship{
	public:
		BattleShip BattleShip(std::vector<int> bow, std::vector<int> stern);
		void move(int x, int y){throw Invalid()};
		void fire(int x, int y, Griglia d, Griglia a);
};

#endif
