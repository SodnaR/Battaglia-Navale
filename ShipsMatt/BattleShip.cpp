#include "BattleShip.h"
BattleShip::BattleShip(std::vector<int> bow, std::vector<int> stern){
	dim=5;
	armor=5;
	locateCenter(bow,stern);
}

/*
	Griglia d= griglia di difesa del giocatore che sta venendo puntato dalla BattleShip
	Griglia a=griglia di attacco del giocatore che sta sparando
	valid()= metodo della griglia che controlla che le coordinate rientrino effettivamente nel range 12x12 della griglia
*/

void BattleShip::fire(int x, int y, Griglia d, Griglia a){
	if(d.vaid(x,y){
		if (d[x][y]=='C'||d[x][y]='S'||d[x][y]=='E'){
			a[x][y]='x';
		}else {
			a[x][y]='O'
		}
	}else{
		throw Invalid();
	}
}
