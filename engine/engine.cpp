#include "../headers/engine.h"

int bship_custom, sship_custom, eship_custom;
int map_custom;
int turn_custom;

std::vector<Battleship> bships;
std::vector<Support> sships;
std::vector<Submarine> eships;

/*setCustomGame
*   Inizializza tutte le variabili globali
*
*   Tutte le variabili vengono usate sia per modalità:
*   + standard
*   + personalizzata
*/
void setCustomGame(int mapSize, int b_ships, int s_ship, int e_ship, int turns){
    map_custom = mapSize;
    bship_custom = b_ships;
    sship_custom = s_ship;
    eship_custom = e_ship;
    turn_custom = turns;
}

void setCustomGame(std::ifstream& log){
    log>>map_custom>>bship_custom>>sship_custom>>eship_custom>>turn_custom;
}

/*gen_Ships
*   Generatore di navi
*
*   Tutti i tipi di nave generate
*   Quantità in diversa in base alla scelta dell'utente:
*   + standard
*   + custom
*/
void gen_Ships(std::ofstream& log, Player& player){
    bool listed;
    std::string stern, bow;
    std::pair<std::string, std::string> ship;
    for(int i = bship_custom; i > 0; i--, listed = false){
        do{
            ship = gen_coordinate(5);
            stern = ship.first;
            bow = ship.second;
            bships.push_back(Battleship(stern, bow));
            listed = player.addShip(stern, bow, bships[(bships.size() - 1)]);  
        }while(!listed);
        log << stern << " " << bow << std::endl;
    }
    for(int i = sship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(3);
            stern = ship.first; 
            bow = ship.second;
            sships.push_back(Support(stern, bow));
            listed = player.addShip(stern, bow, sships[(sships.size() - 1)]);  
        }while(!listed);
        log << stern << " " << bow << std::endl;   
    }
    for(int i = eship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(1);
            stern = ship.first;
            bow = ship.second;
            eships.push_back(Submarine(stern, bow));
            listed = player.addShip(stern, bow, eships[(eships.size() - 1)]);  
        }while(!listed); 
        log << stern << " " << bow << std::endl;   
    }
}

/*insert_Ships
*   Metodo interattivo per inserire le navi
*
*   Tutti i tipi di nave presenti vengono inseriti in base alla quantità inzializzata
*/
void insert_Ships(std::ofstream& log, Player& player){
    bool listed;
	std::string bow, stern;
    for(int i = 1; i <= bship_custom; i++){
        do{
            std::cout<< "Inserire coordinata prua e poppa cannoniera n." << i << ": ";
			std::cin>>stern>>bow;
            bships.push_back(Battleship(stern, bow));
            listed = player.addShip(stern, bow, bships[(bships.size() - 1)]); 
        	if(listed){
        		std::cout << "cannoniera n." << i << " aggiunta" << std::endl;
        	}else{
            	std::cout << "coordinate non valide" << std::endl;
            }
        }while(!listed);   
        log << stern << " " << bow << std::endl;  
    }
    for(int i = 1; i <= sship_custom; i++){
        do{
            std::cout<< "Inserire coordinata prua e poppa nave supporto n." << i << ": ";
			std::cin>>stern>>bow;
            sships.push_back(Support(stern, bow));
            listed = player.addShip(stern, bow, sships[(sships.size() - 1)]); 
        	if(listed){
        		std::cout << "nave supporto n." << i << " aggiunta" << std::endl;
        	}else{
            	std::cout << "coordinate non valide" << std::endl;
            }
        }while(!listed);
        log << stern << " " << bow << std::endl; 
    }
    for(int i = 1; i <= eship_custom; i++){
        do{
            std::cout<< "Inserire coordinata sottomarino n." << i << ": ";
			std::cin>>stern;
            bow = stern;
            eships.push_back(Submarine(stern, bow));
            listed = player.addShip(stern, bow, eships[(eships.size() - 1)]); 
        	if(listed){
        		std::cout << "sottomarino n." << i << " aggiunto" << std::endl;
        	}else{
            	std::cout << "coordinate non valide" << std::endl;
            }
        }while(!listed);
        log << stern << " " << bow << std::endl; 
    }
}

