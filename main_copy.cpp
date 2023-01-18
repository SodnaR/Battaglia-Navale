#include <iostream>
#include <vector>
#include <map>

#include <random>
#include <cstdlib>
#include <ctime>

#include<thread>
#include<chrono>

using namespace std;

#include "headers/player_copy.h"

int testGame(Player p1, Player p2){
    pair<string, string>    s1("a1", "a5"),
                            s2("h1", "l1"),
                            s3("n7", "n11"),
                            s4("i4", "i8"),

                            s5("c3", "c5"),
                            s6("g7", "g9"),
                            s7("h1", "h3"),
                            s8("i9", "m9"),

                            s9("d9", "d9"),
                            s0("d11", "d11");

    Battleship bs1(s1.first, s1.second), bs2(s2.first, s2.second), bs3(s3.first, s3.second), bs4(s4.first, s4.second);
    Support    ss1(s5.first, s5.second), ss2(s6.first, s6.second), ss3(s7.first, s7.second), ss4(s8.first, s8.second);
    Submarine  es1(s9.first, s9.second), es2(s0.first, s0.second);

    p1.addShip(s1.first, s1.second, bs1);
    p2.addShip(s2.first, s2.second, bs2);
    p1.addShip(s3.first, s3.second, bs3);
    p2.addShip(s4.first, s4.second, bs4);

    p1.addShip(s5.first, s5.second, ss1);
    p2.addShip(s6.first, s6.second, ss2);
    p1.addShip(s7.first, s7.second, ss3);
    p2.addShip(s8.first, s8.second, ss4);

    p1.addShip(s9.first, s9.second, es1);
    p2.addShip(s0.first, s0.second, es2);
    
    std::map<std::string, std::shared_ptr<Ship>>::iterator it = p1.shipLegend().begin();
    while (it != p1.shipLegend().end()){
        std::cout << it->first<<": ["<<it->second->getId()<<"] <="<<it->second->getCenter() << std::endl;
        it++;
    }     

    //p1.move_heal(p1.getShip(s5.first), "m7");
    p1.shot(p1.getShip(s1.first), "i9", p2);
    p2.shot(p2.getShip(s2.first), "a1", p1);
    p1.shot(p1.getShip(s1.first), "l9", p2);
    p2.shot(p2.getShip(s2.first), "a4", p1);

    cout<<"Player 1:\n"<<p1<<endl<<"------------------------------------------------"<<endl;
    cout<<"Player 2:\n"<<p2<<endl<<"------------------------------------------------"<<endl;

    p1.move_scan(p1.getShip(s9.first), "m7", p2);
    p2.move_heal(p2.getShip(s6.first), "h9");

    cout<<"Player 1:\n"<<p1<<endl<<"------------------------------------------------"<<endl;
    cout<<"Player 2:\n"<<p2<<endl<<"------------------------------------------------"<<endl;

    p1.move_scan(p1.getShip(s9.first), "l8", p2);

    cout<<"Player 1:\n"<<p1<<endl<<"------------------------------------------------"<<endl;
    return 0;
}

bool customization = false;
int bship_custom = 3, sship_custom = 3, eship_custom = 2;
int map_custom = 12;
int turn_custom = 1000;
vector<string> p1_coordinate, p2_coordinate;
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

string getRandomCoord(){
    string output = gen_coordinate(1).first;
    return output;
}


