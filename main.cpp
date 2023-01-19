#include "headers/game.h"
using namespace std;

/*
bool customization = false;
int bship_custom = 3, sship_custom = 3, eship_custom = 2;
int map_custom = 9;
int turn_custom = 1000;

vector<Battleship> bships;
vector<Support> sships;
vector<Submarine> eships;

int _pos = 0;

pair<string, string> gen_coordinate(int dim){
    int random_orient = rand()%2;
    random_device rd;
    mt19937 gen(rd());
	uniform_int_distribution<int> rng(0, (map_custom - 1));
    char random_x1 = 'a' + rng(gen), random_x2;
    if(random_x1 >= 'j') random_x1 += 2;
    if(random_x1 >= 'w') random_x1 += 3;
    int random_y = rng(gen) + 1;
    string tile1, tile2;
    if(random_orient){
        tile1 = (1, random_x1);
        tile1 += to_string(random_y);
        tile2 = (1, random_x1);
        tile2 += to_string(random_y+(dim-1));
    } else{
        tile1 = (1, random_x1); 
        tile1 += to_string(random_y);
        random_x2 = (random_x1+(dim-1) > 'j' && dim > 1) ? (random_x1+(dim-1)+2) : random_x1+(dim-1);
        tile2 = (1, random_x2); 
        tile2 += to_string(random_y);
    }
    return make_pair(tile1, tile2);
}

Player botVsbot(){
    Player bot1(map_custom);
    bool listed;
    std::string stern, bow;
    pair<string, string> ship;
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
    std::cout << endl << bot1 <<"--------------------------------"<< std::endl;
    std::cout << endl << bot2 <<"--------------------------------"<< std::endl;
	int move;
    string command = "a0", target = "a0";
	srand(time(NULL));
    bool action, replay = false;
	for(int i = 1; i <= turn_custom; i++){
        std::cout<<endl << "TURNO " << i << endl << std::endl;
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
                std::cout << "sparo: ";
                std::cout << command <<" : "<<target<< std::endl;
                break;
            case 1:
                std::cout << "heal: ";
                std::cout << command <<" : "<<target<< std::endl;
                break;
            case 2:
                std::cout << "scan: ";
                std::cout << command <<" : "<<target<< std::endl;
                break;
        }
        this_thread::sleep_for(chrono::nanoseconds(100000));
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
                std::cout << "sparo: ";
                std::cout << command <<" : "<<target<< std::endl;
                break;
            case 1:
                std::cout << "heal: ";
                std::cout << command <<" : "<<target<< std::endl;
                break;
            case 2:
                std::cout << "scan: ";
                std::cout << command <<" : "<<target<< std::endl;
                break;
        }
        this_thread::sleep_for(chrono::nanoseconds(100));
        std::cout << endl << bot1 <<"--------------------------------"<< std::endl;
        std::cout << endl << bot2 <<"--------------------------------"<< std::endl;
        if(bot1.getDefenceGrid().shipsCounter() == 0){
            return bot2;
        }
        if(bot2.getDefenceGrid().shipsCounter() == 0){
            return bot1;
        }
    }
    return Player("PAREGGIO");
}
*/
Player playerVsbot(){
    Player player, bot1;
    return bot1;
}

void playerVsplayer(){
    
}

int main(){
    Player winner;
    int players;
    string username;

    std::cout << "Benvenuti: prego inserire il numero di giocatori [Max 2]: ";
    cin >> players;
    std::cout <<flush; //flush forces the printing to the screen before it pauses
/*
    std::cout << "Regole custom: ";
    std::cout <<endl<< "Inserire la quantita' di corazzate: ";
    cin >> bship_custom;
    std::cout <<endl<< "Inserire la quantita' di suppoorti: ";
    cin >> sship_custom;
    std::cout <<endl<< "Inserire la quantita' di sottomarini: ";
    cin >> eship_costum;*/
    system("clear");

    switch (players)
    {
    case 0:
        winner = botVsbot(9);
        break;
    case 1:
        //winner = playerVsbot();
        break;
    case 2:
        //winner = playerVsplayer();
        break;
    case 9:
        //testGame();
        break;
    }

    std::cout << "The winner is:" <<winner.getUsername()<< std::endl;
    return 0;
}