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

    p1.move_scan(p1.getShip("m7"), "l8", p2);

    cout<<"Player 1:\n"<<p1<<endl<<"------------------------------------------------"<<endl;

    return 0;
}

bool customization = false;
int bship_custom = 3, sship_custom = 3, eship_custom = 2;
int map_custom = 12;
int turn_custom = 10;
vector<string> p1_coordinate, p2_coordinate;

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

Player randomFieldGenerator(){
    Player randomField;
    pair<string, string> ship = gen_coordinate(5);
    Battleship bship(ship.first, ship.second);
    for(int i = bship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(5);
            bship = Battleship(ship.first, ship.second);
        }while(!randomField.addShip(ship.first, ship.second, bship));    
    }
    ship = gen_coordinate(3);
    Support sship(ship.first, ship.second);
    for(int i = sship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(3);
            sship = Support(ship.first, ship.second);
        }while(!randomField.addShip(ship.first, ship.second, sship));
    }
    ship = gen_coordinate(1);
    Submarine eship(ship.first, ship.second);
    for(int i = eship_custom; i > 0; i--){
        do{
            ship = gen_coordinate(1);
            eship = Submarine(ship.first, ship.second);
        }while(!randomField.addShip(ship.first, ship.second, eship));
    }
    return randomField;
}
Player insertShips(){
	Player p1;
	string bow, stern;
    pair<string, string> ship = gen_coordinate(5);
    Battleship bship(ship.first, ship.second);
    for(int i = bship_custom; i > 0; i--){
        do{
            cout<<"Inserire coordinata prua cannoniera"<<endl;
			cin>>bow;
			cout<<"Inserire coordinata poppa cannoniera"<<endl;
			cin>>stern;
        	bship=Battleship(bow, stern);
            if(!p1.addShip(bow, stern, bship)){
            	cout<<"coordinate non valide"<<endl;
            }
        }while(!p1.addShip(bow, stern, bship));    
    }
    ship = gen_coordinate(3);
    Support sship(ship.first, ship.second);
    for(int i = sship_custom; i > 0; i--){
        do{
          	cout<<"Inserire coordinata prua nave da supporto"<<endl;
			cin>>bow;
			cout<<"Inserire coordinata poppa nave da supporto"<<endl;
			cin>>stern;
         	sship=Support (bow, stern);
            if(!p1.addShip(bow, stern, sship)){
            	cout<<"coordinate non valide"<<endl;
            }
        }while(!p1.addShip(bow, stern, sship));
    }
	ship = gen_coordinate(1);
   	Submarine eship(ship.first, ship.second);
    for(int i = eship_custom; i > 0; i--){
        do{
        	cout<<"inserire coordinata sottomarino"<<endl;
        	cin>>bow;
        	stern=bow;
            eship=Submarine (bow, stern);
            if(!p1.addShip(bow, stern, eship)){
            	cout<<"coordinate non valide"<<endl;
            }
        }while(!p1.addShip(bow, stern, sship));
    }
    return p1;
}

