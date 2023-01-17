#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <cstdlib>
#include <ctime>
#include "headers/player.h"
using namespace std;

/*Compilatore
*   g++ -o test mainGame.cpp charts/chart.cpp charts/attack_chart.cpp charts/defense_chart.cpp player/player.cpp ships/ship.cpp ships/battleship.cpp ships/support.cpp ships/submarine.cpp
*
*/

pair<string,string> createXY(int dim){
	char start='a';
	char random_alpha;
	char random_skip;
	int random_y;
	int random_rotation=rand()%2;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0,13);
	string t1, t2;
	srand(time(NULL));
	if(random_rotation==1){
		do{
			random_alpha=start+dis(gen);
			random_y=dis(gen)+1;
			t1=random_alpha+to_string(random_y);
			t2=random_alpha+to_string(random_y+(dim-1));
		}while((random_y+(dim-1)>12));
	}else{
		do{
			random_alpha=start+dis(gen);
			random_y=dis(gen)+1;
			random_skip=(random_alpha+(dim-1)>'j'&&dim>1)?(random_alpha+(dim-1)+2): random_alpha+(dim-1);
			t1=random_alpha+to_string(random_y);
			t2=random_skip;
			t2+=to_string(random_y);
		}while((random_alpha+(dim-1))>'l');
	}
	return make_pair(t1,t2);
}

string RndTileSelector(){
	char start='a';
	char random_alpha;
	int random_y;
	string t;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0,11);
	random_alpha=start+dis(gen);
	random_y=dis(gen)+1;
	t=random_alpha+to_string(random_y);
	return t;
}
void botVsbotGame(Player p1, Player p2, int turncount){
	int move;
	srand(time(NULL));
	for(int i=turncount; i>=0; i++){
		if(i%2==0){
			move=rand()%3+1;
			switch(move){
				case 1:
					p1.shot(p1.getShip(RndTileSelector()), RndTileSelector(), p2);
					break;
				case 2:
					p1.move_heal(p1.getShip(RndTileSelector()), RndTileSelector());
					break;
				case 3:
					p1.move_scan(p1.getShip(RndTileSelector()), RndTileSelector(), p2);
					break;
			}
		}else{
			move=rand()%3+1;
			switch(move){
				case 1:
					p2.shot(p2.getShip(RndTileSelector()), RndTileSelector(), p1);
					break;
				case 2:
					p2.move_heal(p2.getShip(RndTileSelector()), RndTileSelector());
					break;
				case 3:
					p2.move_scan(p2.getShip(RndTileSelector()), RndTileSelector(), p1);
					break;
			}
		}
	}
	/*std::map<std::string, Ship*>::iterator it = p1.shipLegend().begin();
            while (it != p1.shipLegend().end()){
                if(it->second == ships){
                    a_grid.setTile(it->first, 'X');
                }
                it++;
            }
	if(*/
}
Player botVsbot(Player p1,Player p2, int turncount){
	pair<string,string>t=createXY(5);
	bool created=true;
	int random_move;
	Battleship bs1(t.first, t.second);
	created=p1.addShip(t.first, t.second, bs1);
	cout<<"bs1 created"<<endl;
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(5);
		Battleship bs2(t.first, t.second);
		created=p1.addShip(t.first, t.second, bs2);
		if(created){
			cout<<"bs2 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(5);
		Battleship bs3(t.first, t.second);
		created=p1.addShip(t.first, t.second, bs3);
		if(created){
			cout<<"bs3 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss1(t.first, t.second);
		created=p1.addShip(t.first, t.second, ss1);
		if(created){
			cout<<"ss1 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss2(t.first, t.second);
		created=p1.addShip(t.first, t.second, ss2);
		if(created){
			cout<<"ss2 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss3(t.first, t.second);
		created=p1.addShip(t.first, t.second, ss3);
		if(created){
			cout<<"ss3 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(1);
		Submarine sb1(t.first, t.second);
		created=p1.addShip(t.first, t.second, sb1);
		if(created){
			cout<<"sb1 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(1);
		Submarine sb2(t.first, t.second);
		created=p1.addShip(t.first, t.second, sb2);
		if(created){
			cout<<"sb2 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	cout<<"player 1: \n"<<p1<<endl;
	t=createXY(5);
	Battleship bs4(t.first, t.second);
	created=p2.addShip(t.first, t.second, bs4);
	cout<<"bs4 created"<<endl;
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(5);
		Battleship bs5(t.first, t.second);
		created=p2.addShip(t.first, t.second, bs5);
		if(created){
			cout<<"bs5 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(5);
		Battleship bs6(t.first, t.second);
		created=p2.addShip(t.first, t.second, bs6);
		if(created){
			cout<<"bs6 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss4(t.first, t.second);
		created=p2.addShip(t.first, t.second, ss4);
		if(created){
			cout<<"ss4 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss5(t.first, t.second);
		created=p2.addShip(t.first, t.second, ss5);
		if(created){
			cout<<"ss5 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss6(t.first, t.second);
		created=p2.addShip(t.first, t.second, ss6);
		if(created){
			cout<<"ss6 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(1);
		Submarine sb3(t.first, t.second);
		created=p2.addShip(t.first, t.second, sb3);
		if(created){
			cout<<"sb3 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(1);
		Submarine sb4(t.first, t.second);
		created=p2.addShip(t.first, t.second, sb4);
		if(created){
			cout<<"sb4 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	cout<<"player 2: \n"<<p2<<endl;
	//botVsbotGame(Player p1, Player p2, int turncount);
	

	return p1;
}

Player playerVsplayer(Player p1, Player p2){
	int coin=rand()%2;
	if(coin==0){
		cout<<p1.getUsername()<<" inizia"<<endl;
	}else{
		cout<<p2.getUsername()<<" inizia"<<endl;
	}
	return p1;
}


int main(){
    Player winner, p1, p2;
    int players;
    string username;
	int turncount=10;
    std::cout << "Benvenuti: prego inserire il numero di giocatori [Max 2]: ";
    cin >> players;
    std::cout <<flush; //flush forces the printing to the screen before it pauses
    //system("clear");

    switch (players)
    {
    case 0:
        winner = botVsbot(p1, p2,turncount);
        cout<<"player 1 vince"<<endl;
        break;
    case 1:
        std::cout << "Inserire il proprio username: ";
        cin >> username;
        p1.setUsername(username);
        std::cout << p1.getUsername() << std::endl;
       // winner = playerVsbot(p1, p2);
        break;
    case 2:
        std::cout << "Player 1 - Inserire il proprio username: ";
        cin >> username;
        p1.setUsername(username);
        std::cout << endl << "Player 2 - Inserire il proprio username: ";
        cin >> username;
        p2.setUsername(username);
        std::cout << p1.getUsername() << p2.getUsername() << std::endl;
       // winner = playerVsplayer(p1, p2);
        break;
    }
    return 0;
}
