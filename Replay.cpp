#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
using namespace std;

#include "headers/player_copy.h"
bool customization = false;
int bship_custom = 1, sship_custom = 1, eship_custom = 1;
int ships_custom=bship_custom+sship_custom+eship_custom;
int map_custom = 12;
int turn_custom=1;
void insertShips(Player& p1, Player& p2, string file_name){
	ifstream log;
	log.open(file_name);
	log.ignore(1000, '\n');
	string bow, stern, coord;
    pair<string, string> ship =make_pair("a0","a5");
    Battleship bship(ship.first, ship.second);
    for(int i = 0; i<bship_custom; i++){
		getline(log, coord);
		stringstream ss(coord);
		ss>>bow>>stern;
		bship=Battleship(bow, stern);
		p1.addShip(bow, stern, bship);
    }
    ship=make_pair("a0","a3");
    Support sship(ship.first, ship.second);
    for(int i = 0; i < sship_custom; i++){
		getline(log, coord);
		stringstream ss(coord);
		ss>>bow>>stern;
     	sship=Support (bow, stern);
     	p1.addShip(bow, stern, sship);
    }
   	ship=make_pair("a0","a0");
   	Submarine eship(ship.first, ship.second);
    for(int i = 0; i< eship_custom; i++){
		getline(log, coord);
		stringstream ss(coord);
		ss>>bow;
        stern=bow;
        eship=Submarine (bow, stern); 
        p1.addShip(bow, stern, eship);   
    }
    for(int i = 0; i<bship_custom; i++){
		getline(log, coord);
		stringstream ss(coord);
		ss>>bow>>stern;
		bship=Battleship(bow, stern);
		p2.addShip(bow, stern, bship);
    }
    for(int i = 0; i < sship_custom; i++){
		getline(log, coord);
		stringstream ss(coord);
		ss>>bow>>stern;
     	sship=Support (bow, stern);
     	p2.addShip(bow, stern, sship);
    }
    for(int i = 0; i< eship_custom; i++){
		getline(log, coord);
		stringstream ss(coord);
		ss>>bow;
        stern=bow;
        eship=Submarine (bow, stern); 
        p2.addShip(bow, stern, eship);   
    }
    log.close();
}
void playerTurn(Player& p1, Player& p2, string file_name){
	ifstream log;
	log.open(file_name);
   	string origin, target, coord;
   	char move;   
	getline(log, coord);
	stringstream ss(coord);
	ss>>origin>>target;
	move=p1.getDefenceGrid().getTile(origin);
	switch(move){
		case 'C':
			p1.shot(p1.getShip(origin), target, p2);
			break;
		case 'S':
			p1.move_heal(p1.getShip(origin), target);
			break;
		case 'E':
			p1.move_scan(p1.getShip(origin), target, p2);
		break;		    		
	}
	log.close();
}
void Vreplay(Player& p1, Player& p2, string file_name){   	
	string origin, target, coord;
	string coin;
   	char move;
    insertShips(p1,p2,file_name);
    cout<<"griglie di Player 1: \n"<<p1<<endl;
    cout<<"griglie di Player 2: \n"<<p2<<endl;
    ifstream log;
	log.open(file_name);
	getline(log, coin);
	for(int i=0; i<(ships_custom+1); i++){
		log.ignore(1000,'\n');
	}
    if(coin=="Player1"){
    	cout<<"Player 1 inizia"<<endl;
    	for(int i = 1; i <= turn_custom; i++){
    		getline(log, coord);
			stringstream ss(coord);
			ss>>origin>>target;
    		move=p1.getDefenceGrid().getTile(origin);
			switch(move){
				case 'C':
					p1.shot(p1.getShip(origin), target, p2);
					break;
				case 'S':
					p1.move_heal(p1.getShip(origin), target);
					break;
				case 'E':
					p1.move_scan(p1.getShip(origin), target, p2);
				break;		    		
			}
			getline(log, coord);
			stringstream ss1(coord);
			ss1>>origin>>target;
			move=p2.getDefenceGrid().getTile(origin);
			switch(move){
				case 'C':
					p2.shot(p2.getShip(origin), target, p1);
					break;
				case 'S':
					p2.move_heal(p1.getShip(origin), target);
					break;
				case 'E':
					p2.move_scan(p1.getShip(origin), target, p1);
				break;		    		
			}
			cout<<"player 1 \n"<<p1<<endl;
			cout<<"player 2 \n"<<p2<<endl;
    	}
    }else{
    	cout<<"Player 2 inizia"<<endl;
    	for(int i = 1; i <= turn_custom; i++){
			getline(log, coord);
			stringstream ss(coord);
			ss>>origin>>target;
			move=p2.getDefenceGrid().getTile(origin);
			switch(move){
				case 'C':
					p2.shot(p2.getShip(origin), target, p1);
					break;
				case 'S':
					p2.move_heal(p1.getShip(origin), target);
					break;
				case 'E':
					p2.move_scan(p1.getShip(origin), target, p1);
				break;		    		
			}
			getline(log, coord);
			stringstream ss1(coord);
			ss1>>origin>>target;
    		move=p1.getDefenceGrid().getTile(origin);
			switch(move){
				case 'C':
					p1.shot(p1.getShip(origin), target, p2);
					break;
				case 'S':
					p1.move_heal(p1.getShip(origin), target);
					break;
				case 'E':
					p1.move_scan(p1.getShip(origin), target, p2);
				break;		    		
			}
			cout<<"player 1 \n"<<p1<<endl;
			cout<<"player 2 \n"<<p2<<endl;
    	}
    }
    log.close();
}