void playerTurn(Player p1, Player p2){
   	string origin, target;
   	char move; 
	cout<<p1.getUsername()<<" è il tuo turno"<<endl;
	do{    
		cout<<"inserire coordinate per azione di turno (XYOrigin XYTarget)"<<endl;
		cin>>origin>>target;
		if(p1.getDefenceGrid().getTile(origin)==' '){
			cout<<"coordinate di origine non valide, nessuna nave presente, inserire nuove coordinate"<<endl;
			cin>>origin;
		}
	}while(p1.getDefenceGrid().getTile(origin)==' ');
	move=p1.getShip(origin)->getId();
	switch(move){
		case 'C':
			p1.shot(p1.getShip(origin), target, p2);
			break;
		case 'S':
			do{
				p1.move_heal(p1.getShip(origin), target);
				if(!p1.move_heal(p1.getShip(origin), target)){
					cout<<"coordinate non valide"<<endl;
					cout<<"inserire nuova coordinata destinazione valida occupata"<<endl;
					cin>>origin;
				}
			}while(!p1.move_heal(p1.getShip(origin), target));
			break;
		case 'E':
			do{
				p1.move_scan(p1.getShip(origin), target, p2);
				if(!p1.move_scan(p1.getShip(origin), target, p2)){
					cout<<"coordinate non valide"<<endl;
					cout<<"inserire nuova coordinata destinazione valida non occupata"<<endl;
					cin>>origin;
				}
			}while(!p1.move_scan(p1.getShip(origin), target, p2));
		break;		    		
	}
}
void botTurn(Player bot, Player p1){
	int rnd_move;
	rnd_move = rand()%3;
	switch (rnd_move){
	    case 0:
	        std::cout << "Spara: " << std::endl;

	        do{}while(!bot.shot(bot.getShip(shipIdentifier('C')), gen_coordinate(1).second, p1));
	        break;
	    case 1:
	        std::cout << "Sposta e cura: " << std::endl;
	        do{}while(!bot.move_heal(bot.getShip(shipIdentifier('S')), gen_coordinate(1).second));

	        p1_coordinate = updateAllCoords(bot);
	        break;
	    case 2:
	        std::cout << "Sposta e scansiona: " << std::endl;
	        do{}while(!bot.move_scan(bot.getShip(shipIdentifier('E')), gen_coordinate(1).second, p1));
	        //p1_coordinate = updateAllCoords(bot);
	        break;
	    }
}

std::string shipIdentifier(char id){
    string tile;
    bool identified = false; 
    /*
    std::vector<int> myvector (myints,myints+4);
    std::vector<int>::iterator it;

    it = find (myvector.begin(), myvector.end(), 30);
    if (it != myvector.end())
    */
    do{
        tile = gen_coordinate(1).second;
        std::cout << tile << std::endl;
    }while(!identified);
    return tile;
}

vector<string> updateAllCoords(Player player){
    std::vector<std::string> upToDate;
    std::map<std::string, Ship*>::iterator it = player.shipLegend().begin();
    while (it != player.shipLegend().end()){
        upToDate.push_back(it->first);
        it++;
    }
    return upToDate;
}

string CheckWinner(Player p1, Player p2){
	if(p1.getDefenceGrid().shipsCounter()==0){
		return p2.getUsername();
	}else if(p2.getDefenceGrid().shipsCounter()==0){
		return p1.getUsername();
	}
	return "draw";
}

string botVsbot(Player &bot1, Player &bot2){
    bot1 = randomFieldGenerator();
    p1_coordinate = updateAllCoords(bot1);
    bot2 = randomFieldGenerator();
    p2_coordinate = updateAllCoords(bot2);
    bot1.setUsername();
    bot2.setUsername();
    int turncounter=turn_custom;
    std::cout << endl << bot1 <<"--------------------------------"<< std::endl;
    std::cout << endl << bot2 <<"--------------------------------"<< std::endl;
    /*
    int rnd_move; 
    for (int i = 1; i <= turn_custom; i++){
        rnd_move = rand()%3;
        std::cout << bot1.getUsername()<<" turn: ";
        switch (rnd_move){
        case 0:
            std::cout << "Spara: " << std::endl;
            do{}while(!bot1.shot(bot1.getShip(shipIdentifier('C')), gen_coordinate(1).second, bot2));
            break;
        case 1:
            std::cout << "Sposta e cura: " << std::endl;
            do{}while(!bot1.move_heal(bot1.getShip(shipIdentifier('S')), gen_coordinate(1).second));
            p1_coordinate = updateAllCoords(bot1);
            break;
        case 2:
            std::cout << "Sposta e scansiona: " << std::endl;
            do{}while(!bot1.move_scan(bot1.getShip(shipIdentifier('E')), gen_coordinate(1).second, bot2));
            p1_coordinate = updateAllCoords(bot1);
            break;
        }
        rnd_move = rand()%3;
        std::cout << bot2.getUsername()<<" turn: ";
        switch (rnd_move){
        case 0:
            std::cout << "Spara: " << std::endl;
            bot2.shot(bot2.getShip(shipIdentifier('C', bot2)), gen_coordinate(1).first, bot1);
            break;
        case 1:
            std::cout << "Sposta e cura: " << std::endl;
            do{}while(!bot2.move_heal(bot2.getShip(shipIdentifier('S')), gen_coordinate(1).second));
            p2_coordinate = updateAllCoords(bot2);
            break;
        case 2:
            std::cout << "Sposta e scansiona: " << std::endl;
            do{}while(!bot2.move_scan(bot2.getShip(shipIdentifier('E')), gen_coordinate(1).second, bot1));
            p2_coordinate = updateAllCoords(bot2);
            break;
        }
        turncounter--;
    }*/
    std::cout << endl << bot1 <<"--------------------------------"<< std::endl;
    std::cout << endl << bot2 <<"--------------------------------"<< std::endl;
	if(turncounter==0){
		cout<<"partita finita per limite turni raggiunto"<<endl;
		return "draw";
	}
    return CheckWinner(bot1, bot2);
}