Player botVsbot(){
    Player bot1;
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
        p1_coordinate.push_back(bships[(bships.size() - 1)].getCenter());
    }
    for(int i = sship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(3);
            stern = ship.first; 
            bow = ship.second;
            sships.push_back(Support(stern, bow));
            listed = bot1.addShip(stern, bow, sships[(sships.size() - 1)]);  
        }while(!listed);   
        p1_coordinate.push_back(sships[(sships.size() - 1)].getCenter());
    }
    for(int i = eship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(1);
            stern = ship.first;
            bow = ship.second;
            eships.push_back(Submarine(stern, bow));
            listed = bot1.addShip(stern, bow, eships[(eships.size() - 1)]);  
        }while(!listed);    
        p1_coordinate.push_back(eships[(eships.size() - 1)].getCenter()); 
    }
    
    Player bot2;
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
        p1_coordinate.push_back(eships[(eships.size() - 1)].getCenter()); 
    }
    
    std::cout << endl << bot1 <<"--------------------------------"<< std::endl;
    std::cout << endl << bot2 <<"--------------------------------"<< std::endl;

	int move;
    string command = "a0", target = "a0";
	srand(time(NULL));
    bool action, replay = false;
	for(int i = 1; i <= turn_custom; i++){
        std::cout<<endl << "TURNO " << i << endl << std::endl;
        std::cout<<"Player: "<<bot1.getUsername()<< " turn: "<< std::endl;
        move = rand()%3;
        do{
		    move = (replay) ? rand()%3 : move;
            replay = false;
            action = false;
            switch(move){
                case 0:
                    if(!bot1.getDefenceGrid().thereIsChar('C')) return bot2;
                    command = getRandomCoord();
                    target = gen_coordinate(map_custom).first;
                    action = bot1.shot(bot1.getShip(command), target, bot2);
                    break;
                case 1:
                    if(!bot1.getDefenceGrid().thereIsChar('S')){
                        replay = true;
                    }
                    command = getRandomCoord();
                    target = gen_coordinate(map_custom).first;
                    action = bot1.move_heal(bot1.getShip(command), target);
                    p1_coordinate.push_back(target);
                    break;
                case 2:
                    if(!bot1.getDefenceGrid().thereIsChar('E')){
                        replay = true;
                    }
                    command = getRandomCoord();
                    target = gen_coordinate(map_custom).first;
                    action = bot1.move_scan(bot1.getShip(command), target, bot2);
                    p1_coordinate.push_back(target);
                    break;
            }
        }while(!action || replay);
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
        std::cout<<"Player "<<bot2.getUsername()<< " turn: "<< std::endl;
        move = rand()%3;
        do{
		    move= (replay) ? rand()%3 : move;
            replay = false;
            action = false;
            switch(move){
            case 0:
                    if(!bot2.getDefenceGrid().thereIsChar('C')) return bot1;
                    command = getRandomCoord();
                    target = gen_coordinate(map_custom).first;
                    command = getRandomCoord();
                    target = gen_coordinate(map_custom).first;
                    action = bot2.shot(bot2.getShip(command), target, bot1);
                    break;
                case 1:
                    if(!bot2.getDefenceGrid().thereIsChar('S')){
                        replay = true;
                    }
                    command = getRandomCoord();
                    target = gen_coordinate(map_custom).first;
                    action = bot2.move_heal(bot2.getShip(command), target);
                    p2_coordinate.push_back(target);
                    break;
                case 2:
                    if(!bot2.getDefenceGrid().thereIsChar('E')){
                        replay = true;
                    }
                    command = getRandomCoord();
                    target = gen_coordinate(map_custom).first;
                    action = bot2.move_scan(bot2.getShip(command), target, bot1);
                    p2_coordinate.push_back(target);
                break;
            }
        }while(!action || replay);
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
    std::cout << endl << bot1 <<"--------------------------------"<< std::endl;
    std::cout << endl << bot2 <<"--------------------------------"<< std::endl;

    }

    return bot1;
}

Player playerVsbot(){
    Player player, bot1;
    return bot1;
}

void playerVsplayer(){
    
}

int main(){
    Player winner, p1, p2;
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
       winner = botVsbot();
        break;
    case 1:
        std::cout << "Inserire il proprio username: ";
        cin >> username;
        p1.setUsername(username);
        std::cout << p1.getUsername() << std::endl;
        //winner = playerVsbot();
        break;
    case 2:
        std::cout << "Player 1 - Inserire il proprio username: ";
        cin >> username;
        p1.setUsername(username);
        std::cout << endl << "Player 2 - Inserire il proprio username: ";
        cin >> username;
        p2.setUsername(username);
        std::cout << p1.getUsername() << p2.getUsername() << std::endl;
        //winner = playerVsplayer();
        break;
    case 9:
        testGame(p1, p2);
        break;
    }

    return 0;
}