/*insert_Ships
*   Rileva e scansiione le navi presenti in un file
*
*   Tutti i tipi di nave presenti vengono scansionate in base alla quantità inzializzata
*/
void insert_Ships(std::ifstream& log, Player& player){
    std::string stern, bow, coords;
    std::cout << player << std::endl;
    for(int i = bship_custom; i > 0; i--){
        std::getline(log, coords);
        std::stringstream tiles(coords);
        tiles>>stern>>bow;
        bships.push_back(Battleship(stern, bow));
        player.addShip(stern, bow, eships[(eships.size() - 1)]);  
        std::cout << player << std::endl;
    }
    for(int i = bship_custom; i > 0; i--){
        std::getline(log, coords);
        std::stringstream tiles(coords);
        tiles>>stern>>bow;
        sships.push_back(Support(stern, bow));
        player.addShip(stern, bow, sships[(sships.size() - 1)]);  
    }
    for(int i = bship_custom; i > 0; i--){
        std::getline(log, coords);
        std::stringstream tiles(coords);
        tiles>>stern>>bow;
        eships.push_back(Submarine(stern, bow));
        player.addShip(stern, bow, eships[(eships.size() - 1)]);  
    }
}

/*turn
*   Permette di giocare un turno della partita
*
*   Modidica le plance dei giocatori di conseguenza
*   Riporta nel log le azioni
*/
void turn(std::ofstream& log, Player& player, Player& opponent){
	int move;
    std::string command, target;
    bool action, replay = false;
    move = rand()%3;
    do{
        move = (replay) ? rand()%3 : move;
        replay = false;
        action = false;
        switch(move){
            case 0:
                if(!player.getDefenceGrid().thereIsChar('C')){
                    replay = true;
                }
                command = gen_coordinate(1).first;
                target = gen_coordinate(map_custom).first;
                action = player.shot(player.getShip(command), target, opponent);
                break;
            case 1:
                if(!player.getDefenceGrid().thereIsChar('S')){
                    replay = true;
                }
                command = gen_coordinate(1).first;
                target = gen_coordinate(map_custom).first;
                action = player.move_heal(player.getShip(command), target);
                break;
            case 2:
                if(!player.getDefenceGrid().thereIsChar('E')){
                    replay = true;
                }
                command = gen_coordinate(1).first;
                target = gen_coordinate(map_custom).first;
                action = player.move_scan(player.getShip(command), target, opponent);
                break;
        }
    }while(!action || replay);
    log << command << " " << target << std::endl;  
}