string playerVsbot(Player &p1, Player &bot){
    bot = randomFieldGenerator();
    int coin=rand()%2;
    int turncounter=turn_custom;
    string winner;
    cout<<"inserire le coordinate delle proprie navi"<<endl;
    p1=insertShips();

    if(coin==0){
    	cout<<"bot starts"<<endl;
   		for(int i=1; i<=turn_custom; i++){
		    cout <<"bot turn: ";
		    botTurn(bot,p1);
			playerTurn(p1, bot);
			turncounter--;
			if(winner!="draw"){
    			return winner;
    		}
		}
    }else{
    	for(int i=0; i<=turn_custom; i++){
    		cout<<p1.getUsername()<<" turn: "<<endl;
			playerTurn(p1, bot);
			botTurn(bot,p1);
		    turncounter--;
		    if(winner!="draw"){
    			return winner;
    		}
    	}
    }		
	if(turncounter==0){
		cout<<"partita finita per limite turni raggiunto"<<endl;
		return "draw";
	}
    return CheckWinner(bot, p1);
}

string playerVsplayer(Player &p1, Player &p2){
	int coin=rand()%2;
    int turncounter=turn_custom;
    string winner;
    cout<<p1.getUsername()<<" inserire le coordinate delle proprie navi"<<endl;
    p1=insertShips();
    cout<<p2.getUsername()<<" inserire le coordinate delle proprie navi"<<endl;
    p2=insertShips();
    if(coin==0){
    	for(int i=1; i<=turn_custom; i++){
    		playerTurn(p1, p2);
    		playerTurn(p2, p1);
    		turncounter--;
    		winner=CheckWinner(p1, p2);
    		if(winner!="draw"){
    			return winner;
    		}
    	}
	}else{
		for(int i=1; i<=turn_custom; i++){
    		playerTurn(p2, p1);
    		playerTurn(p1, p2);
    		turncounter--;
    		winner=CheckWinner(p1, p2);
    		if(winner!="draw"){
    			return winner;
    		}
    	}
	}
	if(turncounter==0){
		cout<<"partita finita per limite turni raggiunto"<<endl;
		return "draw";
	}
    return CheckWinner(p1, p2);
}

int main(){
    Player p1, p2;
    int players;
    string username, winner;
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
        winner = botVsbot(p1, p2);
        break;
    case 1:
        std::cout << "Inserire il proprio username: ";
        cin >> username;
        p1.setUsername(username);
        std::cout << p1.getUsername() << std::endl;
        winner = playerVsbot(p1, p2);
        break;
    case 2:
        std::cout << "Player 1 - Inserire il proprio username: ";
        cin >> username;
        p1.setUsername(username);
        std::cout << endl << "Player 2 - Inserire il proprio username: ";
        cin >> username;
        p2.setUsername(username);
        std::cout << p1.getUsername() << p2.getUsername() << std::endl;
        winner = playerVsplayer(p1, p2);
        break;
    }

    //testGame(p1, p2);
    return 0;
}
