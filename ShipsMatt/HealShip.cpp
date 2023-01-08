#include "HealShip.H"

HealShip::HealShip(std::vector<int> bow, std::vector<int> stern){
	dim=3;
	armor=3;
	locateCenter(bow,stern);
}

//Griglia d= griglia di difesa del giocatore che ha mosso la HealShip

void HealShip::move(int x, int y, Griglia d){ 	
	if(orien==0){
		if(d[x][y+1]!=' '||d[x][y-1]!=' '){
			throw Invalid();
		}else{
			center[0]=x;
			center[1]=y;
		}
	}else if(orien==1){
		if(d[x+1][y]!=' '||d[x-1][y]!=' '){
			throw Invalid();
		}
	}
}

/*
	Griglia d= griglia di difesa del giocatore che vuole usare heal
	Manca il modo per accedere agli oggetti BattleShip,HealShip, per poter modificare la loro armatura
	Non serve poter accedere a Submarine visto che ha solo 1 di armor e se viene colpito viene distrutto
*/

void HealShip::heal(Griglia d){		
	for(int i=(center[0]-1), i<(center[0]+1), i++){
		for(int j=(center[1]-1), j<(center[1]+1), j++){
			if(d[i][j]=='C'||d[i][j]=='S')
		}
	}
}
