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
int map_custom = 12;
int turn_custom=1;
void insertShips(Player& p1, Player& p2){
	ifstream log;
	log.open("log.txt");
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
void playerTurn(Player& p1, Player& p2){
	ifstream log;
	log.open("log.txt");
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
}
void replay(int starter, Player& p1, Player& p2){
	int coin=starter;   	
	string origin, target, coord;
   	char move;   
    insertShips(p1,p2);
    cout<<"griglie di Player 1: \n"<<p1<<endl;
    cout<<"griglie di Player 2: \n"<<p2<<endl;
    ifstream log;
	log.open("log.txt");
	for(int i=0; i<6; i++){
		log.ignore(1000,'\n');
	}
    if(coin==0){
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
}

int main(){
	int game_mode;
	string username;
	Player p1, p2;
	ifstream log;
	log.open("log.txt");
	replay(0,p1,p2);
	log.close();
	return 0;
}