void Freplay(Player& p1, Player& p2, string file_name){   	
	string origin, target, coord;
	string coin;
   	char move;
    insertShips(p1,p2, file_name);
    ofstream out;
    out.open("game_log.txt");
    out<<"griglie di Player 1: \n"<<p1<<endl;
    out<<"griglie di Player 2: \n"<<p2<<endl;
    ifstream log;
	log.open(file_name);
	getline(log,coin);
	for(int i=0; i<(ships_custom+1); i++){
		log.ignore(1000,'\n');
	}
    if(coin=="Player1"){
    	out<<"Player 1 inizia"<<endl;
    	for(int i = 1; i <= turn_custom; i++){
    		getline(log, coord);
			stringstream ss(coord);
			ss>>origin>>target;
    		move=p1.getDefenceGrid().getTile(origin);
			switch(move){
				case 'C':
					p1.shot(p1.getShip(origin), target, p2);
					break;
				case 'S':
					p1.move_heal(p1.getShip(origin), target);
					break;
				case 'E':
					p1.move_scan(p1.getShip(origin), target, p2);
				break;		    		
			}
			getline(log, coord);
			stringstream ss1(coord);
			ss1>>origin>>target;
			move=p2.getDefenceGrid().getTile(origin);
			switch(move){
				case 'C':
					p2.shot(p2.getShip(origin), target, p1);
					break;
				case 'S':
					p2.move_heal(p1.getShip(origin), target);
					break;
				case 'E':
					p2.move_scan(p1.getShip(origin), target, p1);
				break;		    		
			}
			out<<"player 1 \n"<<p1<<endl;
			out<<"player 2 \n"<<p2<<endl;
    	}
    }else{
    	out<<"Player 2 inizia"<<endl;
    	for(int i = 1; i <= turn_custom; i++){
			getline(log, coord);
			stringstream ss(coord);
			ss>>origin>>target;
			move=p2.getDefenceGrid().getTile(origin);
			switch(move){
				case 'C':
					p2.shot(p2.getShip(origin), target, p1);
					break;
				case 'S':
					p2.move_heal(p1.getShip(origin), target);
					break;
				case 'E':
					p2.move_scan(p1.getShip(origin), target, p1);
				break;		    		
			}
			getline(log, coord);
			stringstream ss1(coord);
			ss1>>origin>>target;
    		move=p1.getDefenceGrid().getTile(origin);
			switch(move){
				case 'C':
					p1.shot(p1.getShip(origin), target, p2);
					break;
				case 'S':
					p1.move_heal(p1.getShip(origin), target);
					break;
				case 'E':
					p1.move_scan(p1.getShip(origin), target, p2);
				break;		    		
			}
			out<<"player 1 \n"<<p1<<endl;
			out<<"player 2 \n"<<p2<<endl;
    	}
    }
    out.close();
    log.close();
}

int main(){
	char replay_mode; 
	string username, file_name;
	Player p1, p2;
	bool mode=true;
	cout<<"inserire modalità di replay: \n v [nome_file_log] stampa a schermo \n f[nome_file_log] creazione file"<<endl<<endl;
	cin>>replay_mode>>file_name;
	do{
		if(replay_mode=='v'){
			Vreplay(p1,p2,file_name);
		}else if(replay_mode=='f'){
			Freplay(p1,p2,file_name);
			cout<<"file di log creato, nome: [game_log.txt]"<<endl;
		}else{
			cout<<"modalità di replay non pervenuta, inserire modalità valida"<<endl;
			cin>>replay_mode;
			mode=false;
		}
	}while(!mode);
	return 0;
}
