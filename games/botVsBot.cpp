#include "../headers/game.h"

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

/*botVsbot
*   Funzione principale dove si scontrano due giocatori comandati dalla IA
*   Inizializza una partita standard o custom a piacimento del giocatore
*   
*   Ritorna il giocatore vincitore
*   + In caso di parità una situazione neutra di pareggio
*/
Player botVsbot(int mapSize, int b_ships, int s_ship, int e_ship, int turns){
    setCustomGame(mapSize, b_ships, s_ship, e_ship, turns);
    std::ofstream log("log.txt");

    //Creazione dei bot in automatico
    Player bot1(map_custom);
    bool listed;
    std::string stern, bow;
    std::pair<std::string, std::string> ship;
    for(int i = bship_custom; i > 0; i--, listed = false){
        do{
            ship = gen_coordinate(5);
            stern = ship.first;
            bow = ship.second;
            bships.push_back(Battleship(stern, bow));
            listed = bot1.addShip(stern, bow, bships[(bships.size() - 1)]);  
        }while(!listed);
    }
    for(int i = sship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(3);
            stern = ship.first; 
            bow = ship.second;
            sships.push_back(Support(stern, bow));
            listed = bot1.addShip(stern, bow, sships[(sships.size() - 1)]);  
        }while(!listed);   
    }
    for(int i = eship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(1);
            stern = ship.first;
            bow = ship.second;
            eships.push_back(Submarine(stern, bow));
            listed = bot1.addShip(stern, bow, eships[(eships.size() - 1)]);  
        }while(!listed);    
    }
    Player bot2(map_custom);
    for(int i = bship_custom; i > 0; i--, listed = false){
        do{
            ship = gen_coordinate(5);
            stern = ship.first;
            bow = ship.second;
            bships.push_back(Battleship(stern, bow));
            listed = bot2.addShip(stern, bow, bships[(bships.size() - 1)]);
        }while(!listed);    
    }
    for(int i = sship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(3);
            stern = ship.first; 
            bow = ship.second;
            sships.push_back(Support(stern, bow));
            listed = bot2.addShip(stern, bow, sships[(sships.size() - 1)]);
        }while(!listed);     
    }
    for(int i = eship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(1);
            stern = ship.first;
            bow = ship.second;
            eships.push_back(Submarine(stern, bow));
            listed = bot2.addShip(stern, bow, eships[(eships.size() - 1)]);  
        }while(!listed);    
    }

	int move;
    std::string command = "a0", target = "a0";
	srand(std::time(NULL));
    bool action, replay = false;
    //Inizio partita
    std::cout << std::endl << bot1 <<"--------------------------------"<< std::endl;
    std::cout << std::endl << bot2 <<"--------------------------------"<< std::endl;
	for(int i = 1; i <= turn_custom; i++){
        std::cout << std::endl << "TURNO " << i << std::endl << std::endl;
        //turno giocatore 1
        move = rand()%3;
        do{
		    move = (replay) ? rand()%3 : move;
            replay = false;
            action = false;
            switch(move){
                case 0:
                    if(!bot1.getDefenceGrid().thereIsChar('C')){
                        replay = true;
                    }
                    command = gen_coordinate(1).first;
                    target = gen_coordinate(map_custom).first;
                    action = bot1.shot(bot1.getShip(command), target, bot2);
                    break;
                case 1:
                    if(!bot1.getDefenceGrid().thereIsChar('S')){
                        replay = true;
                    }
                    command = gen_coordinate(1).first;
                    target = gen_coordinate(map_custom).first;
                    action = bot1.move_heal(bot1.getShip(command), target);
                    break;
                case 2:
                    if(!bot1.getDefenceGrid().thereIsChar('E')){
                        replay = true;
                    }
                    command = gen_coordinate(1).first;
                    target = gen_coordinate(map_custom).first;
                    action = bot1.move_scan(bot1.getShip(command), target, bot2);
                    break;
            }
        }while(!action || replay);
        std::cout<<"Player: "<<bot1.getUsername()<< " turn: "<< std::endl;
        switch(move){
            case 0:
                std::cout << "sparo: "<< command <<" : "<<target<< std::endl;
                break;
            case 1:
                std::cout << "heal: "<< command <<" : "<<target<< std::endl;
                break;
            case 2:
                std::cout << "scan: "<< command <<" : "<<target<< std::endl;
                break;
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(100000));
        //turno giocatore 2
        move = rand()%3;
        do{
		    move= (replay) ? rand()%3 : move;
            replay = false;
            action = false;
            switch(move){
            case 0:
                    if(!bot2.getDefenceGrid().thereIsChar('C')){
                        replay = true;
                    }
                    command = gen_coordinate(1).first;
                    target = gen_coordinate(map_custom).first;
                    action = bot2.shot(bot2.getShip(command), target, bot1);
                    break;
                case 1:
                    if(!bot2.getDefenceGrid().thereIsChar('S')){
                        replay = true;
                    }
                    command = gen_coordinate(1).first;
                    target = gen_coordinate(map_custom).first;
                    action = bot2.move_heal(bot2.getShip(command), target);
                    break;
                case 2:
                    if(!bot2.getDefenceGrid().thereIsChar('E')){
                        replay = true;
                    }
                    command = gen_coordinate(1).first;
                    target = gen_coordinate(map_custom).first;
                    action = bot2.move_scan(bot2.getShip(command), target, bot1);
                break;
            }
        }while(!action || replay);
        std::cout<<"Player "<<bot2.getUsername()<< " turn: "<< std::endl;
        switch(move){
            case 0:
                std::cout << "sparo: "<< command <<" : "<<target<< std::endl;
                break;
            case 1:
                std::cout << "heal: "<< command <<" : "<<target<< std::endl;
                break;
            case 2:
                std::cout << "scan: "<< command <<" : "<<target<< std::endl;
                break;
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(100));
        std::cout << std::endl << bot1 <<"--------------------------------"<< std::endl;
        std::cout << std::endl << bot2 <<"--------------------------------"<< std::endl;
        //fine turno di gioco
        if(bot1.getDefenceGrid().shipsCounter() == 0){
            return bot2;
        }
        if(bot2.getDefenceGrid().shipsCounter() == 0){
            return bot1;
        }
    }
    log.close();
    return Player("PAREGGIO");
}
