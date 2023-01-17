#include <iostream>
#include <vector>
#include <map>

#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "headers/player.h"

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
int turn_custom = 10;
vector<vector<string>> p1_coordinate, p2_coordinate;

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

string getRandomCoord(vector<string>& copy){
    random_device rd;
    mt19937 gen(rd());
	uniform_int_distribution<int> rng(0, (copy.size() - 1));
    return copy[rng(gen)];
}


Player botVsbot(){
    Player bot1;
    bool listed;
    std::string stern, bow;
    vector<string> coordinates;
    pair<string, string> ship = gen_coordinate(5);
    Battleship bship(ship.first, ship.second);
    for(int i = bship_custom; i > 0; i--, listed = false){
        do{
            ship = gen_coordinate(5);
            stern = ship.first;
            bow = ship.second;
            bship = Battleship(stern, bow);
            listed = bot1.addShip(stern, bow, bship);
        }while(!listed);
        coordinates.push_back(bship.getCenter());
    }
    p1_coordinate.push_back(coordinates);
    coordinates = {};
    ship = gen_coordinate(3);
    Support sship(ship.first, ship.second);
    for(int i = sship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(3);
            stern = ship.first; 
            bow = ship.second;
            sship = Support(stern, bow);
            listed = bot1.addShip(stern, bow, sship);
        }while(!listed);    
        coordinates.push_back(sship.getCenter());
    }
    p1_coordinate.push_back(coordinates);
    coordinates = {};
    ship = gen_coordinate(1);
    Submarine eship(ship.first, ship.second);
    for(int i = eship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(1);
            stern = ship.first;
            bow = ship.second;
            eship = Submarine(stern, bow);
            listed = bot1.addShip(stern, bow, eship);
        }while(!listed);   
        coordinates.push_back(eship.getCenter()); 
    }
    p1_coordinate.push_back(coordinates);
    
    Player bot2;
    for(int i = bship_custom; i > 0; i--, listed = false){
        do{
            ship = gen_coordinate(5);
            stern = ship.first;
            bow = ship.second;
            bship = Battleship(stern, bow);
            listed = bot2.addShip(stern, bow, bship);
        }while(!listed);   
        coordinates.push_back(bship.getCenter()); 
    }
    p2_coordinate.push_back(coordinates);
    coordinates = {};
    for(int i = sship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(3);
            stern = ship.first; 
            bow = ship.second;
            sship = Support(stern, bow);
            listed = bot2.addShip(stern, bow, sship);
        }while(!listed);    
        coordinates.push_back(sship.getCenter()); 
    }
    p2_coordinate.push_back(coordinates);
    coordinates = {};
    for(int i = eship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(1);
            stern = ship.first;
            bow = ship.second;
            eship = Submarine(stern, bow);
            listed = bot2.addShip(stern, bow, eship);
        }while(!listed);    
        coordinates.push_back(eship.getCenter()); 
    }
    p2_coordinate.push_back(coordinates);
    coordinates = {};

    std::cout << endl << bot1 <<"--------------------------------"<< std::endl;
    std::cout << endl << bot2 <<"--------------------------------"<< std::endl;

	int move;
    string command, target;
	srand(time(NULL));
	for(int i = 1; i <= turn_custom; i++){
        std::cout<<endl << "TURNO " << i << endl << std::endl;
		move=rand()%3;
        std::cout<<"Player: "<<bot1.getUsername()<< " turn: "<< std::endl;
		switch(move){
        case 0:
            std::cout << "sparo: ";
                command = getRandomCoord(p1_coordinate[0]);
                target = gen_coordinate(map_custom).first;
                std::cout << command <<" : "<<target<< std::endl;
                bot1.shot(bot1.getShip(command), target, bot2);
                break;
            case 1:
                std::cout << "heal: ";
                command = getRandomCoord(p1_coordinate[1]);
                target = gen_coordinate(map_custom).first;
                std::cout << command <<" : "<<target<< std::endl;
                bot1.move_heal(bot1.getShip(command), target);
                break;
            case 2:
                std::cout << "scan: ";
                command = getRandomCoord(p1_coordinate[2]);
                target = gen_coordinate(map_custom).first;
                std::cout << command <<" : "<<target<< std::endl;
                bot1.move_scan(bot1.getShip(command), target, bot2);
                break;
        }
        move=rand()%3;
        std::cout<<"Player "<<bot2.getUsername()<< " turn: "<< std::endl;
        switch(move){
        case 0:
            std::cout << "sparo: ";
                command = getRandomCoord(p2_coordinate[0]);
                target = gen_coordinate(map_custom).first;
                std::cout << command <<" : "<<target<< std::endl;
            bot2.shot(bot2.getShip(command), target, bot1);
                break;
            case 1:
                std::cout << "heal: ";
                command = getRandomCoord(p2_coordinate[1]);
                target = gen_coordinate(map_custom).first;
                std::cout << command <<" : "<<target<< std::endl;
                bot2.move_heal(bot2.getShip(command), target);
                break;
            case 2:
                std::cout << "scan: ";
                command = getRandomCoord(p2_coordinate[2]);
                target = gen_coordinate(map_custom).first;
                std::cout << command <<" : "<<target<< std::endl;
                bot2.move_scan(bot2.getShip(command), target, bot1);
            break;
        }
    }
    std::cout << endl << bot1 <<"--------------------------------"<< std::endl;
    std::cout << endl << bot2 <<"--------------------------------"<< std::endl;

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
        winner = playerVsbot();
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
    }

    //testGame(p1, p2);
    return 0;
}