void playerTurn(std::ofstream& log, Player& player, Player& opponent){
   	std::string origin, target;
   	char move = 0;
   	bool done;
	do{    
		std::cout <<"Inserire comando o inserire coordinate per azione di turno (XYOrigin XYTarget): ";
		std::cin>>origin>>target;
        if(origin == target && target == "AA") move = 'V';
        if(origin == target && target == "XX") move = 'R';
        if(std::isupper(origin[0])) origin[0] += 32; 
        if(std::isupper(target[0])) target[0] += 32;
		if(move != 'V' && move != 'R'){
            std::cout << move << std::endl;
            if(player.getDefenceGrid().getTile(origin) == ' '){
			std::cout <<"coordinate di origine non valide, nessuna nave presente, inserire nuove coordinate" << std::endl;
			std::cin>>origin>>target;
		    } else {
	            move = player.getDefenceGrid().getTile(origin);
            }
        }
	}while(move == 0);
	switch(move){
        case 'C':
            do{
                done = player.shot(player.getShip(origin), target, opponent);
				if(!done){
					std::cout <<"coordinate non valide\n" << "inserire nuova coordinata d'attacco valida: ";
					std::cin>>target;
                    if(std::isupper(target[0])) target[0] += 32; 
				}
            }while(!done);
			break;
		case 'S':
			do{
				done = player.move_heal(player.getShip(origin), target);
				if(!done){
					std::cout <<"coordinate non valide\n" << "inserire nuova coordinata destinazione valida non occupata: ";
					std::cin>>target;
                    if(std::isupper(target[0])) target[0] += 32; 
				}
			}while(!done);
			break;
		case 'E':
			do{
				done = player.move_scan(player.getShip(origin), target, opponent);
				if(!done){
					std::cout <<"coordinate non valide\n" << "inserire nuova coordinata destinazione valida non occupata: ";
					std::cin>>target;
                    if(std::isupper(target[0])) target[0] += 32; 
				}
			}while(!done);
        case 'V':
            std::cout << player << std::endl;
            break;
        case 'R':
            player.getDefenceGrid().clear();
            break;
		break;		    		
	}
    switch(move){
        default:
            break;
        case 'C':
            std::cout << "sparo: "<< origin <<" : "<<target<< std::endl;
            break;
        case 'S':
            std::cout << "heal: "<< origin <<" : "<<target<< std::endl;
            break;
        case 'E':
            std::cout << "scan: "<< origin <<" : "<<target<< std::endl;
            break;
    }
    log << origin << " " << target << std::endl;  
}

void vReplay(std::string file_name){
    std::ifstream log(file_name);
    setCustomGame(log);
    std::string move;
    Player exPlayer1("Player1");
    insert_Ships(log, exPlayer1);
    Player exPlayer2("Player2");
    insert_Ships(log, exPlayer2);
/*
    int coin;
    log>>coin;
    while (getline(log, move)){
        std::stringstream tiles(move);
        if(coin){
            replay_turn(tiles, exPlayer1, exPlayer2);
            coin = 0;
        } else {
            replay_turn(tiles, exPlayer2, exPlayer1);
            coin = 1;
        }
    }
   */ 
}

void replay_turn(std::stringstream& tiles, Player& player, Player& opponent){
    std::string command, target;
    tiles>>command>>target;
    std::cout<<"Player: "<<player.getUsername()<< " turn: "<< std::endl;
    switch (player.getDefenceGrid().getTile(command)){
        case 'C':
            player.shot(player.getShip(command), target, opponent);
            std::cout << "sparo: "<< command <<" : "<<target<< std::endl;
            break;
        case 'S':
            player.move_heal(player.getShip(command), target);
            std::cout << "heal: "<< command <<" : "<<target<< std::endl;
            break;
        case 'E':
            player.move_scan(player.getShip(command), target, opponent);
            std::cout << "scan: "<< command <<" : "<<target<< std::endl;
            break;
    }
}


/*gen_coordinates
*   Genera 2 tile utili da poter usare per la creazione di navi con data misura
*
*   Ritorna un paio di stringhe contenenti tile generati casualmente
*/
std::pair<std::string, std::string> gen_coordinate(int dim){
    int random_orient = rand()%2;
    std::random_device rd;
    std::mt19937 gen(rd());
	std::uniform_int_distribution<int> rng(0, (map_custom - 1));
    char random_x1 = 'a' + rng(gen), random_x2;
    if(random_x1 >= 'j') random_x1 += 2;
    if(random_x1 >= 'w') random_x1 += 3;
    int random_y = rng(gen) + 1;
    std::string tile1, tile2;
    if(random_orient){
        tile1 = (1, random_x1);
        tile1 += std::to_string(random_y);
        tile2 = (1, random_x1);
        tile2 += std::to_string(random_y+(dim-1));
    } else{
        tile1 = (1, random_x1); 
        tile1 += std::to_string(random_y);
        random_x2 = (random_x1+(dim-1) > 'j' && dim > 1) ? (random_x1+(dim-1)+2) : random_x1+(dim-1);
        tile2 = (1, random_x2); 
        tile2 += std::to_string(random_y);
    }
    return std::make_pair(tile1, tile2);
}