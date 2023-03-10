/*Ideatori: Sartori Mattia
*           Zanella Samuele
*
*Autore:    Sartori Mattia
*/
#include "game.h"

/*ship_custom
* + variabile
*
*   Una somma di tutte le navi del giocatore
*   Aggiornato in base alla quantità di navi desiderate
*/
int ships_custom = (bship_custom + sship_custom + eship_custom)*2;

/*vReplay
*	Mostra a schermo il replay di una partita
*
*	Dato un log iniziale ripercorre la partita
*/
void vReplay(std::string file_name){   
    Player p1, p2;	
	std::string origin, target, coord;
	std::string coin;
   	char move;
    std::ifstream log;
	log.open(file_name);
    setCustomGame(file_name);
    log.close();
    insert_Ships(p1,p2,file_name);
    std::cout<<"griglie di Player 1: \n"<<p1<<std::endl;
    std::cout<<"griglie di Player 2: \n"<<p2<<std::endl;
    log.open(file_name);
	log.ignore(1000,'\n');
	getline(log, coin);
	for(int i=0; i<(ships_custom+1); i++){
		log.ignore(1000,'\n');
	}
    while(std::getline(log, coord)){
        if(coin=="Player1"){
            std::cout<<"Player 1 inizia"<<std::endl;
            for(int i = 1; i <= turn_custom ; i++){
                std::stringstream ss(coord);
                ss>>origin>>target;
                std::cout<<"origin: "<<origin<<" target: "<<target<<std::endl;
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
                std::stringstream ss1(coord);
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
                std::cout<<"player 1 \n"<<p1<<std::endl;
                std::cout<<"player 2 \n"<<p2<<std::endl;
            }
        }else{
            std::cout<<"Player 1 inizia"<<std::endl;
            for(int i = 1; i <= turn_custom; i++){
                std::stringstream ss(coord);
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
                std::stringstream ss1(coord);
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
                std::cout<<"player 1 \n"<<p1<<std::endl;
                std::cout<<"player 2 \n"<<p2<<std::endl;
            }
        }   
    }
    log.close();
}


/*fReplay
*	Riporta il replay di una partita in un file
*
*	Dato un log iniziale ripercorre la partita
*/
void fReplay(std::string file_name){   	
    Player p1, p2;
	std::string origin, target, coord;
	std::string coin;
   	char move;
    std::ofstream out;
    std::ifstream log;
	log.open(file_name);
    setCustomGame(file_name);
    log.close();
    insert_Ships(p1,p2, file_name);
    out.open("game_log.txt");
    out<<"griglie di Player 1: \n"<<p1<<std::endl;
    out<<"griglie di Player 2: \n"<<p2<<std::endl;
	log.open(file_name);
	getline(log,coin);
	for(int i=0; i<(ships_custom+1); i++){
		log.ignore(1000,'\n');
	}
    if(coin=="Player1"){
    	out<<"Player 1 inizia"<<std::endl;
    	for(int i = 1; i <= turn_custom; i++){
    		getline(log, coord);
			std::stringstream ss(coord);
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
			std::stringstream ss1(coord);
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
			out<<"player 1 \n"<<p1<<std::endl;
			out<<"player 2 \n"<<p2<<std::endl;
    	}
    }else{
    	out<<"Player 2 inizia"<<std::endl;
    	for(int i = 1; i <= turn_custom; i++){
			getline(log, coord);
			std::stringstream ss(coord);
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
			std::stringstream ss1(coord);
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
			out<<"player 1 \n"<<p1<<std::endl;
			out<<"player 2 \n"<<p2<<std::endl;
    	}
    }
    out.close();
    log.close();
}
