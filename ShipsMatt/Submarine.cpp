#include "Submarine.h"

/*
	Griglia d= griglia di difesa del giocatore che vuole muovere il sottomarino
*/

void Submarine::move(int x, int y, Griglia d){
	if(d[x][y]!=' '){
		throw Invalid();
	}else{
		center[0]=x;
		center[1]=y;
	}
}

/*
	Griglia d= griglia di difesa del giocatore che sta venendo scansionato
	Griglia a= griglia di attacco del giocatore che sta scansionando
*/

void Submarine::scan(Griglia d, Griglia a){
	for(int i=(center[0]-2), i<(center[0]+2), i++){
		for(int j=(center[1]-2), j<(center[1]+2), j++){
			if((d[i][j]=='C'||d[i][j]=='S'||d[i][j]=='E')&&(a[i][j]!='x')||(a[i][j]!='X')){
				a[i][j]='Y';
			}
		}
	}
}
